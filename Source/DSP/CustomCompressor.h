/*
  ==============================================================================

    CustomCompressor.h
    Created: 7 Feb 2023 4:07:01pm
    Author:  Utente

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomCompressor
{

public:
    CustomCompressor();

    void prepare(juce::dsp::ProcessSpec& spec) noexcept;

    void process(juce::AudioBuffer<float>& buffer) noexcept
    {
        //the process method is defined in the header file
        //because it is passed through the translation unit
        //and has a better chance of being optimized
        //bypassing the dsp

        if (_isBypassed == true)
            return;

        auto data = buffer.getArrayOfWritePointers();

        //sample/channel loop
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {

            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                data[ch][sample] = processSample(data[ch][sample]);
            }
        }
    }

    float processSample(float inputValue)
    {
        //attack and release variable from Eric Tarr Hack Audio
        auto alphaAttack = std::exp((std::log(9) * -1.0) / (_sampleRate * _attack));
        auto alphaRelease = std::exp((std::log(9) * -1.0) / (_sampleRate * _release));

        const auto input = inputValue;

        //input dividedin unipolar (absolute value) and dB values
        auto input_uni = std::abs(input); //maybe remove std
        auto input_dB = juce::Decibels::gainToDecibels(input_uni / 1.0);

        //checking that no value in dB are negative infinity
        if (input_dB < -96)
        { 
            input_dB = -96;
        }

        if (input_dB > _thresh)
        {
            _gainSC = _thresh + (input_dB - _thresh) / _ratio;
        }

        else
        {
            _gainSC = input_dB;
        }

        _gainChange_dB = _gainSC - input_dB;

        if (_gainChange_dB < _gainSmoothPrevious)
        {
            _gainSmooth = ((1.0 - alphaAttack) * _gainChange_dB) + (alphaAttack * _gainSmoothPrevious);
            _currentSignal = _gainSmooth;
        }

        else
        {
            _gainSmooth = ((1.0 - alphaRelease) * _gainChange_dB) + (alphaRelease * _gainSmoothPrevious);
            _currentSignal = _gainSmooth;

        }

        auto output = input * juce::Decibels::decibelsToGain(_gainSmooth);
        _gainSmoothPrevious = _gainSmooth;

        //output signal
        return output;

    }

    void setThreshold(float newThresh);
    void setRatio(float newRatio);
    void setAttack(float newAttack);
    void setRelease(float newRelease);
    void setBypass(bool newBypass);


private:
    
    //compressor parameters
    float _thresh = 0.0f;
    float _ratio = 1.0f;
    float _attack = 50.0f / 1000.0f ;
    float _release = 160.0f / 1000.0f;
    bool _isBypassed = false;

    //sample rate
    float _sampleRate = 44100.0f;

    //gain sidechain
    float _gainSC = 0.0f;

    //gain smooth
    float _gainSmooth = 0.0f;

    //gain smooth previous
    float _gainSmoothPrevious = 0.0f;

    //current signal
    float _currentSignal = 0.0f;

    //gain change in decibels
    float _gainChange_dB = 0.0f;
   


};