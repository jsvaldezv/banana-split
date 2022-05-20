/*
  ==============================================================================

    SynthVoice.cpp
    Created: 18 May 2022 8:26:10pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice(){}

SynthVoice::~SynthVoice(){}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber,
                            [[maybe_unused]] float velocity,
                            [[maybe_unused]] juce::SynthesiserSound *sound,
                            [[maybe_unused]] int currentPitchWheelPosition)
{
    auto frequency = static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    
    oscOne.setFrequency(frequency);
    
    adsr.noteOn();
}

void SynthVoice::stopNote ([[maybe_unused]] float velocity,
                           [[maybe_unused]] bool allowTailOff)
{
    adsr.noteOff();
    
    if(!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved ([[maybe_unused]] int controllerNumber, [[maybe_unused]] int newControllerValue) {}

void SynthVoice::pitchWheelMoved ([[maybe_unused]] int newPitchWheelValue) {}

void SynthVoice::prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels)
{
    adsr.setSampleRate(inSampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.numChannels = static_cast<juce::uint32>(inNumChannels);
    spec.maximumBlockSize = static_cast<juce::uint32>(inSamplesPerBlock);
    
    oscOne.prepare(spec);
    //oscOne.initialise([](float x) { return std::sinf(2.0f * juce::MathConstants<float>::pi * x); });
    oscOne.initialise([](float x) { return x / juce::MathConstants<float>::pi * x; });
    
    isPrepared = true;
}

void SynthVoice::updateParameters(juce::AudioProcessorValueTreeState& inAPVT)
{
    auto attack = inAPVT.getRawParameterValue("Attack")->load();
    auto decay = inAPVT.getRawParameterValue("Decay")->load();
    auto sustain = inAPVT.getRawParameterValue("Sustain")->load();
    auto release = inAPVT.getRawParameterValue("Release")->load();
    
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    adsr.setParameters(adsrParams);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    if(!isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    oscOne.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if(!adsr.isActive())
            clearCurrentNote();
    }
}
