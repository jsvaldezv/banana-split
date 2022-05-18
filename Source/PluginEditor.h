#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class MidiSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor&);
    ~MidiSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    MidiSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthAudioProcessorEditor)
};
