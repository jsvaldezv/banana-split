/*
  ==============================================================================

    ControlsComponent.cpp
    Created: 3 Jun 2022 6:15:37pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "ControlsComponent.h"

ControlsComponent::ControlsComponent (BananaSplitAudioProcessor& p) : audioProcessor (p)
{
    prepareSlider (gain, gainLabel, BananaSplit::Gain, juce::Colour (57, 236, 57), juce::Colours::limegreen, juce::Colour (36, 150, 36));
    prepareSlider (attack, attackLabel, BananaSplit::Attack, juce::Colours::hotpink, juce::Colours::hotpink, juce::Colours::deeppink);
    prepareSlider (decay, decayLabel, BananaSplit::Decay, juce::Colour (57, 236, 229), juce::Colour (48, 198, 192), juce::Colour (42, 166, 161));
    prepareSlider (sustain, sustainLabel, BananaSplit::Sustain, juce::Colours::orange, juce::Colours::orange, juce::Colours::darkorange);
    prepareSlider (release, releaseLabel, BananaSplit::Release, juce::Colours::red, juce::Colours::red, juce::Colours::darkred);
    prepareSlider (fmFreq, fmFreqLabel, BananaSplit::FmFreq, juce::Colours::purple, juce::Colours::mediumpurple, juce::Colours::purple);
    prepareSlider (fmDepth, fmDepthLabel, BananaSplit::FmDepth, juce::Colours::yellow, juce::Colours::lightyellow, juce::Colours::yellow);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), BananaSplit::Gain, gain);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), BananaSplit::Attack, attack);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), BananaSplit::Decay, decay);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), BananaSplit::Sustain, sustain);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), BananaSplit::Release, release);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), BananaSplit::FmFreq, fmFreq);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), BananaSplit::FmDepth, fmDepth);
}

void ControlsComponent::paint (juce::Graphics&) {}

void ControlsComponent::prepareSlider (juce::Slider& slider,
                                       juce::Label& label,
                                       juce::String labelString,
                                       juce::Colour thumbColour,
                                       juce::Colour backgroundColour,
                                       juce::Colour trackColour)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    slider.setColour (juce::Slider::thumbColourId, thumbColour);
    slider.setColour (juce::Slider::backgroundColourId, backgroundColour);
    slider.setColour (juce::Slider::trackColourId, trackColour);
    addAndMakeVisible (slider);

    label.setText (labelString, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setColour (juce::Label::textColourId, juce::Colours::white);
    label.setFont (juce::Font (10.0f, juce::Font::plain));
    addAndMakeVisible (label);
}

void ControlsComponent::resized()
{
    gain.setBoundsRelative (0.06f, 0.5f - (0.9f / 2.0f), 0.1f, 0.8f);
    gainLabel.setBoundsRelative (0.058f, 0.865f, 0.1f, 0.1f);

    attack.setBoundsRelative (0.185f, 0.5f - (0.9f / 2.0f), 0.1f, 0.8f);
    attackLabel.setBoundsRelative (0.185f, 0.865f, 0.1f, 0.1f);

    decay.setBoundsRelative (0.33f, 0.5f - (0.9f / 2.0f), 0.1f, 0.8f);
    decayLabel.setBoundsRelative (0.33f, 0.865f, 0.1f, 0.1f);

    sustain.setBoundsRelative (0.475f, 0.5f - (0.9f / 2.0f), 0.1f, 0.8f);
    sustainLabel.setBoundsRelative (0.477f, 0.865f, 0.1f, 0.1f);

    release.setBoundsRelative (0.597f, 0.5f - (0.9f / 2.0f), 0.1f, 0.8f);
    releaseLabel.setBoundsRelative (0.595f, 0.865f, 0.1f, 0.1f);

    fmFreq.setBoundsRelative (0.725f, 0.5f - (0.9f / 2.0f), 0.1f, 0.8f);
    fmFreqLabel.setBoundsRelative (0.723f, 0.865f, 0.1f, 0.1f);

    fmDepth.setBoundsRelative (0.86f, 0.5f - (0.9f / 2.0f), 0.1f, 0.8f);
    fmDepthLabel.setBoundsRelative (0.86f, 0.865f, 0.1f, 0.1f);
}
