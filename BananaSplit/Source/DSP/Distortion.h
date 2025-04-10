/*
  ==============================================================================

    Distortion.h
    Created: 23 May 2022 4:19:01pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Distortion
{
public:

    void process (juce::AudioBuffer<float>& inBuffer);

private:

    float gain { 50.0f };
};
