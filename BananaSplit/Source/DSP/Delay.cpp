/*
  ==============================================================================

    Delay.cpp
    Created: 23 May 2022 4:18:52pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "Delay.h"

void Delay::prepare (double inSampleRate)
{
    sampleRate = static_cast<float> (inSampleRate);
}

void Delay::reset()
{
    juce::zeromem (circularBuffer, (sizeof (double) * BananaSplit::MaxBufferDelaySize));
}

void Delay::process (juce::AudioBuffer<float>& inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float in = inBuffer.getSample (channel, i);
            inBuffer.setSample (channel, i, getDelayedSample (in, channel));
        }
    }
}

float Delay::getDelayedSample (float inSample, int inChannel)
{
    smoothTime[inChannel] = smoothTime[inChannel] - BananaSplit::SmoothCoefficient_Fine * (smoothTime[inChannel] - time);
    smoothFeedback[inChannel] = smoothFeedback[inChannel] - BananaSplit::SmoothCoefficient_Fine * (smoothFeedback[inChannel] - feedback);
    smoothWet[inChannel] = smoothWet[inChannel] - BananaSplit::SmoothCoefficient_Fine * (smoothWet[inChannel] - wet);
    smoothDry[inChannel] = smoothDry[inChannel] - BananaSplit::SmoothCoefficient_Fine * (smoothDry[inChannel] - dry);

    delayTimeInSamples[inChannel] = (smoothTime[inChannel] * sampleRate);
    const float sample = getInterpolatedSample (delayTimeInSamples[inChannel], inChannel);

    circularBuffer[inChannel][delayIndex[inChannel]] = inSample + (feedbackSample[inChannel] * smoothFeedback[inChannel]);
    feedbackSample[inChannel] = sample;

    float out = (inSample * smoothDry[inChannel] + sample * smoothWet[inChannel]);

    delayIndex[inChannel]++;

    if (delayIndex[inChannel] >= BananaSplit::MaxBufferDelaySize)
        delayIndex[inChannel] = delayIndex[inChannel] - BananaSplit::MaxBufferDelaySize;

    return out;
}

float Delay::getInterpolatedSample (float inDelayTimeInSamples, int channel)
{
    float readPosition = delayIndex[channel] - inDelayTimeInSamples;

    if (readPosition < 0.0f)
        readPosition = readPosition + BananaSplit::MaxBufferDelaySize;

    index_y0[channel] = (int) readPosition - 1;

    if (index_y0[channel] <= 0)
        index_y0[channel] = index_y0[channel] + BananaSplit::MaxBufferDelaySize;

    index_y1[channel] = (int) readPosition;

    if (index_y1[channel] > BananaSplit::MaxBufferDelaySize)
        index_y1[channel] = index_y1[channel] - BananaSplit::MaxBufferDelaySize;

    sample_y0[channel] = circularBuffer[channel][index_y0[channel]];
    sample_y1[channel] = circularBuffer[channel][index_y1[channel]];
    t[channel] = readPosition - (int) readPosition;
    outSample[channel] = BananaSplit::linearInterpolation (sample_y0[channel], sample_y1[channel], t[channel]);

    return outSample[channel];
}
