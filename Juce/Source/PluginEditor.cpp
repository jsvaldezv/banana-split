#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiSynthAudioProcessorEditor::MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), keyboard(p)
{
    setSize (700, 400);
    
    addAndMakeVisible (keyboard);
}

MidiSynthAudioProcessorEditor::~MidiSynthAudioProcessorEditor(){}

void MidiSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
   
}

void MidiSynthAudioProcessorEditor::resized()
{
    keyboard.setBounds(0.0f, 300, 700, 100);
}
