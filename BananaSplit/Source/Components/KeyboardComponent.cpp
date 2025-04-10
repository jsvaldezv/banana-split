/*
  ==============================================================================

    KeyboardComponent.cpp
    Created: 29 May 2022 8:01:14pm
    Author:  ximec

  ==============================================================================
*/

#include "KeyboardComponent.h"

KeyboardComponent::KeyboardComponent (juce::MidiKeyboardState& keyState) : keyboardState (keyState)
{
    addAndMakeVisible (keyboardComponent);
    keyboardComponent.setMidiChannel (1);

    startTimer (400);
}

void KeyboardComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::red);
}

void KeyboardComponent::resized()
{
    keyboardComponent.setBoundsRelative (0.0f, 0.0f, 1.0f, 1.0f);
}

void KeyboardComponent::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}
