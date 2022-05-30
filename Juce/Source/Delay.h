/*
  ==============================================================================

    Delay.h
    Created: 23 May 2022 4:18:52pm
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

const static int maxBufferDelaySize = 192000;
const static float SmoothCoefficient_Fine = 0.002f;

inline float linearInterpolation(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

class Delay
{
public:
    
    Delay();
    
    ~Delay();
    
    void prepare(double inSampleRate);
    
    void reset();
    
    void process(juce::AudioBuffer<float>& inBuffer);
    
    float getDelayedSample(float inSample, int inChannel);

    float getInterpolatedSample(float inDelayTimeInSamples, int channel);
    
private:
    
    // GENERAL
    float sampleRate;
    
    // PARAMETERS
    float time                      {0.5f};
    float smoothTime[2]             {0.0f};
    
    float feedback                  {0.7f};
    float smoothFeedback[2]         {0.0f};
    
    float wet                       {0.5f};
    float smoothWet[2]              {0.0f};
    
    float dry                       {0.5f};
    float smoothDry[2]              {0.0f};
    
    // CIRCULAR BUFFER
    float circularBuffer[2][maxBufferDelaySize] = { };
    float feedbackSample[2]         {0};
    float delayTimeInSamples[2]     {0};
    int delayIndex[2]               {0};
    
    // INTERPOLATION
    int index_y0[2]                 {0};
    int index_y1[2]                 {0};
    float sample_y0[2]              {0.0f};
    float sample_y1[2]              {0.0f};
    float t[2]                      {0.0f};
    float outSample[2]              {0.0};
};
