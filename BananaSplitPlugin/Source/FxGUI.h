/*
  ==============================================================================

    FxGUI.h
    Created: 3 Jun 2022 6:15:44pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class FxGUI  : public juce::Component
{
public:
    
    FxGUI(MidiSynthAudioProcessor&);
    ~FxGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MidiSynthAudioProcessor& audioProcessor;
    
    juce::TextButton reverb;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> reverbAttachment;
    
    juce::TextButton chorus;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> chorusAttachment;
    
    juce::TextButton delay;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> delayAttachment;
    
    juce::TextButton distortion;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> distorAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxGUI)
};
