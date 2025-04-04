#include "PluginEditor.h"
#include "PluginProcessor.h"

BananaSplitAudioProcessorEditor::BananaSplitAudioProcessorEditor (BananaSplitAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    background.setImage (backgroundImage, juce::RectanglePlacement::stretchToFit);
    glass.setImage (glassImage, juce::RectanglePlacement::stretchToFit);
    glass.setInterceptsMouseClicks (false, true);

    addAndMakeVisible (background);
    addAndMakeVisible (controls);
    addAndMakeVisible (fx);
    addAndMakeVisible (keyboard);
    addAndMakeVisible (glass);

    setSize (700, 400);
}

BananaSplitAudioProcessorEditor::~BananaSplitAudioProcessorEditor() {}

void BananaSplitAudioProcessorEditor::paint (juce::Graphics&) {}

void BananaSplitAudioProcessorEditor::resized()
{
    background.setBounds (0, 0, 700, 300);
    controls.setBounds (84, 62, 386, 169);
    fx.setBounds (502, 62, 115, 169);
    keyboard.setBounds (0, 300, 700, 100);
    glass.setBounds (0, 0, 700, 302);
}
