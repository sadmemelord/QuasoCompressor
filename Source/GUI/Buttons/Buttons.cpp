/*
  ==============================================================================

    Buttons.cpp
    Created: 7 Feb 2023 8:21:22pm
    Author:  Utente

  ==============================================================================
*/

#include "../../PluginEditor.h"

void QuasoCompressorAudioProcessorEditor::setButtonProps(juce::ToggleButton& button)
{
    addAndMakeVisible(button);
    button.setLookAndFeel(&buttonLAF);
}


void QuasoCompressorAudioProcessorEditor::attachButtons()
{
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    compBypassAttach = std::make_unique<ButtonAttachment>(audioProcessor.apvts, compBypassID, compBypassButton);
}