/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/LookAndFeel/DialLAF.h"
#include "GUI/LookAndFeel/ToggleButtonLAF.h"

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
    //This reference is provided as a quick way for your editor to
    //access the processor object that created it.
    QuasoCompressorAudioProcessor& audioProcessor;

    //dials to attach to the apvts parameters
    juce::Slider inputDial;
    juce::Slider threshDial;
    juce::Slider ratioDial;
    juce::Slider attackDial;
    juce::Slider releaseDial;
    juce::Slider limThreshDial;
    juce::Slider limReleaseDial;
    juce::Slider outputDial;

    //using custom look and feel for dials and button from ViatorDSP style sheet
    DialStyle customDialLAF;
    PowerToggleLAF buttonLAF;

    //shadows properties
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
    
    //labels for each dial
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

    //three groups for a cleaner GUI look with
    // I/O, Compressor and Limiter section
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

    //toggle button to bypass the compressor
    juce::ToggleButton compBypassButton;

    //method to set some properties common to every silders, labels, groups and button
    void setCommonSliderProps(juce::Slider& slider);
    void setCommonLabelProps(juce::Label& label);
    void setShadowProps(juce::Slider& slider);
    void setGroupProps(juce::GroupComponent& group);
    void setButtonProps(juce::ToggleButton& button);
    
    //method to set unique properties
    void setUniqueSliderProps();
    void setLabelText();

    //setting up attachments
    using ButtonAttachment = std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>;
    ButtonAttachment compBypassAttach;

    using SliderAttachment = std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>;
    SliderAttachment inputAttach;
    SliderAttachment threshAttach;
    SliderAttachment ratioAttach;
    SliderAttachment attackAttach;
    SliderAttachment releaseAttach;
    SliderAttachment limThreshAttach;
    SliderAttachment limReleaseAttach;
    SliderAttachment outputAttach;

    //method to attach sliders to the apvts
    void attachSliders();
    void attachButtons();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuasoCompressorAudioProcessorEditor)
};
