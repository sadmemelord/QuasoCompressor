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
    apvts.addParameterListener("input", this);
    apvts.addParameterListener("thresh", this);
    apvts.addParameterListener("ratio", this);
    apvts.addParameterListener("attack", this);
    apvts.addParameterListener("release", this);
    apvts.addParameterListener("output", this);
}

QuasoCompressorAudioProcessor::~QuasoCompressorAudioProcessor()
{ 
    //the listener for each parameter has to be removed in the destructor
    apvts.removeParameterListener("input", this);
    apvts.removeParameterListener("thresh", this);
    apvts.removeParameterListener("ratio", this);
    apvts.removeParameterListener("attack", this);
    apvts.removeParameterListener("release", this);
    apvts.removeParameterListener("output", this);

}

//the apvts' methods needs to be defined
juce::AudioProcessorValueTreeState::ParameterLayout QuasoCompressorAudioProcessor::createParameterLayout()
{
    //parameters of the apvts are stored in a vector as unique_pointers to RangedAudioParamter
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //attack and release parameters need to be skewed and not linear
    juce::NormalisableRange<float> attackRange = juce::NormalisableRange<float>(0.0f, 200.0f, 1.0f);
    attackRange.setSkewForCentre(50.0f);

    juce::NormalisableRange<float> releaseRange = juce::NormalisableRange<float>(0.0f, 5000.0f, 1.0f);
    releaseRange.setSkewForCentre(160.0f);

    //parameters are created
    auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", -60.0f, 24.0f, 0.0f);
    auto pThresh = std::make_unique<juce::AudioParameterFloat>("thresh", "Threshold", -60.0f, 10.0f, 0.0f);
    auto pRatio = std::make_unique<juce::AudioParameterFloat>("ratio", "Ratio", 1.0f, 20.0f, 1.0f);
    auto pAttack = std::make_unique<juce::AudioParameterFloat>("attack", "Attack", attackRange, 50.0f);
    auto pRelease = std::make_unique<juce::AudioParameterFloat>("release", "Release", releaseRange, 160.0f);
    auto pOutput = std::make_unique<juce::AudioParameterFloat>("output", "Output", -60.0f, 24.0f, 0.0f);

    //different type of parameters like floats or selection are pushed into the params vector
    params.push_back(std::move(pInput));
    params.push_back(std::move(pThresh));
    params.push_back(std::move(pRatio));
    params.push_back(std::move(pAttack));
    params.push_back(std::move(pRelease));
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
    inputModule.setGainDecibels(apvts.getRawParameterValue("input")->load());
    compressorModule.setThreshold(apvts.getRawParameterValue("thresh")->load());
    compressorModule.setRatio(apvts.getRawParameterValue("ratio")->load());
    compressorModule.setAttack(apvts.getRawParameterValue("attack")->load());
    compressorModule.setRelease(apvts.getRawParameterValue("release")->load());
    outputModule.setGainDecibels(apvts.getRawParameterValue("output")->load());

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
    outputModule.prepare(spec);
    outputModule.setRampDurationSeconds(0.02);
    compressorModule.prepare(spec);

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

    juce::dsp::AudioBlock<float> block(buffer);

    //process DSP modules
    inputModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    compressorModule.process(juce::dsp::ProcessContextReplacing<float>(block));
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
