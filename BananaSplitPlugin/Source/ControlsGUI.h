/*
  ==============================================================================

    ControlsGUI.h
    Created: 3 Jun 2022 6:15:37pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ControlsGUI  : public juce::Component
{
public:
    
    ControlsGUI();
    ~ControlsGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider gain;
    
    juce::Slider attack;
    juce::Slider decay;
    juce::Slider sustain;
    juce::Slider release;
    
    juce::Slider fmFreq;
    juce::Slider fmDepth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsGUI)
};
