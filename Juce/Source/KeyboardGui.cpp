/*
  ==============================================================================

    KeyboardGui.cpp
    Created: 29 May 2022 8:01:14pm
    Author:  ximec

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KeyboardGUI.h"

KeyboardGUI::KeyboardGUI(juce::MidiKeyboardState& keyState) : keyboardState(keyState)
{
    addAndMakeVisible (keyboardComponent);
    keyboardComponent.setMidiChannel(1);
    
    startTimer(400);
}

KeyboardGUI::~KeyboardGUI(){}

void KeyboardGUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::red);
}

void KeyboardGUI::resized()
{
    keyboardComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}

void KeyboardGUI::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}
