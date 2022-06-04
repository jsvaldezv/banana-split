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
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    juce::Slider attack;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    
    juce::Slider decay;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    
    juce::Slider sustain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    
    juce::Slider release;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    
    juce::Slider fmFreq;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    
    juce::Slider fmDepth;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsGUI)
};
