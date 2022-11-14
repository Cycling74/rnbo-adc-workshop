/*
 ==============================================================================

 RNBO_JuceAudioProcessorEditor.h
 Created: 21 Sep 2015 11:50:17am
 Author:  stb

 ==============================================================================
 */

#ifndef RNBO_JUCEAUDIOPROCESSOREDITOR_H_INCLUDED
#define RNBO_JUCEAUDIOPROCESSOREDITOR_H_INCLUDED

#include "JuceHeader.h"
#include "RNBO.h"

namespace RNBO {

	//==============================================================================
	class RNBOAudioProcessorEditor :
		public AudioProcessorEditor,
		public AsyncUpdater,
		public RNBO::EventHandler,
		public juce::Slider::Listener,
		public juce::AudioProcessorListener
	{
	public:
		//==============================================================================
		RNBOAudioProcessorEditor (AudioProcessor* owner, CoreObject& rnboObject);
		~RNBOAudioProcessorEditor() override;

		//==============================================================================
		void paint (Graphics&) override;
		void resized() override;

		void handleAsyncUpdate() override;

		void eventsAvailable() override;
		void handleParameterEvent(const RNBO::ParameterEvent& event) override;
		
	private:

		//==============================================================================
		CoreObject&								_rnboObject;
		ParameterEventInterfaceUniquePtr		_parameterInterface;

		juce::Slider							overblowSlider;
		juce::Slider							harmonicsSlider;
		ParameterIndex							overblowParamIndex;
		ParameterIndex							harmonicsParamIndex;
	};

} // namespace RNBO

#endif  // RNBO_JUCEAUDIOPROCESSOREDITOR_H_INCLUDED
