/*
  ==============================================================================

    Oscillator.cpp
    Created: 18 May 2022 1:09:48am
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "Oscillator.h"

Oscillator::Oscillator(){}

Oscillator::~Oscillator(){}

void Oscillator::prepare(double inSampleRate)
{
    sampleRate = static_cast<float>(inSampleRate);
    calculateIncrement();
}

void Oscillator::process(juce::AudioBuffer<float> inBuffer)
{
    for(int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for(int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            phase[channel] += increment[channel];
            
            if(phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
            
            float oscSample = sinf(2.0f * pi * phase[channel]) * depth;
            
            inBuffer.setSample(channel, i, oscSample);
        }
    }
}

void Oscillator::calculateIncrement()
{
    for(int channel = 0; channel < 2; channel++)
        increment[channel] = frequency * (1.0f / sampleRate);
}

void Oscillator::setFreq(float inFreq)
{
    frequency = inFreq;
    calculateIncrement();
}

void Oscillator::setDepth(float inDepth)
{
    depth = inDepth;
}
