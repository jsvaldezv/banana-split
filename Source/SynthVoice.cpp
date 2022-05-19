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
    adsr.noteOn();
    oscOne.setFreq(static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)));
}

void SynthVoice::stopNote ([[maybe_unused]] float velocity,
                           [[maybe_unused]] bool allowTailOff)
{
    adsr.noteOff();
}

void SynthVoice::controllerMoved ([[maybe_unused]] int controllerNumber,
                                  [[maybe_unused]] int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved ([[maybe_unused]] int newPitchWheelValue)
{
    
}

void SynthVoice::prepare(double inSampleRate, int inSamplesPerBlock)
{
    oscOne.prepare(inSampleRate);
    oscOne.setOscType(OSC_TYPE::SAW);
    
    adsr.setSampleRate(inSampleRate);
    
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    oscOne.process(outputBuffer);
    
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
