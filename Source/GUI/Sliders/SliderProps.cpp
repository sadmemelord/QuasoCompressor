/*
  ==============================================================================

    SliderProps.cpp
    Created: 1 Feb 2023 11:41:19am
    Author:  Utente

  ==============================================================================
*/

#include "../../PluginEditor.h"

void QuasoCompressorAudioProcessorEditor::setCommonSliderProps(juce::Slider& slider)
{
    //setting properties common to every slider
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 36);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke.darker(0.75));
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, 
                     slider.findColour(juce::Slider::ColourIds::rotarySliderOutlineColourId).brighter(0.2));
    slider.setLookAndFeel(&customDialLAF);

    shadowProperties.radius = 25;
    shadowProperties.offset = juce::Point<int>(0,0);
    shadowProperties.colour = juce::Colours::black.brighter(0.1);
    dialShadow.setShadowProperties(shadowProperties);
    slider.setComponentEffect(&dialShadow);

}

void QuasoCompressorAudioProcessorEditor::setCommonLabelProps(juce::Label& label)
{
    //setting properties common to every slider
    addAndMakeVisible(label);
    label.setFont(juce::Font("Helvetica", 16.0f, juce::Font::FontStyleFlags::bold));
    label.setJustificationType(juce::Justification::centred);
}

