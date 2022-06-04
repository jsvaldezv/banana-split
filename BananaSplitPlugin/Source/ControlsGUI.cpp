/*
  ==============================================================================

    ControlsGUI.cpp
    Created: 3 Jun 2022 6:15:37pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ControlsGUI.h"

ControlsGUI::ControlsGUI(MidiSynthAudioProcessor& p) : audioProcessor(p)
{
    gain.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    gain.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    gain.setColour(juce::Slider::backgroundColourId, juce::Colours::lightyellow);
    gain.setColour(juce::Slider::trackColourId, juce::Colours::yellowgreen);
    addAndMakeVisible(gain);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Gain", gain);
    
    attack.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attack.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    attack.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    attack.setColour(juce::Slider::backgroundColourId, juce::Colours::blue);
    attack.setColour(juce::Slider::trackColourId, juce::Colours::red);
    addAndMakeVisible(attack);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Attack", attack);
    
    decay.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decay.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    decay.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    decay.setColour(juce::Slider::backgroundColourId, juce::Colours::blue);
    decay.setColour(juce::Slider::trackColourId, juce::Colours::red);
    addAndMakeVisible(decay);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Decay", decay);
    
    sustain.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    sustain.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    sustain.setColour(juce::Slider::backgroundColourId, juce::Colours::blue);
    sustain.setColour(juce::Slider::trackColourId, juce::Colours::red);
    addAndMakeVisible(sustain);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Sustain", sustain);
    
    release.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    release.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    release.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    release.setColour(juce::Slider::backgroundColourId, juce::Colours::blue);
    release.setColour(juce::Slider::trackColourId, juce::Colours::red);
    addAndMakeVisible(release);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Release", release);
    
    fmFreq.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    fmFreq.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    fmFreq.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    fmFreq.setColour(juce::Slider::backgroundColourId, juce::Colours::blue);
    fmFreq.setColour(juce::Slider::trackColourId, juce::Colours::red);
    addAndMakeVisible(fmFreq);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "FmFreq", fmFreq);
    
    fmDepth.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    fmDepth.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    fmDepth.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    fmDepth.setColour(juce::Slider::backgroundColourId, juce::Colours::blue);
    fmDepth.setColour(juce::Slider::trackColourId, juce::Colours::red);
    addAndMakeVisible(fmDepth);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "FmDepth", fmDepth);
}

ControlsGUI::~ControlsGUI(){}

void ControlsGUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::pink);
}

void ControlsGUI::resized()
{
    gain.   setBoundsRelative(0.05f, 0.5f - (0.9f/2.0f), 0.1f, 0.9f);
    
    attack. setBoundsRelative(0.185f, 0.5f - (0.9f/2.0f), 0.1f, 0.9f);
    decay.  setBoundsRelative(0.32f, 0.5f - (0.9f/2.0f), 0.1f, 0.9f);
    sustain.setBoundsRelative(0.455f, 0.5f - (0.9f/2.0f), 0.1f, 0.9f);
    release.setBoundsRelative(0.59f, 0.5f - (0.9f/2.0f), 0.1f, 0.9f);
    
    fmFreq. setBoundsRelative(0.725f, 0.5f - (0.9f/2.0f), 0.1f, 0.9f);
    fmDepth.setBoundsRelative(0.86f, 0.5f - (0.9f/2.0f), 0.1f, 0.9f);
}
