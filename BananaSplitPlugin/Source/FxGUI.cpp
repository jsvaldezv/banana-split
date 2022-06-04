/*
  ==============================================================================

    FxGUI.cpp
    Created: 3 Jun 2022 6:15:44pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FxGUI.h"

FxGUI::FxGUI(MidiSynthAudioProcessor& p) : audioProcessor(p)
{
    reverb.setButtonText("Reverb");
    reverb.setClickingTogglesState(true);
    reverb.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    reverb.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    addAndMakeVisible(reverb);
    reverbAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvt, "Reverb", reverb);
    
    chorus.setButtonText("Chorus");
    chorus.setClickingTogglesState(true);
    chorus.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    chorus.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    addAndMakeVisible(chorus);
    chorusAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvt, "Chorus", chorus);
    
    
    delay.setButtonText("Delay");
    delay.setClickingTogglesState(true);
    delay.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    delay.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    addAndMakeVisible(delay);
    delayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvt, "Delay", delay);
    
    distortion.setButtonText("Distortion");
    distortion.setClickingTogglesState(true);
    distortion.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    distortion.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    addAndMakeVisible(distortion);
    distorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvt, "Distortion", distortion);
}

FxGUI::~FxGUI(){}

void FxGUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::blueviolet);
}

void FxGUI::resized()
{
    reverb.     setBoundsRelative(0.5f - 0.45f, 0.07f, 0.9f, 0.2f);
    chorus.     setBoundsRelative(0.5f - 0.45f, 0.29f, 0.9f, 0.2f);
    delay.      setBoundsRelative(0.5f - 0.45f, 0.51f, 0.9f, 0.2f);
    distortion. setBoundsRelative(0.5f - 0.45f, 0.73f, 0.9f, 0.2f);
}
