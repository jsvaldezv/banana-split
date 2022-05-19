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

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
}
