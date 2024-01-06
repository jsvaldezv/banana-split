/*
  ==============================================================================

    Reverb.cpp
    Created: 23 May 2022 4:18:41pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "Reverb.h"

Reverb::Reverb(){}

Reverb::~Reverb(){}

void Reverb::prepare(juce::dsp::ProcessSpec inSpec)
{    
    reverb.reset();
    reverb.prepare(inSpec);
    reverb.setParameters(revParams);
    
    gain.prepare(inSpec);
    gain.reset();
    gain.setGainDecibels(-12);
}

void Reverb::process(juce::AudioBuffer<float> inBuffer)
{
    juce::dsp::AudioBlock<float> block (inBuffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    
    reverb.process(context);
    gain.process(context);
}
