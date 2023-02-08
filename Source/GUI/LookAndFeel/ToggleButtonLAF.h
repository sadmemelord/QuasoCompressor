/*
  ==============================================================================

    ToggleButtonLAF.h
    Created: 8 Feb 2023 11:21:46am
    Author:  Utente

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PowerToggleLAF : public LookAndFeel_V4
{

public:


    void drawToggleButton
    (
        juce::Graphics& g,
        juce::ToggleButton& toggleButton,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown
    ) override;
};
