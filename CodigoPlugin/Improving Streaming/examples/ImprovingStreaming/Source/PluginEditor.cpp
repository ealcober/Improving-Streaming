/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleCompressorAudioProcessorEditor::SimpleCompressorAudioProcessorEditor(SimpleCompressorAudioProcessor& p, AudioProcessorValueTreeState& params)
	: AudioProcessorEditor(&p), processor(p), parameters(params),
	cv(processor.getGainReductionComputer()),
	threshold(Slider::RotaryVerticalDrag, Slider::TextBoxBelow),
	knee(Slider::RotaryVerticalDrag, Slider::TextBoxBelow),
	attack(Slider::RotaryVerticalDrag, Slider::TextBoxBelow),
	release(Slider::RotaryVerticalDrag, Slider::TextBoxBelow),
	ratio(Slider::RotaryVerticalDrag, Slider::TextBoxBelow),
	makeUp(Slider::RotaryVerticalDrag, Slider::TextBoxBelow),
	bypass("Bypass"),
	hpf("High Pass Filter"),
	autoThreshold("Auto Threshold"),
	compDegree("Compression Degree"),
	gainReductionInDb("Max of Gain Reduction in DB")
	
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 380);

	// Sliders added to editor view and linked with processor parameters via the SliderAttachment class

	addAndMakeVisible(threshold);
	thresholdAttachment.reset(new SliderAttachment(parameters, "threshold", threshold));
	threshold.setTextValueSuffix(" dB");

	addAndMakeVisible(knee);
	kneeAttachment.reset(new SliderAttachment(parameters, "knee", knee));
	knee.setTextValueSuffix(" dB");

	addAndMakeVisible(attack);
	attackAttachment.reset(new SliderAttachment(parameters, "attack", attack));
	attack.setTextValueSuffix(" ms");

	addAndMakeVisible(release);
	releaseAttachment.reset(new SliderAttachment(parameters, "release", release));
	release.setTextValueSuffix(" ms");

	addAndMakeVisible(ratio);
	ratioAttachment.reset(new SliderAttachment(parameters, "ratio", ratio));
	ratio.setTextValueSuffix(" : 1");

	addAndMakeVisible(makeUp);
	makeUpAttachment.reset(new SliderAttachment(parameters, "makeUp", makeUp));
	makeUp.setTextValueSuffix(" dB");

	// little panel to show gain reduction applied in real time

	addAndMakeVisible(gainReductionInDb);

	addAndMakeVisible(l);
	


	addAndMakeVisible(cv);

	// controls added for bypass, high pass filter and compression degree functions

	addAndMakeVisible(bypass);
	bypassAttachment.reset(new ButtonAttachment(parameters, "bypass", bypass));

	addAndMakeVisible(hpf);
	hpfAttachment.reset(new ButtonAttachment(parameters, "hpf", hpf));

	addAndMakeVisible(autoThreshold);
	autoThresholdAttachment.reset(new ButtonAttachment(parameters, "autoThreshold", autoThreshold));

	addAndMakeVisible(compDegree);
	compDegree.setSliderStyle(Slider::IncDecButtons);
	compDegree.setTextBoxStyle(Slider::TextBoxRight, true, 180, 30);

	compDegree.setBounds(Rectangle<int>(209, 45, 180, 30));

	compDegree.setRange(Range<double>(0.0, 5.0), 1.0);
	compDegree.setEnabled(true);
	compDegree.setTextValueSuffix(" # Compression Level");
	compDegreeAttachment.reset(new SliderAttachment(parameters, "compDegree", compDegree));

	startTimer(50);

}

SimpleCompressorAudioProcessorEditor::~SimpleCompressorAudioProcessorEditor()
{
}

//==============================================================================
void SimpleCompressorAudioProcessorEditor::paint(Graphics& g)
{
	auto bounds = getLocalBounds();
	
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	// set the color and text font of next drawing
	g.setColour(Colours::yellowgreen);
	g.setFont(15.0f);
	// draw plugin title
	g.drawFittedText("Improving Voice @ Streaming - UCM", bounds.removeFromTop(30), Justification::centred, 1);

	// set row space for slider's titles and set positions
	auto labelRow = bounds.removeFromBottom(12);

	g.setFont(10.0f);
	g.drawFittedText("Threshold", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
	labelRow.removeFromLeft(8);
	g.drawFittedText("Knee", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
	labelRow.removeFromLeft(8);
	g.drawFittedText("Attack", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
	labelRow.removeFromLeft(8);
	g.drawFittedText("Release", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
	labelRow.removeFromLeft(8);
	g.drawFittedText("Ratio", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
	labelRow.removeFromLeft(8);
	g.drawFittedText("Volume Out", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
	g.setColour(Colours::red);
	g.setFont(20.0f);
	g.drawFittedText( "Gain Reduction", Rectangle<int>(45, 200, 90, 35), 12, Justification::centred, 1);


}

void SimpleCompressorAudioProcessorEditor::resized()
{

	// set for just in case view is resizeable
	// as this is not the case we use absolut values for new buttons possitions
	auto bounds = getLocalBounds();
	bounds.removeFromTop(40);
	bounds.removeFromBottom(12);

	auto rowDown = bounds.removeFromBottom(80);

	auto rowTop = bounds.removeFromTop(50);
	bypass.setBounds(rowTop.removeFromLeft(60));
	rowTop.removeFromLeft(8);

	hpf.setBounds(rowTop.removeFromLeft(60));
	rowTop.removeFromLeft(8);

	autoThreshold.setBounds(rowTop.removeFromLeft(60));
	rowTop.removeFromLeft(8);

	gainReductionInDb.setBounds(Rectangle<int>(70, 155, 40, 40));
	l.setBounds(Rectangle<int>(73, 157, 35, 35));

	compDegree.setBounds(rowTop.removeFromLeft(60));
	rowTop.removeFromLeft(8);

	threshold.setBounds(rowDown.removeFromLeft(60));
	rowDown.removeFromLeft(8);
	knee.setBounds(rowDown.removeFromLeft(60));
	rowDown.removeFromLeft(8);
	attack.setBounds(rowDown.removeFromLeft(60));
	rowDown.removeFromLeft(8);
	release.setBounds(rowDown.removeFromLeft(60));
	rowDown.removeFromLeft(8);
	ratio.setBounds(rowDown.removeFromLeft(60));
	rowDown.removeFromLeft(8);
	makeUp.setBounds(rowDown.removeFromLeft(60));

	cv.setBounds(Rectangle<int>(165, 95, 220, 190));



}

//update visualizer when any characteristic change
void SimpleCompressorAudioProcessorEditor::timerCallback()
{
	if (processor.characteristicChanged.get())
	{



		processor.characteristicChanged = false;



		cv.updateCharacteristic();

	}

	// update gain reduction in real time painting the little square on the left as defined
	auto dataGR = (int)processor.getGainReductionComputer().getMaxGainReductionInDecibels();
	l.setColour(Label::textColourId, Colours::black);
	if (dataGR <= 0 && dataGR > -2)
		l.setColour(Label::backgroundColourId, Colours::green);
	if (dataGR <= -2 && dataGR >= -4)
		l.setColour(Label::backgroundColourId, Colours::greenyellow);
	if (dataGR < -4 && dataGR >= -6)
		l.setColour(Label::backgroundColourId, Colours::yellow);
	if (dataGR < -6 && dataGR >= -8)
		l.setColour(Label::backgroundColourId, Colours::orangered);
	if (dataGR < -8)
		l.setColour(Label::backgroundColourId, Colours::red);
	gainReductionInDb.setButtonText(std::to_string(dataGR));
	l.setText(std::to_string(dataGR), NotificationType::sendNotificationSync);
	


	cv.repaint();

}

