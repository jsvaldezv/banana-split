#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiSynthAudioProcessorEditor::MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    background.setImage(backgroundImage, juce::RectanglePlacement::stretchToFit);
    addAndMakeVisible(background);
    
    addAndMakeVisible(controls);
    
    addAndMakeVisible(fx);
    
    addAndMakeVisible(keyboard);
    
    setSize (700, 400);
}

MidiSynthAudioProcessorEditor::~MidiSynthAudioProcessorEditor(){}

void MidiSynthAudioProcessorEditor::paint ([[maybe_unused]] juce::Graphics& g){}

void MidiSynthAudioProcessorEditor::resized()
{
    background. setBounds(0, 0, 700, 300);
    controls.   setBounds(350 - 250 + 20, 150 - 100, 350, 200);
    fx.         setBounds(500 - 50 + 20, 150 - 100, 100, 200);
    keyboard.   setBounds(0, 300, 700, 100);
}
