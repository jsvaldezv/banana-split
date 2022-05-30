/*
  ==============================================================================

    KeyboardGui.h
    Created: 29 May 2022 8:01:14pm
    Author:  ximec

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class KeyboardGui  : public juce::Component
{
public:
    KeyboardGui();
    ~KeyboardGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardGui)
};
