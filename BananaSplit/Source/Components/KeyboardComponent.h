/*
  ==============================================================================

    KeyboardComponent.h
    Created: 29 May 2022 8:01:14pm
    Author:  ximec

  ==============================================================================
*/

#pragma once
#include "../PluginProcessor.h"

class KeyboardComponent : public juce::Component, public juce::Timer
{
public:

    KeyboardComponent (juce::MidiKeyboardState&);

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:

    juce::MidiKeyboardState& keyboardState;
    juce::MidiKeyboardComponent keyboardComponent { keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};
