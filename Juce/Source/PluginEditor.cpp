#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiSynthAudioProcessorEditor::MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
{
    addAndMakeVisible (keyboard)
    setSize (400, 300);
}

MidiSynthAudioProcessorEditor::~MidiSynthAudioProcessorEditor(){}

void MidiSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
   
}

void MidiSynthAudioProcessorEditor::resized()
{
keyboard.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.5f);

}


