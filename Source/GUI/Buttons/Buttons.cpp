/*
  ==============================================================================

    Buttons.cpp
    Created: 7 Feb 2023 8:21:22pm
    Author:  sadmemelord

  ==============================================================================
*/

#include "../../PluginEditor.h"

void QuasoCompressorAudioProcessorEditor::setButtonProps(juce::ToggleButton& button)
{
    //setting up group properties
    addAndMakeVisible(button);
    button.setLookAndFeel(&buttonLAF);
}


void QuasoCompressorAudioProcessorEditor::attachButtons()
{
    //attaching the buttons to the related apvts parameters
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    compBypassAttach = std::make_unique<ButtonAttachment>(audioProcessor.apvts, compBypassID, compBypassButton);
}