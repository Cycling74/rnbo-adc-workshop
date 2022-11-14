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
	p->addListener(this);

	addAndMakeVisible (overblowSlider);
	overblowSlider.addListener (this);

	addAndMakeVisible (harmonicsSlider);
	harmonicsSlider.addListener (this);

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

	for (int i = 0; i < 8; i++) {
		blobs.add(new BlobComponent(Colours::rebeccapurple));
		addAndMakeVisible( blobs[i] );
	}

	setResizable( true, true );
	setSize (400, 400);
}

RNBOAudioProcessorEditor::~RNBOAudioProcessorEditor()
{
	processor.removeListener(this);
	for (int i = 0; i < 8; i++) {
		BlobComponent *b = blobs.removeAndReturn(0);
		delete b;
	}
}

void RNBOAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll (Colours::darkgrey);
}

void RNBOAudioProcessorEditor::resized()
{
	// position the blobs in the space at the top
	auto blobBounds = getBounds().withBottom(getHeight() - 40);
	auto blobWidth = blobBounds.getWidth() / 4.0;
	auto blobHeight = blobBounds.getHeight() / 2.0;
	for (int i = 0; i < 8; i++) {
		auto myBounds = blobBounds.withX((i % 4) * blobWidth);
		myBounds.setY((i / 4) * blobHeight);
		myBounds.setWidth(blobWidth);
		myBounds.setHeight(blobHeight);
		blobs[i]->setBounds( myBounds );
	}

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

	if (param && index >= 0) {
		value = _rnboObject.convertToNormalizedParameterValue(index, slider->getValue());
		param->beginChangeGesture();
		param->setValueNotifyingHost(value);
		param->endChangeGesture();
	}
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
		double trueValue = _rnboObject.convertFromNormalizedParameterValue(parameterIndex, value);
		slider->setValue(trueValue, juce::dontSendNotification);

		ParameterValue hv = _rnboObject.getParameterNormalized(harmonicsParamIndex);
		ParameterValue ov = 1.0 - _rnboObject.getParameterNormalized(overblowParamIndex); // invert
		for (BlobComponent *blob: blobs) {
			blob->stretchPointTarget(hv, ov);
		}
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
	if (event.getType() == MessageEvent::List) {
		if (event.getTag() == TAG("active")) {
			auto list = event.getListValue().get();
			unsigned int idx = list->operator[](0) - 1;
			bool active = list->operator[](1) > 0;
			blobs[idx]->active(active);
		}
	}
}

} // namespace RNBO
