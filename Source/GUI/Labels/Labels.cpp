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

void QuasoCompressorAudioProcessorEditor::setLabelText()
{
    //setting the text for each label
    inputDialLabel.setText("Input", juce::dontSendNotification);
    threshDialLabel.setText("Threshold", juce::dontSendNotification);
    ratioDialLabel.setText("Ratio", juce::dontSendNotification);
    attackDialLabel.setText("Attack", juce::dontSendNotification);
    releaseDialLabel.setText("Release", juce::dontSendNotification);
    limThreshDialLabel.setText("Threshold", juce::dontSendNotification);
    limReleaseDialLabel.setText("Release", juce::dontSendNotification);
    outputDialLabel.setText("Output", juce::dontSendNotification);
}
