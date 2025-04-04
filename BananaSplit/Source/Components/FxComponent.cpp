/*
  ==============================================================================

    FxComponent.cpp
    Created: 3 Jun 2022 6:15:44pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "FxComponent.h"

FxComponent::FxComponent (BananaSplitAudioProcessor& p) : audioProcessor (p)
{
    prepareSlider (reverb, "Reverb", juce::Colours::black, juce::Colours::green);
    prepareSlider (chorus, "Chorus", juce::Colours::black, juce::Colours::red);
    prepareSlider (delay, "Delay", juce::Colours::black, juce::Colours::yellow);
    prepareSlider (distortion, "Distortion", juce::Colours::black, juce::Colours::orange);

    delay.setColour (juce::TextButton::textColourOnId, juce::Colours::black);

    reverbAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.apvts, "Reverb", reverb);
    chorusAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.apvts, "Chorus", chorus);
    delayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.apvts, "Delay", delay);
    distorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.apvts, "Distortion", distortion);
}

void FxComponent::paint (juce::Graphics&) {}

void FxComponent::prepareSlider (juce::TextButton& button, juce::String labelString, juce::Colour onColour, juce::Colour offColour)
{
    button.setButtonText (labelString);
    button.setClickingTogglesState (true);
    button.setColour (juce::TextButton::buttonColourId, onColour);
    button.setColour (juce::TextButton::buttonOnColourId, offColour);
    addAndMakeVisible (button);
}

void FxComponent::resized()
{
    reverb.setBoundsRelative (0.5f - 0.45f, 0.07f, 0.9f, 0.2f);
    chorus.setBoundsRelative (0.5f - 0.45f, 0.29f, 0.9f, 0.2f);
    delay.setBoundsRelative (0.5f - 0.45f, 0.51f, 0.9f, 0.2f);
    distortion.setBoundsRelative (0.5f - 0.45f, 0.73f, 0.9f, 0.2f);
}
