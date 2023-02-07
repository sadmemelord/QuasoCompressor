/*
  ==============================================================================

    CustomCompressor.cpp
    Created: 7 Feb 2023 4:07:01pm
    Author:  Utente

  ==============================================================================
*/

#include "CustomCompressor.h"

CustomCompressor::CustomCompressor()
{

}
   

void CustomCompressor::prepare(juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
}


void CustomCompressor::setThreshold(float newThresh)
{
    _thresh = newThresh;
}


void CustomCompressor::setRatio(float newRatio)
{
    _ratio = newRatio;
}


void CustomCompressor::setAttack(float newAttack)
{
    _attack = newAttack / 1000.0f;
}

void CustomCompressor::setRelease(float newRelease)
{
    _release = newRelease / 1000.0f;
}

void CustomCompressor::setBypass(bool newBypass)
{
    _isBypassed = newBypass;
}