/*
  ==============================================================================

    Knob_LookAndFeel.h
    Created: 3 Jun 2022 11:21:47am
    Author:  Jesús Valdez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Knob_LookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    Knob_LookAndFeel();
    ~Knob_LookAndFeel() override;
    
    void drawRotarySlider(juce::Graphics& g,
                          int x, int y,
                          int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;
    
private:
    
    juce::Image knobImage { juce::ImageFileFormat::loadFrom(BinaryData::knob_png, BinaryData::knob_pngSize) } ;
    
};
