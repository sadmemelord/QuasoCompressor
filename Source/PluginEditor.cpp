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

    //setting the label text
    inputDialLabel.setText("Input", juce::dontSendNotification);
    threshDialLabel.setText("Threshold", juce::dontSendNotification);
    ratioDialLabel.setText("Ratio", juce::dontSendNotification);
    attackDialLabel.setText("Attack", juce::dontSendNotification);
    releaseDialLabel.setText("Release", juce::dontSendNotification);
    outputDialLabel.setText("Output", juce::dontSendNotification);

    //setting the slider properties is called for every slider in the vector
    for (int i = 0; i < dials.size(); i++)
    {
        setCommonSliderProps(*dials[i]);
        setCommonLabelProps(*dialLabels[i]);
        dialLabels[i]->attachToComponent(dials[i], false);
    }

   

    setSize(1000, 500);

    //the windows can be resized by mantaining the dafault 2:1 aspect ratio and only by 25% bigger or smaller
    juce::AudioProcessorEditor::setResizable(true,true);
    juce::AudioProcessorEditor::setResizeLimits(getWidth() * 0.75, getHeight() * 0.75, getWidth() * 1.25, getHeight() * 1.25);
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
    auto dialSize = getWidth() * 0.15;
    auto mainLeftMargin = getWidth() * 0.25;
    auto leftMargin = getWidth() * 0.02;
    auto secondRowHeight = 1.5;

    ////first row of GUI with input, thresh and ratio
    //juce::FlexBox flexboxRowOne;
    //flexboxRowOne.flexDirection = juce::FlexBox::Direction::row;
    //flexboxRowOne.flexWrap = juce::FlexBox::Wrap::noWrap;
    //flexboxRowOne.alignContent = juce::FlexBox::AlignContent::center;
    //
    //juce::Array<juce::FlexItem> itemArrayRowOne;
    //itemArrayRowOne.add(juce::FlexItem(dialSize, dialSize, inputDial).withMargin(juce::FlexItem::Margin(0, 0, 0, leftMargin)));
    //itemArrayRowOne.add(juce::FlexItem(dialSize, dialSize, threshDial).withMargin(juce::FlexItem::Margin(0, 0, 0, mainLeftMargin)));
    //itemArrayRowOne.add(juce::FlexItem(dialSize, dialSize, ratioDial).withMargin(juce::FlexItem::Margin(0, 0, 0, leftMargin)));
    //
    //flexboxRowOne.items = itemArrayRowOne;
    //flexboxRowOne.performLayout(getLocalBounds().withY(0).withHeight(getHeight() * 0.5));
    //
    ////second row of GUI with output, attack and release
    //juce::FlexBox flexboxRowTwo;
    //flexboxRowTwo.flexDirection = juce::FlexBox::Direction::row;
    //flexboxRowTwo.flexWrap = juce::FlexBox::Wrap::noWrap;
    //flexboxRowTwo.alignContent = juce::FlexBox::AlignContent::center;
    // 
    //juce::Array<juce::FlexItem> itemArrayRowTwo;
    //itemArrayRowTwo.add(juce::FlexItem(dialSize, dialSize, outputDial).withMargin(juce::FlexItem::Margin(0, 0, 0, leftMargin)));
    //itemArrayRowTwo.add(juce::FlexItem(dialSize, dialSize, attackDial).withMargin(juce::FlexItem::Margin(0, 0, 0, mainLeftMargin)));
    //itemArrayRowTwo.add(juce::FlexItem(dialSize, dialSize, releaseDial).withMargin(juce::FlexItem::Margin(0, 0, 0, leftMargin)));
    // 
    //flexboxRowTwo.items = itemArrayRowTwo;
    //flexboxRowTwo.performLayout(getLocalBounds().withY(getHeight() * 0.5).withHeight(getHeight()*0.5));
    inputDial.setBounds(leftMargin, 75, dialSize, dialSize);
    threshDial.setBounds(mainLeftMargin, 75, dialSize, dialSize);
    ratioDial.setBounds(threshDial.getX() + threshDial.getWidth(), 75, dialSize, dialSize);

    outputDial.setBounds(leftMargin, inputDial.getY() + inputDial.getHeight() *secondRowHeight, dialSize, dialSize);
    attackDial.setBounds(threshDial.getX(), outputDial.getY(), dialSize, dialSize);
    releaseDial.setBounds(ratioDial.getX(), outputDial.getY(),  dialSize, dialSize);


}
