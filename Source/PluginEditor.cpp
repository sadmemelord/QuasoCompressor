/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
QuasoCompressorAudioProcessorEditor::QuasoCompressorAudioProcessorEditor (QuasoCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //setting up common slider and labels props
    for (int i = 0; i < dials.size(); i++)
    {
        setCommonSliderProps(*dials[i]);
        setCommonLabelProps(*dialLabels[i]);
        dialLabels[i]->attachToComponent(dials[i], false);
    }
    //unique slider properties like suffixes and colors
    setUniqueSliderProps();
    //text for each label
    setLabelText();
    //toggle button properties
    setButtonProps(compBypassButton);

    //shadow properties are the same for each slider
    for (int i = 0; i < dials.size(); i++)
    {
        setShadowProps(*dials[i]);
    }

    //group properties
    for (int i = 0; i < groups.size(); i++)
    {
        setGroupProps(*groups[i]);
    }

    //methods to attach sliders and buttons the apvts parameters
    attachSliders();
    attachButtons();

    setSize(1000, 500);

    //the windows can be resized by mantaining the dafault 2:1 aspect ratio and only by 25% bigger or smaller
    juce::AudioProcessorEditor::setResizable(true,true);
    juce::AudioProcessorEditor::setResizeLimits(getWidth(), getHeight(), getWidth() * 1.25, getHeight() * 1.25);
    juce::AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0);
}

QuasoCompressorAudioProcessorEditor::~QuasoCompressorAudioProcessorEditor()
{
    for (auto& dial : dials)
    {
        dial->setLookAndFeel(nullptr);
    }

    //the vector is cleared and then shrinked to size zero inside the destructor
    dials.clear();
    dials.shrink_to_fit();
}

//==============================================================================
void QuasoCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    //the background is filled with a vertical gradient
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(40, 42, 50).darker(0.50f), getHeight(),
                      juce::Colour::fromRGB(40,42,50).brighter(0.05f),getHeight()*0.4f));
    g.fillRect(getLocalBounds());
    
}

void QuasoCompressorAudioProcessorEditor::resized()
{
    //useful variables for placing the components in the gui
    auto dialSize = getWidth() * 0.18;
    auto mainLeftMargin = getWidth() * 0.32;
    auto leftMargin = getWidth() * 0.05;
    auto secondRowHeight = 1.3;
    auto limiterMargin = 1.5;
    auto buttonSize = 50;

    //I/O section GUI
    inputDial.setBounds(leftMargin, 65, dialSize, dialSize);
    outputDial.setBounds(leftMargin, inputDial.getY() + inputDial.getHeight() * secondRowHeight, dialSize, dialSize);

    ioGroup.setBounds(inputDial.getX(), inputDial.getY() * 0.1, inputDial.getWidth(),
                      inputDial.getY() + inputDial.getHeight() * 2.35);


    //Compressor section GUI
    threshDial.setBounds(mainLeftMargin, 65, dialSize, dialSize);
    ratioDial.setBounds(threshDial.getX() + threshDial.getWidth(), 65, dialSize, dialSize);
    attackDial.setBounds(threshDial.getX(), outputDial.getY(), dialSize, dialSize);
    releaseDial.setBounds(ratioDial.getX(), outputDial.getY(),  dialSize, dialSize);

    compressorGroup.setBounds(threshDial.getX(), threshDial.getY() * 0.1, threshDial.getWidth() * 2.0,
                              threshDial.getY() + threshDial.getHeight() * 2.35);

    compBypassButton.setBounds(releaseDial.getX() - 26, compressorGroup.getBottom() - 55, buttonSize, buttonSize);


    //Limiter Section GUI
    limThreshDial.setBounds(ratioDial.getX() + ratioDial.getWidth() * limiterMargin, inputDial.getY(), dialSize, dialSize);
    limReleaseDial.setBounds(limThreshDial.getX(), inputDial.getY() +limThreshDial.getHeight()*secondRowHeight, dialSize, dialSize);

    limiterGroup.setBounds(limThreshDial.getX(), limThreshDial.getY() * 0.1,
                        limThreshDial.getWidth(), limThreshDial.getY() + limThreshDial.getHeight() * 2.35);


}
