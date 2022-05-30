#pragma once
#include <JuceHeader.h>
#include "Oscillator.h"
#include "Helpers_DSP.h"
#include "SynthSound.h"
#include "SynthVoice.h"

#include "Chorus.h"
#include "Delay.h"
#include "Distortion.h"
#include "Reverb.h"
#include "Gain.h"

class MidiSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    
    MidiSynthAudioProcessor();
    ~MidiSynthAudioProcessor() override;

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
    
    juce::AudioProcessorValueTreeState apvt;
    juce::AudioProcessorValueTreeState::ParameterLayout createAPVT();
    
    juce::MidiKeyboardState keyboardState;

private:
    
    juce::Synthesiser synth;
    
    Reverb reverb;
    Delay delay;
    Chorus chorus;
    Distortion distortion;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthAudioProcessor)
};
