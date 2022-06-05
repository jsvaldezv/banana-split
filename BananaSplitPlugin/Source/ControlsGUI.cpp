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
    gain.setColour(juce::Slider::thumbColourId, juce::Colour(57, 236, 57));
    gain.setColour(juce::Slider::backgroundColourId, juce::Colours::limegreen);
    gain.setColour(juce::Slider::trackColourId, juce::Colour(36, 150, 36) );
    addAndMakeVisible(gain);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Gain", gain);
    
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    gainLabel.setFont(juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible(gainLabel);
    
    attack.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attack.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    attack.setColour(juce::Slider::thumbColourId, juce::Colours::hotpink);
    attack.setColour(juce::Slider::backgroundColourId, juce::Colours::hotpink);
    attack.setColour(juce::Slider::trackColourId, juce::Colours::deeppink);
    addAndMakeVisible(attack);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Attack", attack);
    
    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);
    attackLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    attackLabel.setFont(juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible(attackLabel);
    
    decay.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decay.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    decay.setColour(juce::Slider::thumbColourId, juce::Colour(57, 236, 229));
    decay.setColour(juce::Slider::backgroundColourId, juce::Colour(48, 198, 192));
    decay.setColour(juce::Slider::trackColourId, juce::Colour(42, 166, 161));
    addAndMakeVisible(decay);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Decay", decay);
    
    decayLabel.setText("Decay", juce::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centred);
    decayLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    decayLabel.setFont(juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible(decayLabel);
    
    sustain.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    sustain.setColour(juce::Slider::thumbColourId, juce::Colours::orange);
    sustain.setColour(juce::Slider::backgroundColourId, juce::Colours::orange);
    sustain.setColour(juce::Slider::trackColourId, juce::Colours::darkorange);
    addAndMakeVisible(sustain);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Sustain", sustain);
    
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    sustainLabel.setJustificationType(juce::Justification::centred);
    sustainLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    sustainLabel.setFont(juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible(sustainLabel);
    
    release.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    release.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    release.setColour(juce::Slider::thumbColourId, juce::Colours::red);
    release.setColour(juce::Slider::backgroundColourId, juce::Colours::red);
    release.setColour(juce::Slider::trackColourId, juce::Colours::darkred);
    addAndMakeVisible(release);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "Release", release);
    
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    releaseLabel.setFont(juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible(releaseLabel);
    
    fmFreq.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    fmFreq.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    fmFreq.setColour(juce::Slider::thumbColourId, juce::Colours::purple);
    fmFreq.setColour(juce::Slider::backgroundColourId, juce::Colours::mediumpurple);
    fmFreq.setColour(juce::Slider::trackColourId, juce::Colours::purple);
    addAndMakeVisible(fmFreq);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "FmFreq", fmFreq);
    
    fmFreqLabel.setText("FM Freq", juce::dontSendNotification);
    fmFreqLabel.setJustificationType(juce::Justification::centred);
    fmFreqLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    fmFreqLabel.setFont(juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible(fmFreqLabel);
    
    fmDepth.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    fmDepth.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    fmDepth.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    fmDepth.setColour(juce::Slider::backgroundColourId, juce::Colours::lightyellow);
    fmDepth.setColour(juce::Slider::trackColourId, juce::Colours::yellow);
    addAndMakeVisible(fmDepth);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvt, "FmDepth", fmDepth);
    
    fmDepthLabel.setText("FM Depth", juce::dontSendNotification);
    fmDepthLabel.setJustificationType(juce::Justification::centred);
    fmDepthLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    fmDepthLabel.setFont(juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible(fmDepthLabel);
}

ControlsGUI::~ControlsGUI(){}

void ControlsGUI::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::pink);
}

void ControlsGUI::resized()
{
    gain.           setBoundsRelative(0.06f, 0.5f - (0.9f/2.0f), 0.1f, 0.8f);
    gainLabel.      setBoundsRelative(0.058f, 0.865f, 0.1f, 0.1f);
    
    attack.         setBoundsRelative(0.185f, 0.5f - (0.9f/2.0f), 0.1f, 0.8f);
    attackLabel.    setBoundsRelative(0.185f, 0.865f, 0.1f, 0.1f);
    
    decay.          setBoundsRelative(0.33f, 0.5f - (0.9f/2.0f), 0.1f, 0.8f);
    decayLabel.     setBoundsRelative(0.33f, 0.865f, 0.1f, 0.1f);
    
    sustain.        setBoundsRelative(0.475f, 0.5f - (0.9f/2.0f), 0.1f, 0.8f);
    sustainLabel.   setBoundsRelative(0.477f, 0.865f, 0.1f, 0.1f);
    
    release.        setBoundsRelative(0.597f, 0.5f - (0.9f/2.0f), 0.1f, 0.8f);
    releaseLabel.   setBoundsRelative(0.595f, 0.865f, 0.1f, 0.1f);
    
    fmFreq.         setBoundsRelative(0.725f, 0.5f - (0.9f/2.0f), 0.1f, 0.8f);
    fmFreqLabel.    setBoundsRelative(0.723f, 0.865f, 0.1f, 0.1f);
    
    fmDepth.        setBoundsRelative(0.86f, 0.5f - (0.9f/2.0f), 0.1f, 0.8f);
    fmDepthLabel.   setBoundsRelative(0.86f, 0.865f, 0.1f, 0.1f);
}
