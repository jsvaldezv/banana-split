/*
  ==============================================================================

    Chorus.cpp
    Created: 23 May 2022 4:18:46pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "Chorus.h"

Chorus::Chorus(){}

Chorus::~Chorus(){}

void Chorus::prepare(juce::dsp::ProcessSpec inSpec)
{
    chorus.reset();
    chorus.prepare(inSpec);
    
    chorus.setRate(2.0f);
    chorus.setDepth(0.9f);
    chorus.setCentreDelay(50.0f);
    chorus.setFeedback(0.7f);
    chorus.setMix(0.7f);
}

void Chorus::process(juce::AudioBuffer<float> inBuffer)
{
    juce::dsp::AudioBlock<float> block (inBuffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    chorus.process(context);
}
