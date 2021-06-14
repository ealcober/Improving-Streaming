/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
SimpleCompressorAudioProcessor::SimpleCompressorAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
	AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
#endif
	parameters(*this, nullptr, Identifier("SimpleCompressorState"), createParameterLayout())
{

	// add Listeners to processor parameters 
	// function createParameterLayout is called before in order to fill parameters vector
	// with already set-up default and limit values of the parameters
	parameters.addParameterListener("threshold", this);
	parameters.addParameterListener("knee", this);
	parameters.addParameterListener("attack", this);
	parameters.addParameterListener("release", this);
	parameters.addParameterListener("ratio", this);
	parameters.addParameterListener("makeUp", this);

	parameters.addParameterListener("bypass", this);
	parameters.addParameterListener("hpf", this);

	parameters.addParameterListener("frequency", this);
	parameters.addParameterListener("quality", this);
	parameters.addParameterListener("compDegree", this);
	parameters.addParameterListener("autoThreshold", this);


}

SimpleCompressorAudioProcessor::~SimpleCompressorAudioProcessor()
{
}

//==============================================================================
const String SimpleCompressorAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool SimpleCompressorAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool SimpleCompressorAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool SimpleCompressorAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double SimpleCompressorAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int SimpleCompressorAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int SimpleCompressorAudioProcessor::getCurrentProgram()
{
	return 0;
}

void SimpleCompressorAudioProcessor::setCurrentProgram(int index)
{
}

const String SimpleCompressorAudioProcessor::getProgramName(int index)
{
	return {};
}

void SimpleCompressorAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void SimpleCompressorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	
	//compressor prepare to play code
	compressor.prepare({ sampleRate, static_cast<uint32> (samplesPerBlock), 2 });
	// prepare variables used on high pass filter processing
	twopi = 8.0f * atan(1.0f);
	quality = 0;
	pole1 = 0;
	pole2 = 0;
	pole3 = 0;
	pole4 = 0;
	outputs = (float*)calloc(getTotalNumInputChannels(), sizeof(float));
	pole1 = (float*)calloc(getTotalNumInputChannels(), sizeof(float));
	pole2 = (float*)calloc(getTotalNumInputChannels(), sizeof(float));
	pole3 = (float*)calloc(getTotalNumInputChannels(), sizeof(float));
	pole4 = (float*)calloc(getTotalNumInputChannels(), sizeof(float));


}

void SimpleCompressorAudioProcessor::releaseResources()
{ // safely free used resources before call destructor

	if (outputs) {
		free(outputs);
		outputs = nullptr;
	}
	if (pole1) {
		free(pole1);
		pole1 = nullptr;
	}
	if (pole2) {
		free(pole2);
		pole2 = nullptr;
	}
	if (pole3) {
		free(pole3);
		pole3 = nullptr;
	}
	if (pole4) {
		free(pole4);
		pole4 = nullptr;
	}
	compressor.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleCompressorAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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
/*

Just for get interoperability of both plugins used as source,
in order to let Compressor Visualizer be correctly updated
with values changed on sliders while playing, I needed to
create a second AudioBuffer Object that is only processed
when bypass is disabled and high pass filter option is enabled.
Visualization component is updated as parameter changes directed by 
preset selection button. With just one buffer this was impossible 

*/
void SimpleCompressorAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	
	int sample;
	
	const int numSamples = buffer.getNumSamples();

	AudioBuffer<float> ab2(buffer);


	// hpf + compresion
	bool off = parameters.getParameterAsValue("bypass").getValue();
	bool filtro = parameters.getParameterAsValue("hpf").getValue();
	bool autoTh = parameters.getParameterAsValue("autoThreshold").getValue();


	if (!off) {
	// AUTO THRESHOLD

		if (autoTh) {
			float tav = 0.5;
			auto rms = 0.0; //1
			rms = (1 - tav) * rms + tav * std::pow(buffer.getRMSLevel(1, 0, buffer.getNumSamples()), 2.0f);
			float dbRMS = 10 * std::log10(rms); //2
			Value thresholdSetTo = parameters.getParameterAsValue("threshold");
			thresholdSetTo = dbRMS;
		}

		if (filtro) {

			// HPF

			frequency = 250.0f;

			float c = (float)exp((-1.0) * twopi * frequency / getSampleRate());
			float input;
			quality = 0.4f;
			for (int channel = 0; channel < totalNumInputChannels; ++channel)
			{
				auto* outData = ab2.getWritePointer(channel);
				auto* inData = ab2.getReadPointer(channel);
				for (sample = 0; sample < ab2.getNumSamples(); sample++)
				{
					input = *(inData + sample) - pole4[channel] * quality;

					if (input > 1.0f) input = 1.0f;
					if (input < -1.0f) input = -1.0f;
					input = 1.5f * input - 0.5f * (input * input * input);

					pole1[channel] = input * (1.0f - c) + pole1[channel] * c;
					pole2[channel] = pole1[channel] * (1.0f - c) + pole2[channel] * c;
					pole3[channel] = pole2[channel] * (1.0f - c) + pole3[channel] * c;
					pole4[channel] = pole3[channel] * (1.0f - c) + pole4[channel] * c;

					//The subtraction causes the filter to do a highpass
					outputs[channel] = input - pole4[channel];


					*(outData + sample) = outputs[channel];
				}

			}


		}
		// if filter is disabled
		// no processing over buffer has been done
		// and compression is applied as in original code
		if (!hpf) {
			AudioBlock<float> ab(buffer);
			ProcessContextReplacing<float> context(ab);
			compressor.process(context);
		}
		// if filter is enabled
		// filtered signal has been already written on secondary (auxiliary) buffer
		// so we just compress that buffer as in original code.
		else {
			AudioBlock<float> ab(ab2);
			ProcessContextReplacing<float> context(ab);
			compressor.process(context);
		}

	}
	// if bypass is enabled buffer arrives here unprocessed
}


//==============================================================================
bool SimpleCompressorAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleCompressorAudioProcessor::createEditor()
{
	return new SimpleCompressorAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void SimpleCompressorAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	auto state = parameters.copyState();
	std::unique_ptr<juce::XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void SimpleCompressorAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new SimpleCompressorAudioProcessor();
}

// =============================================================================

// Params structure is filled here, as explained in constructor. 
// Data type, parameter name, variable parameter name, range and default values are defined
AudioProcessorValueTreeState::ParameterLayout SimpleCompressorAudioProcessor::createParameterLayout()
{
	// In this function parameters are setted
	std::vector<std::unique_ptr<RangedAudioParameter>> params;
	NormalisableRange<float> frequencyRange = NormalisableRange<float>(0, 20000);
	frequencyRange.setSkewForCentre(900);
	params.push_back(std::make_unique<AudioParameterFloat>("threshold", "Threshold", NormalisableRange<float>(-50.0f, 10.0f, 0.1f), -12.0f, "dB"));
	params.push_back(std::make_unique<AudioParameterFloat>("knee", "Knee", NormalisableRange<float>(0.0f, 30.0f, 0.1f), 0.0f, "dB"));
	params.push_back(std::make_unique<AudioParameterFloat>("attack", "Attack Time", NormalisableRange<float>(0.0f, 100.0f, 0.1f), 30.0f, "ms"));
	params.push_back(std::make_unique<AudioParameterFloat>("release", "Release Time", NormalisableRange<float>(0.0f, 800.0f, 0.1f), 800.0f, "ms"));
	params.push_back(std::make_unique<AudioParameterFloat>("ratio", "Ratio", NormalisableRange<float>(1.0f, 16.0f, 0.1f), 2.0f, " : 1",
		AudioProcessorParameter::genericParameter,
		[](float value, int maximumStringLength) { if (value > 15.9f) return String("inf"); return String(value, 2); }));
	params.push_back(std::make_unique<AudioParameterFloat>("makeUp", "Volume Out", NormalisableRange<float>(-10.0f, 20.0f, 0.1f), 0.0f, "dB"));

	params.push_back(std::make_unique<AudioParameterFloat>("frequency", "Frecuency", frequencyRange, 250.0f, "Hz"));
	params.push_back(std::make_unique<AudioParameterFloat>("quality", "Quality", NormalisableRange<float>(0, 4), 0.4f, "Q"));

	params.push_back(std::make_unique<AudioParameterBool>("bypass", "Bypass", false));
	params.push_back(std::make_unique<AudioParameterBool>("hpf", "200Hz Filter", true));
	params.push_back(std::make_unique<AudioParameterBool>("autoThreshold", "Auto Threshold", false));

	params.push_back(std::make_unique<AudioParameterInt>("compDegree", "Compression Degree", 1, 5, 3, "Compression Degree", nullptr, nullptr));


	return { params.begin(), params.end() };
}

float valueToString(String v) {

	return v.getFloatValue();
}

void SimpleCompressorAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
	

	// When a listener detected a parameter has changed
	// this function is called in order to update variable value
	// across editor-processor chain

	// timerCallback is checking to update compressor visualizer just in case charcteristicChanged=true


	if (parameterID == "knee")
	{

		compressor.setKnee(newValue);
		characteristicChanged = true;

	}
	else if (parameterID == "attack") {

		compressor.setAttackTime(newValue / 1000);

	}
	else if (parameterID == "release") {

		compressor.setReleaseTime(newValue / 1000);

	}
	else if (parameterID == "ratio")
	{

		if (newValue > 15.9f)
			compressor.setRatio(std::numeric_limits<float>::infinity());
		else
			compressor.setRatio(newValue);
		characteristicChanged = true;

	}
	else if (parameterID == "makeUp")
	{

		compressor.setMakeUpGain(newValue);
		characteristicChanged = true;

	}
	else if (parameterID == "autoThreshold")
		characteristicChanged = true;
	else if (parameterID == "bypass")
	{
		characteristicChanged = true;
	}
	else if (parameterID == "hpf")
	{

		characteristicChanged = true;

	}
	else if (parameterID == "compDegree") {

		// I decided to develop here compression degree
		// preset changes.

		Value knee, ratio, attack, release, makeUp, threshold;

		knee = parameters.getParameterAsValue("knee");
		knee = 0.5;

		bool autoTh = parameters.getParameterAsValue("autoThreshold").getValue();

		compDegree = (int)newValue;

		switch (compDegree)
		{
		case 1: //40,15,5 - times in ms from first test are written as comments in this section. 
				//second tests values are hard coded
			attack = parameters.getParameterAsValue("attack");
			attack = 70.0;
			release = parameters.getParameterAsValue("release");
			release = 70.0;
			makeUp = parameters.getParameterAsValue("makeUp");
			makeUp = 0.0;
			ratio = parameters.getParameterAsValue("ratio");
			ratio = 3.0;
			break;
		case 2: //35,20,4
			attack = parameters.getParameterAsValue("attack");
			attack = 40.0;
			release = parameters.getParameterAsValue("release");
			release = 80.0;
			makeUp = parameters.getParameterAsValue("makeUp");
			makeUp = 0.0;
			ratio = parameters.getParameterAsValue("ratio");
			ratio = 3.0;
			break;
		case 3: //30,25,3
			attack = parameters.getParameterAsValue("attack");
			attack = 10.0;
			release = parameters.getParameterAsValue("release");
			release = 90.0;
			makeUp = parameters.getParameterAsValue("makeUp");
			makeUp = 0.0;
			ratio = parameters.getParameterAsValue("ratio");
			ratio = 3.0;
			break;
		case 4://25,30,3.5
			attack = parameters.getParameterAsValue("attack");
			attack = 50.0;
			release = parameters.getParameterAsValue("release");
			release = 800.0;
			makeUp = parameters.getParameterAsValue("makeUp");
			makeUp = 0.0;
			ratio = parameters.getParameterAsValue("ratio");
			ratio = 3.5;
			break;
		case 5: //20,35,2
			attack = parameters.getParameterAsValue("attack");
			attack = 25.0;
			release = parameters.getParameterAsValue("release");
			release = 800.0;
			makeUp = parameters.getParameterAsValue("makeUp");
			makeUp = 0.0;
			ratio = parameters.getParameterAsValue("ratio");
			ratio = 3.5;
			break;
		default:
			break;
		}

		characteristicChanged = true;


	}
	else if (parameterID == "threshold")
	{
		
			compressor.setThreshold(newValue);
			characteristicChanged = true;
		
		

	}
	else if (parameterID == "maxGainRedInDb")
	{

		maxGainRedInDb = newValue;
		characteristicChanged = true;

	}



}
