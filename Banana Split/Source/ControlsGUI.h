/*
  ==============================================================================

    ControlsGUI.h
    Created: 3 Jun 2022 6:15:37pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class ControlsGUI  : public juce::Component
{
public:
    
    ControlsGUI(MidiSynthAudioProcessor&);
    ~ControlsGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MidiSynthAudioProcessor& audioProcessor;
    
    juce::Slider gain;
    juce::Label gainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    juce::Slider attack;
    juce::Label attackLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    
    juce::Slider decay;
    juce::Label decayLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    
    juce::Slider sustain;
    juce::Label sustainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    
    juce::Slider release;
    juce::Label releaseLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    
    juce::Slider fmFreq;
    juce::Label fmFreqLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    
    juce::Slider fmDepth;
    juce::Label fmDepthLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsGUI)
};
