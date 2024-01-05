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
    
    for (auto i = 0; i < 5; i++)
        synth.addVoice (new SynthVoice());
}

MidiSynthAudioProcessor::~MidiSynthAudioProcessor(){}

juce::AudioProcessorValueTreeState::ParameterLayout MidiSynthAudioProcessor::createAPVT()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    
    params.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID("Type", 1), "Type", juce::StringArray("Sin", "Square", "Triangle", "Saw"), 1));
    params.add(std::make_unique<juce::AudioParameterInt>(juce::ParameterID("Gain", 1), "Gain", -60.0f, 12.0f, -12.0f));
    
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Attack", 1), "Attack", 0.1f, 1.0f, 0.1f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Decay", 1), "Decay", 0.1f, 1.0f, 0.1f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Sustain", 1), "Sustain", 0.1f, 1.0f, 1.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Release", 1), "Release", 0.1f, 1.0f, 0.4f));

    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("FmFreq", 1), "FmFreq", 0.0f, 1000.0f, 5.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("FmDepth", 1), "FmDepth", 0.0f, 1000.0f, 50.0f));
    
    params.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Reverb", 1), "Reverb", false));
    params.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Chorus", 1), "Chorus", false));
    params.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Delay", 1), "Delay", false));
    params.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Distortion", 1), "Distortion", false));
    
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
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = 2;
    
    reverb.prepare(spec);
    chorus.prepare(spec);
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
    
    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);
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
    return new MidiSynthAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

void MidiSynthAudioProcessor::getStateInformation ([[maybe_unused]] juce::MemoryBlock& destData){}

void MidiSynthAudioProcessor::setStateInformation ([[maybe_unused]] const void* data, [[maybe_unused]] int sizeInBytes){}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiSynthAudioProcessor();
}
