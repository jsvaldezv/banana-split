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

void Chorus::prepare(double inSampleRate, int inNumChannels, int inSamplesPerBlock)
{
    // INICIALIZAR SPEC
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(inSamplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(inNumChannels);
    
    chorus.reset();
    chorus.prepare(spec);
    
    chorus.setMix(0.7f);
    chorus.setRate(2.0f);
    chorus.setDepth(1.0f);
    chorus.setFeedback(0.7f);
    chorus.setCentreDelay(50.0f);
}

void Chorus::process(juce::AudioBuffer<float> inBuffer)
{
    juce::dsp::AudioBlock<float> block (inBuffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    chorus.process(context);
}
