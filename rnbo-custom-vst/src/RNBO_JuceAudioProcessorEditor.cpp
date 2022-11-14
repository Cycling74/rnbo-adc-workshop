/*
  ==============================================================================

    RNBO_JuceAudioProcessorEditor.cpp
    Created: 21 Sep 2015 11:50:17am
    Author:  stb

  ==============================================================================
*/

#include "RNBO_JuceAudioProcessorEditor.h"

namespace RNBO {

//==============================================================================
RNBOAudioProcessorEditor::RNBOAudioProcessorEditor(AudioProcessor* const p, CoreObject& rnboObject)
: AudioProcessorEditor (p)
, _rnboObject(rnboObject)
, _parameterInterface(_rnboObject.createParameterInterface(ParameterEventInterface::SingleProducer, this))
{
	jassert (p != nullptr);
	setOpaque (true);

	// Important--Add our editor as an AudioProcessorListener
	p->addListener(this);

	addAndMakeVisible (overblowSlider);
	overblowSlider.addListener (this);

	addAndMakeVisible (harmonicsSlider);
	harmonicsSlider.addListener (this);

	// Since getParameterIndexForID is temporarily bugged, you have to
	// do things this way. Even after that function gets fixed, it might
	// still be a good idea to pre-compute your indexes
	ParameterInfo paramInfo;
	for (ParameterIndex i = 0; i < _rnboObject.getNumParameters(); i++) {
		ConstCharPointer pid = _rnboObject.getParameterId(i);
		if (strcmp(pid, "harmonics") == 0) {
			harmonicsParamIndex = i;
			_rnboObject.getParameterInfo(i, &paramInfo);
			harmonicsSlider.setRange(paramInfo.min, paramInfo.max);
		} else if (strcmp(pid, "overblow") == 0) {
			overblowParamIndex = i;
			_rnboObject.getParameterInfo(i, &paramInfo);
			overblowSlider.setRange(paramInfo.min, paramInfo.max);
		}
	}

	// TODO: Create blobs

	setResizable( true, true );
	setSize (400, 400);
}

RNBOAudioProcessorEditor::~RNBOAudioProcessorEditor()
{
	processor.removeListener(this);
	// TODO: Free blobs
}

void RNBOAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll (Colours::darkgrey);
}

void RNBOAudioProcessorEditor::resized()
{
	// TODO: position your blobs

	// position the sliders at the bottom
	auto bottomBounds = getBounds().withTop(getHeight() - 40);

	overblowSlider.setBounds (bottomBounds.withRight(getWidth() / 2).reduced(4));
	harmonicsSlider.setBounds (bottomBounds.withLeft(getWidth() / 2).reduced(4));
}

void RNBOAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
	juce::AudioProcessorParameter *param = nullptr;
	int index = -1;
	double value = 0.0;
	if (slider == &overblowSlider) {
		index = overblowParamIndex;
		param = processor.getParameters()[overblowParamIndex];
	} else if (slider == &harmonicsSlider) {
		index = harmonicsParamIndex;
		param = processor.getParameters()[harmonicsParamIndex];
	}

	// TODO: Finish handling updates to the slider values
}

void RNBOAudioProcessorEditor::audioProcessorChanged (AudioProcessor*, const ChangeDetails&) { }

void RNBOAudioProcessorEditor::audioProcessorParameterChanged (AudioProcessor*, int parameterIndex, float value)
{
	juce::Slider *slider = nullptr;
	if (parameterIndex == overblowParamIndex) {
		slider = &overblowSlider;
	} else if (parameterIndex == harmonicsParamIndex) {
		slider = &harmonicsSlider;
	}

	if (slider != nullptr) {
		// TODO: Update sliders

		// TODO: Update blobs
	}
}


void RNBOAudioProcessorEditor::handleAsyncUpdate()
{
	drainEvents();
}

void RNBOAudioProcessorEditor::eventsAvailable()
{
	this->triggerAsyncUpdate();
}

void RNBOAudioProcessorEditor::handleParameterEvent(const ParameterEvent&)
{

}

void RNBOAudioProcessorEditor::handleMessageEvent(const MessageEvent& event) {
	// TODO: Handle RNBO message events
}

} // namespace RNBO
