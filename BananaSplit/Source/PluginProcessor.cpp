#include "PluginProcessor.h"
#include "PluginEditor.h"

BananaSplitAudioProcessor::BananaSplitAudioProcessor() : AudioProcessor (BusesProperties()
                                                                             .withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                                                             .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
                                                         apvts (*this, nullptr, "Parameters", BananaSplit::createParameters())
{
    synth.addSound (new SynthSound());

    for (auto i = 0; i < BananaSplit::NumVoices; i++)
        synth.addVoice (new SynthVoice());
}

BananaSplitAudioProcessor::~BananaSplitAudioProcessor() {}

const juce::String BananaSplitAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BananaSplitAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool BananaSplitAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool BananaSplitAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double BananaSplitAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int BananaSplitAudioProcessor::getNumPrograms() { return 1; }

int BananaSplitAudioProcessor::getCurrentProgram() { return 0; }

void BananaSplitAudioProcessor::setCurrentProgram (int /*index*/) {}

const juce::String BananaSplitAudioProcessor::getProgramName (int /*index*/)
{
    return {};
}

void BananaSplitAudioProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/) {}

void BananaSplitAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice (i)))
            voice->prepare (sampleRate, samplesPerBlock, getTotalNumInputChannels());
    }

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels = 2;

    reverb.prepare (spec);
    chorus.prepare (spec);
    delay.prepare (sampleRate);
}

void BananaSplitAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BananaSplitAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
    #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
        #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
        #endif
    return true;
    #endif
}
#endif

void BananaSplitAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice (i)))
            voice->updateParameters (apvts);
    }

    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());

    // Fx
    if (static_cast<bool> (apvts.getRawParameterValue (BananaSplit::Reverb)->load()))
        reverb.process (buffer);

    if (static_cast<bool> (apvts.getRawParameterValue (BananaSplit::Chorus)->load()))
        chorus.process (buffer);

    if (static_cast<bool> (apvts.getRawParameterValue (BananaSplit::Delay)->load()))
        distortion.process (buffer);

    if (static_cast<bool> (apvts.getRawParameterValue (BananaSplit::Distortion)->load()))
        delay.process (buffer);
}

bool BananaSplitAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* BananaSplitAudioProcessor::createEditor()
{
    return new BananaSplitAudioProcessorEditor (*this);
}

void BananaSplitAudioProcessor::getStateInformation (juce::MemoryBlock& /*destData*/) {}

void BananaSplitAudioProcessor::setStateInformation (const void* /*data*/, int /*sizeInBytes*/) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BananaSplitAudioProcessor();
}
