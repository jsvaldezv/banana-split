/*
  ==============================================================================

    Delay.h
    Created: 23 May 2022 4:18:52pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include "../Helpers/DSP.h"
#include <JuceHeader.h>

class Delay
{
public:

    void prepare (double inSampleRate);

    void reset();

    void process (juce::AudioBuffer<float>& inBuffer);

    float getDelayedSample (float inSample, int inChannel);

    float getInterpolatedSample (float inDelayTimeInSamples, int channel);

private:

    float sampleRate;

    // Parameters
    float time { 0.5f };
    float smoothTime[2] { 0.0f };

    float feedback { 0.7f };
    float smoothFeedback[2] { 0.0f };

    float wet { 0.5f };
    float smoothWet[2] { 0.0f };

    float dry { 0.5f };
    float smoothDry[2] { 0.0f };

    // Circular buffer
    float circularBuffer[2][BananaSplit::MaxBufferDelaySize] = {};
    float feedbackSample[2] { 0 };
    float delayTimeInSamples[2] { 0 };
    int delayIndex[2] { 0 };

    // Interpolation
    int index_y0[2] { 0 };
    int index_y1[2] { 0 };
    float sample_y0[2] { 0.0f };
    float sample_y1[2] { 0.0f };
    float t[2] { 0.0f };
    float outSample[2] { 0.0 };
};
