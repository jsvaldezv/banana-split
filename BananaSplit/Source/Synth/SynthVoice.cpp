/*
  ==============================================================================

    SynthVoice.cpp
    Created: 18 May 2022 8:26:10pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*> (sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float /*velocity*/, juce::SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/)
{
    auto frequency = static_cast<float> (juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber));

    mMidiNote = midiNoteNumber;
    oscOne.setFrequency (frequency + fmMod);
    adsr.noteOn();
}

void SynthVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    adsr.noteOff();

    if (! allowTailOff || ! adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int /*controllerNumber*/, int /*newControllerValue*/) {}

void SynthVoice::pitchWheelMoved (int /*newPitchWheelValue*/) {}

void SynthVoice::prepare (double inSampleRate, int inSamplesPerBlock, int inNumChannels)
{
    adsr.setSampleRate (inSampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.numChannels = static_cast<juce::uint32> (inNumChannels);
    spec.maximumBlockSize = static_cast<juce::uint32> (inSamplesPerBlock);

    oscOne.prepare (spec);
    oscOne.initialise ([] (float x)
    {
        return x / juce::MathConstants<float>::pi * x;
    });

    oscOneFm.prepare (spec);
    oscOneFm.initialise ([] (float x)
    {
        return std::sin (x);
    });

    gainOne.prepare (spec);

    isPrepared = true;
}

void SynthVoice::updateParameters (juce::AudioProcessorValueTreeState& inAPVT)
{
    auto typeOne = static_cast<int> (inAPVT.getRawParameterValue (BananaSplit::Type)->load());
    auto gainOneValue = inAPVT.getRawParameterValue (BananaSplit::Gain)->load();

    auto attack = inAPVT.getRawParameterValue (BananaSplit::Attack)->load();
    auto decay = inAPVT.getRawParameterValue (BananaSplit::Decay)->load();
    auto sustain = inAPVT.getRawParameterValue (BananaSplit::Sustain)->load();
    auto release = inAPVT.getRawParameterValue (BananaSplit::Release)->load();

    auto fmFreq = inAPVT.getRawParameterValue (BananaSplit::FmFreq)->load();
    auto fmDepthUser = inAPVT.getRawParameterValue (BananaSplit::FmDepth)->load();

    setWaveType (typeOne);
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    adsr.setParameters (adsrParams);
    gainOne.setGainDecibels (gainOneValue);

    oscOneFm.setFrequency (fmFreq);
    fmDepth = fmDepthUser;

    auto currentFreq = static_cast<float> (juce::MidiMessage::getMidiNoteInHertz (mMidiNote)) + fmMod;
    oscOne.setFrequency (currentFreq >= 0 ? currentFreq : currentFreq * 1.0f);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);

    if (! isVoiceActive())
        return;

    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };

    for (auto channel = 0; channel < static_cast<int> (audioBlock.getNumChannels()); ++channel)
    {
        for (int i = 0; i < static_cast<int> (audioBlock.getNumSamples()); i++)
        {
            auto sample = audioBlock.getSample (channel, i);
            fmMod = oscOneFm.processSample (sample) * fmDepth;
        }
    }

    juce::dsp::ProcessContextReplacing<float> block (audioBlock);
    oscOne.process (block);
    gainOne.process (block);

    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);

        if (! adsr.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::setWaveType (int inType)
{
    switch (inType)
    {
        // Sin
        case BananaSplit::OscType::Sin:
            oscOne.initialise ([] (float x)
            {
                return std::sinf (2.0f * juce::MathConstants<float>::pi * x);
            });
            break;

        // Square
        case BananaSplit::OscType::Square:
            oscOne.initialise ([] (float x)
            {
                return x <= 0.5f ? 1.0f : -1.0f;
            });
            break;

        // Triangle
        case BananaSplit::OscType::Triangle:
            oscOne.initialise ([] (float x)
            {
                return (2.0f / juce::MathConstants<float>::pi) * std::asinf (std::sinf (2.0f * juce::MathConstants<float>::pi * x));
            });
            break;

        // Saw
        case BananaSplit::OscType::Saw:
            oscOne.initialise ([] (float x)
            {
                return -(2.0f / juce::MathConstants<float>::pi) * std::atanf (1.0f / std::tanf (juce::MathConstants<float>::pi * x));
            });
            break;
    }
}
