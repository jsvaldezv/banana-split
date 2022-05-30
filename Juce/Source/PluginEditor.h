#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KeyboardGUI.h"

class MidiSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor&);
    ~MidiSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MidiSynthAudioProcessor& audioProcessor;
    
    KeyboardGUI keyboard { audioProcessor.keyboardState };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthAudioProcessorEditor)
};
