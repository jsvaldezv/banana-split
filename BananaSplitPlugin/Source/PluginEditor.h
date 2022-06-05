#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KeyboardGUI.h"
#include "ControlsGUI.h"
#include "FxGUI.h"

class MidiSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor&);
    ~MidiSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MidiSynthAudioProcessor& audioProcessor;
    
    juce::Image backgroundImage { juce::ImageFileFormat::loadFrom(BinaryData::background_png, BinaryData::background_pngSize) };
    juce::ImageComponent        background;
    KeyboardGUI keyboard        { audioProcessor.keyboardState };
    
    juce::Image glassImage { juce::ImageFileFormat::loadFrom(BinaryData::glass_png, BinaryData::glass_pngSize) };
    juce::ImageComponent        glass;
    
    ControlsGUI controls        { audioProcessor };
    FxGUI fx                    { audioProcessor };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthAudioProcessorEditor)
};
