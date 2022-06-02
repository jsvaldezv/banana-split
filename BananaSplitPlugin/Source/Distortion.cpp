/*
  ==============================================================================

    Distortion.cpp
    Created: 23 May 2022 4:19:01pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion(){}

Distortion::~Distortion(){}

void Distortion::process(juce::AudioBuffer<float>& inBuffer)
{
    for(int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for(int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float sample = inBuffer.getSample(channel, i);
            float newInput = sample * (gain / 10.0f);
            float out = 0.0f;
            
            // SOFT CLIPPING
            if (newInput >= 1.0f)
                out = 1.0f;
            else if ((newInput > -1.0f) && (newInput < 1.0f))
                out = (3.0f / 2.0f) * (newInput - (powf(newInput, 3.0f) / 3.0f));
            else if (newInput <= -1.0f)
                out = -1.0f;
            
            out = out * 0.5f;
            
            inBuffer.setSample(channel, i, out);
        }
    }
}
