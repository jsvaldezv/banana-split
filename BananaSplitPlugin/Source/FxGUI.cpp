/*
  ==============================================================================

    FxGUI.cpp
    Created: 3 Jun 2022 6:15:44pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FxGUI.h"

FxGUI::FxGUI()
{
    reverb.setButtonText("Reverb");
    reverb.setClickingTogglesState(true);
    addAndMakeVisible(reverb);
    
    chorus.setButtonText("Chorus");
    chorus.setClickingTogglesState(true);
    addAndMakeVisible(chorus);
    
    delay.setButtonText("Delay");
    delay.setClickingTogglesState(true);
    addAndMakeVisible(delay);
    
    distortion.setButtonText("Distortion");
    distortion.setClickingTogglesState(true);
    addAndMakeVisible(distortion);
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
