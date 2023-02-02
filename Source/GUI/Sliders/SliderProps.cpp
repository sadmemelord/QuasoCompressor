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

    //setting colours based on the custom look and feel
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::trackColourId, 
                     slider.findColour(juce::Slider::ColourIds::rotarySliderOutlineColourId).brighter(0.2));
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke.darker(1));
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, 
                     slider.findColour(juce::Slider::ColourIds::rotarySliderOutlineColourId).brighter(0.15));
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::cornflowerblue.darker(0.3));

    slider.setLookAndFeel(&customDialLAF);

    //setting shadow properties based on the juce::shadowdrop
    shadowProperties.radius = 25;
    shadowProperties.offset = juce::Point<int>(0,0);
    shadowProperties.colour = juce::Colours::black.brighter(0.05);
    dialShadow.setShadowProperties(shadowProperties);
    slider.setComponentEffect(&dialShadow);

}

void QuasoCompressorAudioProcessorEditor::attachSliders()
{
    //method to attach dials to apvts
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    inputAttach = std::make_unique<SliderAttachment>(audioProcessor.apvts, inputID, inputDial);
    threshAttach = std::make_unique<SliderAttachment>(audioProcessor.apvts, threshID, threshDial);
    ratioAttach = std::make_unique<SliderAttachment>(audioProcessor.apvts, ratioID, ratioDial);
    attackAttach = std::make_unique<SliderAttachment>(audioProcessor.apvts, attackID, attackDial);
    releaseAttach = std::make_unique<SliderAttachment>(audioProcessor.apvts, releaseID, releaseDial);
    outputAttach = std::make_unique<SliderAttachment>(audioProcessor.apvts, outputID, outputDial);

}

void QuasoCompressorAudioProcessorEditor::setCommonLabelProps(juce::Label& label)
{
    //setting properties common to every slider
    addAndMakeVisible(label);
    label.setFont(juce::Font("Helvetica", 16.0f, juce::Font::FontStyleFlags::bold));
    label.setJustificationType(juce::Justification::centred);
}

