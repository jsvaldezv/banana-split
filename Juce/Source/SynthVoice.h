/*
  ==============================================================================

    SynthVoice.h
    Created: 18 May 2022 8:26:10pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Oscillator.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    
    SynthVoice();
    
    ~SynthVoice() override;
    
    bool canPlaySound (juce::SynthesiserSound *) override;
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels);
    
    void updateParameters(juce::AudioProcessorValueTreeState& inAPVT);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void setWaveType(int inType);
    
private:
    
    bool isPrepared {false};
    
    // OSC ONE
    int mMidiNote {0};
    juce::dsp::Oscillator<float> oscOne;
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::AudioBuffer<float> synthBuffer;
    
    juce::dsp::Oscillator<float> oscOneFm;
    float fmMod {0.0f};
    float fmDepth {0.0f};
    
    //juce::MidiKeyboardState& keyboardState;
};
