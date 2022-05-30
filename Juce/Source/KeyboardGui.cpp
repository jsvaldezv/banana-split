/*
  ==============================================================================

    KeyboardGui.cpp
    Created: 29 May 2022 8:01:14pm
    Author:  ximec

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KeyboardGui.h"

//==============================================================================
KeyboardGui::KeyboardGui(): keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible (keyboardComponent);

}

KeyboardGui::~KeyboardGui()
{
}

void KeyboardGui::paint (juce::Graphics& g)
{
    
  
}

void KeyboardGui::resized()
{
    

}
