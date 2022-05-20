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
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.8f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.5f;
    adsr.setParameters(adsrParams);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.numChannels = static_cast<juce::uint32>(inNumChannels);
    spec.maximumBlockSize = static_cast<juce::uint32>(inSamplesPerBlock);
    
    oscOne.prepare(spec);
    
    isPrepared = true;
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
