/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../src/GainReductionComputer.h"
#include "../../../src/SimpleCompressor.h"

//==============================================================================
/**
*/
class SimpleCompressorAudioProcessor : public AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
	//==============================================================================
	SimpleCompressorAudioProcessor();
	~SimpleCompressorAudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;
	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

	void parameterChanged(const String& parameterID, float newValue) override;
	

	GainReductionComputer& getGainReductionComputer() { return compressor.getGainReductionComputer(); };

	Atomic<bool> characteristicChanged = true;


private:
	// plugin parameter vector, filled in constructor
	AudioProcessorValueTreeState parameters;
	// Gain Reduction Computer added
	SimpleCompressor compressor;
	// boolean values to activate/deactivate added functions
	bool bypass;
	bool hpf;
	bool autoThreshold;

	int compDegree;

	float maxGainRedInDb=0.0f;
	// high pass filter parameters
	float frequency;
	float quality;
	float* pole1;
	float* pole2;
	float* pole3;
	float* pole4;
	float* outputs;
	float twopi;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleCompressorAudioProcessor)
};
