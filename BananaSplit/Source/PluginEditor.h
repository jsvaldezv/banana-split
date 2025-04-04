#pragma once
#include "Components/ControlsComponent.h"
#include "Components/FxComponent.h"
#include "Components/KeyboardComponent.h"
#include "PluginProcessor.h"
#include <JuceHeader.h>

class BananaSplitAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:

    BananaSplitAudioProcessorEditor (BananaSplitAudioProcessor&);
    ~BananaSplitAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    BananaSplitAudioProcessor& audioProcessor;

    juce::Image backgroundImage { juce::ImageFileFormat::loadFrom (BinaryData::background_png, BinaryData::background_pngSize) };
    juce::Image glassImage { juce::ImageFileFormat::loadFrom (BinaryData::glass_png, BinaryData::glass_pngSize) };

    juce::ImageComponent background;
    juce::ImageComponent glass;

    KeyboardComponent keyboard { audioProcessor.getKeyboardState() };
    ControlsComponent controls { audioProcessor };
    FxComponent fx { audioProcessor };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BananaSplitAudioProcessorEditor)
};
