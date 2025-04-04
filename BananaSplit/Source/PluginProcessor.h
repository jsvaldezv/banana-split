#pragma once
#include "DSP/Chorus.h"
#include "DSP/Delay.h"
#include "DSP/Distortion.h"
#include "DSP/Reverb.h"
#include "Helpers/DSP.h"
#include "Helpers/Parameters.h"
#include "Synth/SynthSound.h"
#include "Synth/SynthVoice.h"
#include <JuceHeader.h>

class BananaSplitAudioProcessor : public juce::AudioProcessor
{
public:

    BananaSplitAudioProcessor();
    ~BananaSplitAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::MidiKeyboardState keyboardState;

    juce::AudioProcessorValueTreeState apvts;

private:

    juce::Synthesiser synth;

    Reverb reverb;
    Delay delay;
    Chorus chorus;
    Distortion distortion;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BananaSplitAudioProcessor)
};
