/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
QuasoCompressorAudioProcessor::QuasoCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), 
                       //the apvts has to be constructed
                       apvts(*this,nullptr, "PARAMETERS", createParameterLayout())
                  
#endif
{
    //every paramaters needs a listener inside the constructor of the main AudioProcessor class
    //everything the listener receives a changes from its parameter ID the parameterChanged method is called
    apvts.addParameterListener(inputID, this);
    apvts.addParameterListener(compBypassID, this);
    apvts.addParameterListener(threshID, this);
    apvts.addParameterListener(ratioID, this);
    apvts.addParameterListener(attackID, this);
    apvts.addParameterListener(releaseID, this);
    //apvts.addParameterListener(limBypassID, this);
    apvts.addParameterListener(limThreshID, this);
    apvts.addParameterListener(limReleaseID, this);
    apvts.addParameterListener(outputID, this);
}

QuasoCompressorAudioProcessor::~QuasoCompressorAudioProcessor()
{ 
    //the listener for each parameter has to be removed in the destructor
    apvts.removeParameterListener(inputID, this);
    apvts.removeParameterListener(compBypassID, this);
    apvts.removeParameterListener(threshID, this);
    apvts.removeParameterListener(ratioID, this);
    apvts.removeParameterListener(attackID, this);
    apvts.removeParameterListener(releaseID, this);
    //apvts.removeParameterListener(limBypassID, this);
    apvts.removeParameterListener(limThreshID, this);
    apvts.removeParameterListener(limReleaseID, this);
    apvts.removeParameterListener(outputID, this);

}

//the apvts' methods needs to be defined
juce::AudioProcessorValueTreeState::ParameterLayout QuasoCompressorAudioProcessor::createParameterLayout()
{
    //parameters of the apvts are stored in a vector as unique_pointers to RangedAudioParamter
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //attack and release parameters need to be skewed and not linear
    juce::NormalisableRange<float> attackRange = juce::NormalisableRange<float>(0.0f, 200.0f, 1.0f);
    attackRange.setSkewForCentre(50.0f);

    juce::NormalisableRange<float> releaseRange = juce::NormalisableRange<float>( 5.0f, 5000.0f, 1.0f);
    releaseRange.setSkewForCentre(160.0f);

    juce::NormalisableRange<float> limReleaseRange = juce::NormalisableRange<float>(1.0f, 1000.0f, 1.0f);
    releaseRange.setSkewForCentre(250.0f);

    //parameters are created
    auto pInput = std::make_unique<juce::AudioParameterFloat>(inputID, inputName, -60.0f, 24.0f, 0.0f);
    auto pBypass = std::make_unique<juce::AudioParameterBool>(compBypassID, compBypassName, false);
    auto pThresh = std::make_unique<juce::AudioParameterFloat>(threshID, threshName, -60.0f, 12.0f, 0.0f);
    auto pRatio = std::make_unique<juce::AudioParameterFloat>(ratioID, ratioName, 1.0f, 20.0f, 1.0f);
    auto pAttack = std::make_unique<juce::AudioParameterFloat>(attackID, attackName, attackRange, 50.0f);
    auto pRelease = std::make_unique<juce::AudioParameterFloat>(releaseID, releaseName, releaseRange, 160.0f);
    //auto pLimBypass = std::make_unique<juce::AudioParameterBool>(limBypassID, limBypassName, false);
    auto pLimThresh = std::make_unique<juce::AudioParameterFloat>(limThreshID, limThreshName, -60.0f, 0.0f, 160.0f);
    auto pLimRelease = std::make_unique<juce::AudioParameterFloat>(limReleaseID, limReleaseName, limReleaseRange, 250.0f);
    auto pOutput = std::make_unique<juce::AudioParameterFloat>(outputID, outputName, -60.0f, 24.0f, 0.0f);
     
    //different type of parameters like floats or selection are pushed into the params vector
    params.push_back(std::move(pInput));
    params.push_back(std::move(pBypass));
    params.push_back(std::move(pThresh));
    params.push_back(std::move(pRatio));
    params.push_back(std::move(pAttack)); 
    params.push_back(std::move(pRelease));
    //params.push_back(std::move(pLimBypass));
    params.push_back(std::move(pLimThresh));
    params.push_back(std::move(pLimRelease));
    params.push_back(std::move(pOutput));


    return { params.begin() , params.end() };


}

void QuasoCompressorAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    updateParameters();
}

void QuasoCompressorAudioProcessor::updateParameters()
{
    //the load method is needed because the raw parameters are atomic
    inputModule.setGainDecibels(apvts.getRawParameterValue(inputID)->load());
    customCompressorModule.setBypass(apvts.getRawParameterValue(compBypassID)->load());
    customCompressorModule.setThreshold(apvts.getRawParameterValue(threshID)->load());
    customCompressorModule.setRatio(apvts.getRawParameterValue(ratioID)->load());
    customCompressorModule.setAttack(apvts.getRawParameterValue(attackID)->load());
    customCompressorModule.setRelease(apvts.getRawParameterValue(releaseID)->load());
    limiterModule.setThreshold(apvts.getRawParameterValue(limThreshID)->load());
    limiterModule.setRelease(apvts.getRawParameterValue(limReleaseID)->load());
    outputModule.setGainDecibels(apvts.getRawParameterValue(outputID)->load());

}



//==============================================================================
const juce::String QuasoCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool QuasoCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool QuasoCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool QuasoCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double QuasoCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int QuasoCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int QuasoCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void QuasoCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String QuasoCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void QuasoCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void QuasoCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();

    //prepare dsp modules for processing
    inputModule.prepare(spec);
    inputModule.setRampDurationSeconds(0.02);

    outputModule.setRampDurationSeconds(0.02); 
    outputModule.prepare(spec);

    customCompressorModule.prepare(spec);

    limiterModule.prepare(spec);
   
    updateParameters();
}

void QuasoCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool QuasoCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void QuasoCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto block = juce::dsp::AudioBlock<float>(buffer);

    //process DSP modules
    inputModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    customCompressorModule.process(buffer);
    limiterModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    outputModule.process(juce::dsp::ProcessContextReplacing<float>(block));


}

//==============================================================================
bool QuasoCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* QuasoCompressorAudioProcessor::createEditor()
{
    return new QuasoCompressorAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void QuasoCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    //method to save the vst parameters
    juce::MemoryOutputStream    stream(destData, false);
    apvts.state.writeToStream(stream);
}

void QuasoCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //method to restore the vst parameters
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));

    if (tree.isValid())
    {
        apvts.state = tree;
    }

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new QuasoCompressorAudioProcessor();
}
