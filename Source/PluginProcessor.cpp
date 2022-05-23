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
                       ), apvt(*this, nullptr, "PARAMETERS", createAPVT())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

MidiSynthAudioProcessor::~MidiSynthAudioProcessor(){}

juce::AudioProcessorValueTreeState::ParameterLayout MidiSynthAudioProcessor::createAPVT()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    
    params.add(std::make_unique<juce::AudioParameterChoice>("OscOne", "Osc One", juce::StringArray("Sin", "Square", "Triangle", "Saw"), 0));
    
    params.add(std::make_unique<juce::AudioParameterFloat>("Attack", "Attack", 0.1f, 1.0f, 0.1f));
    params.add(std::make_unique<juce::AudioParameterFloat>("Decay", "Decay", 0.1f, 1.0f, 0.1f));
    params.add(std::make_unique<juce::AudioParameterFloat>("Sustain", "Sustain", 0.1f, 1.0f, 1.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("Release", "Release", 0.1f, 1.0f, 0.4f));
    
    params.add(std::make_unique<juce::AudioParameterFloat>("OscOneFmFreq", "OscOneFmFreq", 0.0f, 1000.0f, 5.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("OscOneFmDepth", "OscOneFmDepth", 0.0f, 1000.0f, 500.0f));
    
    params.add(std::make_unique<juce::AudioParameterBool>("Reverb", "Reverb", false));
    params.add(std::make_unique<juce::AudioParameterBool>("Chorus", "Chorus", false));
    params.add(std::make_unique<juce::AudioParameterBool>("Delay", "Delay", false));
    params.add(std::make_unique<juce::AudioParameterBool>("Distortion", "Distortion", false));
    
    return params;
}

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

void MidiSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for(int i = 0; i < synth.getNumVoices(); i++)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
        }
    }
    
    reverb.prepare(sampleRate, getTotalNumInputChannels(), samplesPerBlock);
    chorus.prepare(sampleRate, getTotalNumInputChannels(), samplesPerBlock);
    delay.prepare(sampleRate);
}

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
                                            juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for(int i = 0; i < synth.getNumVoices(); i++)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // PARAMETERS
            voice->updateParameters(apvt);
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    //************************************************** FX ***************************************************//
    bool revToggle = static_cast<bool>(apvt.getRawParameterValue("Reverb")->load());
    bool choToggle = static_cast<bool>(apvt.getRawParameterValue("Chorus")->load());
    bool delayToggle = static_cast<bool>(apvt.getRawParameterValue("Delay")->load());
    bool distorToggle = static_cast<bool>(apvt.getRawParameterValue("Distortion")->load());
    
    if(revToggle)
        reverb.process(buffer);
    
    if(choToggle)
        chorus.process(buffer);
    
    if(distorToggle)
        distortion.process(buffer);
    
    if(delayToggle)
        delay.process(buffer);
}

bool MidiSynthAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* MidiSynthAudioProcessor::createEditor()
{
    //return new MidiSynthAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

void MidiSynthAudioProcessor::getStateInformation ([[maybe_unused]] juce::MemoryBlock& destData){}

void MidiSynthAudioProcessor::setStateInformation ([[maybe_unused]] const void* data, [[maybe_unused]] int sizeInBytes){}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiSynthAudioProcessor();
}
