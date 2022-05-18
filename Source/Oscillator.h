/*
  ==============================================================================

    Oscillator.h
    Created: 18 May 2022 1:09:48am
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Oscillator
{
public:
    
    Oscillator();
    ~Oscillator();
    
    void prepare(double inSampleRate);
    
    void process(juce::AudioBuffer<float> inBuffer);
    
    void calculateIncrement();
    
    void setFreq(float inFreq);
    
    void setDepth(float inDepth);
    
private:
    
    //**************************************** GENERAL DATA ***************************************//
    float sampleRate {0.0f};
    float pi { juce::MathConstants<float>::pi };
    
    //***************************************** PARAMETERS ****************************************//
    float frequency {440.0f};
    float depth {1.0f};
    
    //******************************************** DATA *******************************************//
    float phase[2] {0.0f};
    float increment[2] {0.0f};
    
};
