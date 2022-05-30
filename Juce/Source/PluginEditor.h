#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KeyboardGui.h"

class MidiSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor&);
    ~MidiSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    KeyboardGui keyboard;
    MidiSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthAudioProcessorEditor)
};
