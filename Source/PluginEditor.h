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
    juce::Slider limThreshDial;
    juce::Slider limReleaseDial;
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
        &limThreshDial,
        &limReleaseDial,
        &outputDial
    };
    
    //labels
    juce::Label inputDialLabel;
    juce::Label threshDialLabel;
    juce::Label ratioDialLabel;
    juce::Label attackDialLabel;
    juce::Label releaseDialLabel;
    juce::Label limThreshDialLabel;
    juce::Label limReleaseDialLabel;
    juce::Label outputDialLabel;

    //labels vector
    std::vector<juce::Label*> dialLabels =
    {
        &inputDialLabel,
        &threshDialLabel,
        &ratioDialLabel,
        &attackDialLabel,
        &releaseDialLabel,
        &limThreshDialLabel,
        &limReleaseDialLabel,
        &outputDialLabel
    };

    //groups
    juce::GroupComponent ioGroup;
    juce::GroupComponent compressorGroup;
    juce::GroupComponent limiterGroup;

    //groups vector
    std::vector<juce::GroupComponent*> groups =
    {
        &ioGroup,
        &compressorGroup,
        &limiterGroup
    };

    //buttons
    juce::ToggleButton compBypassButton;
    juce::ToggleButton limBypassButton;

    //buttons vector
    std::vector<juce::ToggleButton*> buttons =
    {
        &compBypassButton,
        &limBypassButton
    };


    //method to set some properties common to every silders, labels, groups and buttons
    void setCommonSliderProps(juce::Slider& slider);
    void setCommonLabelProps(juce::Label& label);
    void setGroupProps(juce::GroupComponent& group);
    void setButtonProps(juce::ToggleButton& button);

    //setting up attachment
    using Attachment = std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>;

    Attachment inputAttach;
    Attachment threshAttach;
    Attachment ratioAttach;
    Attachment attackAttach;
    Attachment releaseAttach;
    Attachment limThreshAttach;
    Attachment limReleaseAttach;
    Attachment outputAttach;

    //method to attach sliders to the apvts
    void attachSliders();






    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuasoCompressorAudioProcessorEditor)
};
