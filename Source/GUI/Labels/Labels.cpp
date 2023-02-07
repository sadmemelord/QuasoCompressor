/*
  ==============================================================================

    Labels.cpp
    Created: 7 Feb 2023 8:23:29pm
    Author:  Utente

  ==============================================================================
*/

#include "../../PluginEditor.h"

void QuasoCompressorAudioProcessorEditor::setCommonLabelProps(juce::Label& label)
{
    //setting properties common to every slider
    addAndMakeVisible(label);
    label.setFont(juce::Font("Helvetica", 16.0f, juce::Font::FontStyleFlags::bold));
    label.setJustificationType(juce::Justification::centred);
}
