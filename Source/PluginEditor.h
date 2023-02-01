/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/LookAndFeel/DialLAF.h"

//==============================================================================
/**
*/
class QuasoCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    QuasoCompressorAudioProcessorEditor (QuasoCompressorAudioProcessor&);
    ~QuasoCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    QuasoCompressorAudioProcessor& audioProcessor;

    //six dials attached to the six apvts parameters
    juce::Slider inputDial;
    juce::Slider threshDial;
    juce::Slider ratioDial;
    juce::Slider attackDial;
    juce::Slider releaseDial;
    juce::Slider outputDial;

    //using custom look and feel
    DialStyle customDialLAF;

    //shadows
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;

    //dials can be accessed faster by creating a vector
    std::vector<juce::Slider*> dials =
    {
        &inputDial,
        &threshDial,
        &ratioDial,
        &attackDial,
        &releaseDial,
        &outputDial
    };
    
    juce::Label inputDialLabel;
    juce::Label threshDialLabel;
    juce::Label ratioDialLabel;
    juce::Label attackDialLabel;
    juce::Label releaseDialLabel;
    juce::Label outputDialLabel;

    std::vector<juce::Label*> dialLabels =
    {
        &inputDialLabel,
        &threshDialLabel,
        &ratioDialLabel,
        &attackDialLabel,
        &releaseDialLabel,
        &outputDialLabel
    };

    //method to set some properties common to every silder and label
    void setCommonSliderProps(juce::Slider& slider);
    void setCommonLabelProps(juce::Label& label);





    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuasoCompressorAudioProcessorEditor)
};
