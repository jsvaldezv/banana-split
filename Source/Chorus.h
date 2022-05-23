/*
  ==============================================================================

    Chorus.h
    Created: 23 May 2022 4:18:46pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Chorus
{
public:
    
    Chorus();
    ~Chorus();
    
    void prepare(double inSampleRate, int inNumChannels, int inSamplesPerBlock);
    
    void process(juce::AudioBuffer<float> inBuffer);
    
private:
    
    juce::dsp::Chorus<float> chorus;
    
};
