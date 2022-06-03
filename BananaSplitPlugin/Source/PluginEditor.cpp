#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiSynthAudioProcessorEditor::MidiSynthAudioProcessorEditor (MidiSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    background.setImage(backgroundImage, juce::RectanglePlacement::stretchToFit);
    addAndMakeVisible(background);
    
    addAndMakeVisible (keyboard);
    
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    attackSlider.setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(attackSlider);
    
    setSize (700, 400);
}

MidiSynthAudioProcessorEditor::~MidiSynthAudioProcessorEditor()
{
    attackSlider.setLookAndFeel(nullptr);
}

void MidiSynthAudioProcessorEditor::paint ([[maybe_unused]] juce::Graphics& g){}

void MidiSynthAudioProcessorEditor::resized()
{
    background.setBounds(0, 0, 700, 300);
    keyboard.setBounds(0, 300, 700, 100);
    
    attackSlider.setBounds(0, 0, 100, 100);
}
