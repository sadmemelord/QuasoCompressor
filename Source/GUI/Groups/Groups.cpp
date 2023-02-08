/*
  ==============================================================================

    Groups.cpp
    Created: 6 Feb 2023 7:43:46pm
    Author:  Utente

  ==============================================================================
*/

#include "../../PluginEditor.h"

void QuasoCompressorAudioProcessorEditor::setGroupProps(juce::GroupComponent& group)
{
    //setting group properties
    addAndMakeVisible(group);
    group.setColour(group.outlineColourId, juce::Colours::darkgrey);
    ioGroup.setText("I/O");
    compressorGroup.setText("Compressor");
    limiterGroup.setText("Limiter");
}
