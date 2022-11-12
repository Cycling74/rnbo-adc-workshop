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

	setResizable( true, true );
	setSize (400, 400);
}

RNBOAudioProcessorEditor::~RNBOAudioProcessorEditor()
{
}

void RNBOAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll (Colours::white);
}

void RNBOAudioProcessorEditor::resized()
{

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

} // namespace RNBO
