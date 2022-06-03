/*
  ==============================================================================

    Knob_LookAndFeel.cpp
    Created: 3 Jun 2022 11:21:47am
    Author:  Jesús Valdez

  ==============================================================================
*/

#include "Knob_LookAndFeel.h"

Knob_LookAndFeel::Knob_LookAndFeel(){}

Knob_LookAndFeel::~Knob_LookAndFeel(){}

void Knob_LookAndFeel::drawRotarySlider(juce::Graphics& g,
                                        int x, int y,
                                        int width, int height,
                                        float sliderPosProportional,
                                        [[maybe_unused]] float rotaryStartAngle,
                                        [[maybe_unused]] float rotaryEndAngle,
                                        [[maybe_unused]] juce::Slider& slider)
{
    auto radius = (float) juce::jmin (width / 2, height / 2);
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    
    float stopValue = 0.7f;
    float rotation = stopValue * juce::MathConstants<float>::twoPi * (sliderPosProportional - 0.5f);
    knobImage = knobImage.rescaled((int)radius * 2,
                                   (int)radius * 2,
                                   juce::Graphics::ResamplingQuality::highResamplingQuality);
    
    g.drawImageTransformed(knobImage, juce::AffineTransform::rotation(rotation,
                                                                      static_cast<float>(knobImage.getWidth() / 2),
                                                                      static_cast<float>(knobImage.getHeight() / 2)).translated(rx, ry));
}
