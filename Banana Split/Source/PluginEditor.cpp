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
    
    glass.setImage(glassImage, juce::RectanglePlacement::stretchToFit);
    glass.setInterceptsMouseClicks(false, true);
    addAndMakeVisible(glass);
    
    setSize (700, 400);
}

MidiSynthAudioProcessorEditor::~MidiSynthAudioProcessorEditor(){}

void MidiSynthAudioProcessorEditor::paint ([[maybe_unused]] juce::Graphics& g){}

void MidiSynthAudioProcessorEditor::resized()
{
    background. setBounds(0, 0, 700, 300);
    controls.   setBounds(84, 62, 386, 169);
    fx.         setBounds(502, 62, 115, 169);
    keyboard.   setBounds(0, 300, 700, 100);
    glass.      setBounds(0, 0, 700, 302);
}
