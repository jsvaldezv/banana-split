/*
  ==============================================================================

    FxGUI.h
    Created: 3 Jun 2022 6:15:44pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FxGUI  : public juce::Component
{
public:
    
    FxGUI();
    ~FxGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::TextButton reverb;
    juce::TextButton chorus;
    juce::TextButton delay;
    juce::TextButton distortion;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxGUI)
};
