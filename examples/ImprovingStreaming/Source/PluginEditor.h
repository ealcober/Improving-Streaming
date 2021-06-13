/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../../thirdparty/CompressorVisualizer.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
/**
*/
class SimpleCompressorAudioProcessorEditor : public AudioProcessorEditor, private Timer
{
public:
	SimpleCompressorAudioProcessorEditor(SimpleCompressorAudioProcessor&, AudioProcessorValueTreeState&);
	~SimpleCompressorAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	
	void timerCallback() override;
	// sliders has been added to control processor parameter values from editor
	// slider attachments are created to keep link between processor and editor parameter values, as Button Attachment below
	Slider threshold, knee, attack, release, ratio, makeUp, compDegree;
	std::unique_ptr<SliderAttachment> thresholdAttachment, kneeAttachment, attackAttachment,
		releaseAttachment, ratioAttachment, makeUpAttachment, compDegreeAttachment;

	std::unique_ptr<ButtonAttachment> bypassAttachment, hpfAttachment, autoThresholdAttachment; 

	ToggleButton bypass, hpf, autoThreshold;
	// i will use this label for drawing a square updated with gain reduction in real time and color-painted accordingly
	Label l;
	TextButton gainReductionInDb;
private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	SimpleCompressorAudioProcessor& processor;
	AudioProcessorValueTreeState& parameters;
	// compressor visualizar is included as private
	CompressorVisualizer cv;
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleCompressorAudioProcessorEditor)
};
