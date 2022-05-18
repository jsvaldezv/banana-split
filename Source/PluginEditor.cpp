#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiSynthAudioProcessorEditor::MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

MidiSynthAudioProcessorEditor::~MidiSynthAudioProcessorEditor(){}

void MidiSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Banana Split!", getLocalBounds(), juce::Justification::centred, 1);
}

void MidiSynthAudioProcessorEditor::resized(){}
