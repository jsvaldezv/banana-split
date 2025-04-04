/*
  ==============================================================================

    SynthSound.h
    Created: 18 May 2022 8:26:29pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:

    bool appliesToNote (int /*midiNoteNumber*/) override { return true; }

    bool appliesToChannel (int /*midiChannel*/) override { return true; }
};
