/*
  ==============================================================================

    ToggleButtonLAF.cpp
    Created: 8 Feb 2023 11:21:46am
    Author:  Utente

  ==============================================================================
*/

#include "ToggleButtonLAF.h"

void PowerToggleLAF::drawToggleButton
(
    juce::Graphics& g,
    juce::ToggleButton& toggleButton,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown
)
{
    Path button;

    auto bounds = toggleButton.getLocalBounds();

    auto size = jmin(bounds.getWidth(), bounds.getHeight()) - 6;
    auto r = bounds.withSizeKeepingCentre(size, size).toFloat();

    float ang = 30.f;

    size -= 9;


    button.addCentredArc(r.getCentreX(),
        r.getCentreY(),
        size * 0.25,
        size * 0.25,
        0.f,
        degreesToRadians(ang),
        degreesToRadians(360.f - ang),
        true);

    button.startNewSubPath(r.getCentreX(), r.getY() + r.getHeight() * 0.21);
    button.lineTo(r.getCentre());

    PathStrokeType pst(2.5f, PathStrokeType::JointStyle::curved);

    auto color =
        toggleButton.getToggleState() ? toggleButton.findColour(juce::ToggleButton::tickDisabledColourId) : toggleButton.findColour(juce::ToggleButton::tickColourId);

    g.setColour(color);
    g.strokePath(button, pst);
}
