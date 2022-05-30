/*
  ==============================================================================

    KeyboardGui.h
    Created: 29 May 2022 8:01:14pm
    Author:  ximec

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class KeyboardGui  : public juce::Component, public juce::Timer
{
public:
    
    KeyboardGui(MidiSynthAudioProcessor&);
    ~KeyboardGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override; 
private:
    
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    MidiSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardGui)
};
