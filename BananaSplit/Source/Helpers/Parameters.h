/*
  ==============================================================================

    Helpers_DSP.h
    Created: 18 May 2022 1:37:28am
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace BananaSplit
{
    static const juce::String Type = "Type";
    static const juce::StringArray Types { "Sin", "Square", "Triangle", "Saw" };

    static const juce::String Gain = "Gain";

    static const juce::String Attack = "Attack";
    static const juce::String Decay = "Decay";
    static const juce::String Sustain = "Sustain";
    static const juce::String Release = "Release";

    static const juce::String FmFreq = "FmFreq";
    static const juce::String FmDepth = "FmDepth";

    static const juce::String Reverb = "Reverb";
    static const juce::String Chorus = "Chorus";
    static const juce::String Delay = "Delay";
    static const juce::String Distortion = "Distortion";

    inline juce::AudioProcessorValueTreeState::ParameterLayout createParameters()
    {
        juce::AudioProcessorValueTreeState::ParameterLayout params;

        params.add (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID (Type, 1), Type, Types, 1));

        params.add (std::make_unique<juce::AudioParameterInt> (juce::ParameterID (Gain, 1), Gain, -60.0f, 12.0f, -12.0f));

        params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (Attack, 1), Attack, 0.1f, 1.0f, 0.1f));
        params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (Decay, 1), Decay, 0.1f, 1.0f, 0.1f));
        params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (Sustain, 1), Sustain, 0.1f, 1.0f, 1.0f));
        params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (Release, 1), Release, 0.1f, 1.0f, 0.4f));

        params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (FmFreq, 1), FmFreq, 0.0f, 1000.0f, 5.0f));
        params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (FmDepth, 1), FmDepth, 0.0f, 1000.0f, 50.0f));

        params.add (std::make_unique<juce::AudioParameterBool> (juce::ParameterID (Reverb, 1), Reverb, false));
        params.add (std::make_unique<juce::AudioParameterBool> (juce::ParameterID (Chorus, 1), Chorus, false));
        params.add (std::make_unique<juce::AudioParameterBool> (juce::ParameterID (Delay, 1), Delay, false));
        params.add (std::make_unique<juce::AudioParameterBool> (juce::ParameterID (Distortion, 1), Distortion, false));

        return params;
    }
}
