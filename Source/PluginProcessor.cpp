#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiSynthAudioProcessor::MidiSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MidiSynthAudioProcessor::~MidiSynthAudioProcessor(){}

const juce::String MidiSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiSynthAudioProcessor::getNumPrograms()
{
    return 1;
}

int MidiSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiSynthAudioProcessor::setCurrentProgram ([[maybe_unused]] int index){}

const juce::String MidiSynthAudioProcessor::getProgramName ([[maybe_unused]] int index)
{
    return {};
}

void MidiSynthAudioProcessor::changeProgramName ([[maybe_unused]] int index, [[maybe_unused]] const juce::String& newName){}

void MidiSynthAudioProcessor::prepareToPlay ([[maybe_unused]] double sampleRate, [[maybe_unused]] int samplesPerBlock){}

void MidiSynthAudioProcessor::releaseResources(){}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}
#endif

void MidiSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                            [[maybe_unused]] juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    
}

bool MidiSynthAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* MidiSynthAudioProcessor::createEditor()
{
    return new MidiSynthAudioProcessorEditor (*this);
}

void MidiSynthAudioProcessor::getStateInformation ([[maybe_unused]] juce::MemoryBlock& destData){}

void MidiSynthAudioProcessor::setStateInformation ([[maybe_unused]] const void* data, [[maybe_unused]] int sizeInBytes){}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiSynthAudioProcessor();
}
