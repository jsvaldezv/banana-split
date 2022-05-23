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

void Reverb::prepare(double inSampleRate, int inNumChannels, int inSamplesPerBlock)
{
    // INICIALIZAR SPEC
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(inSamplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(inNumChannels);
    
    reverb.reset();
    reverb.prepare(spec);
    
    reverb.setParameters(revParams);
}

void Reverb::process(juce::AudioBuffer<float> inBuffer)
{
    juce::dsp::AudioBlock<float> block (inBuffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    reverb.process(context);
}
