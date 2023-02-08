/*
  ==============================================================================

    DialLAF.h
    Created: 1 Feb 2023 5:32:48pm
    Author:  sadmemelord

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DialStyle: public juce::LookAndFeel_V4
{
public:
    DialStyle();
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

private:
    float sliderWidth;
};