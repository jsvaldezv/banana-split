/*
  ==============================================================================

    Helpers_DSP.h
    Created: 18 May 2022 1:37:28am
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once

namespace BananaSplit
{
    enum OscType
    {
        Sin = 0,
        Square = 1,
        Triangle = 2,
        Saw = 3,
    };

    const static int NumVoices = 5;

    const static int MaxBufferDelaySize = 192000;

    const static float SmoothCoefficient_Fine = 0.002f;

    inline float linearInterpolation (float v0, float v1, float t)
    {
        return (1 - t) * v0 + t * v1;
    }
}
