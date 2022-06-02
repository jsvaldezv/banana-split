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
            
            inBuffer.setSample(channel, i, getOscValue(type, channel));
            
            if(phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
        }
    }
}

float Oscillator::getOscValue(OSC_TYPE inOscType, int inChannel)
{
    float oscValue = 0.0f;
    float fase = phase[inChannel];
    
    switch(inOscType)
    {
        case SIN:
            oscValue = sinf(2.0f * pi * fase) * depth;
            break;
            
        case SQUARE:
            if (fase <= 0.5f)
                oscValue = 1.0f;
            else
                oscValue = -1.0f;
            break;
            
        case TRIANGLE:
            oscValue = (2.0f / pi) * asinf(sinf(2.0f * pi * fase));
            break;
            
        case SAW:
            oscValue = -(2.0f / pi) * atanf(1.0f/tanf(2.0f * pi * fase));
            break;
    }
    
    return oscValue;
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

void Oscillator::setOscType(int inType)
{
    switch(inType)
    {
        case 0:
            type = OSC_TYPE::SIN;
            break;
            
        case 1:
            type = OSC_TYPE::SQUARE;
            break;
            
        case 2:
            type = OSC_TYPE::TRIANGLE;
            break;
            
        case 3:
            type = OSC_TYPE::SAW;
            break;
    }
}
