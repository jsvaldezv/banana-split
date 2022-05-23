/*
  ==============================================================================

    Reverb.h
    Created: 23 May 2022 4:18:41pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Reverb
{
public:
    
    Reverb();
    ~Reverb();
    
    void prepare(double inSampleRate, int inNumChannels, int inSamplesPerBlock);
    
    void process(juce::AudioBuffer<float> inBuffer);
    
private:
    
    juce::dsp::Reverb::Parameters revParams;
    juce::dsp::Reverb reverb;
    
};
