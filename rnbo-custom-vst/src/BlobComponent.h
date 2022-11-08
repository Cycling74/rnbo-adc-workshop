
#include "JuceHeader.h"

#pragma once

class BlobComponent : public juce::Component, private juce::Timer
{
public:
    //==============================================================================
    BlobComponent(juce::Colour bc): bodyColor(bc)
    {
        setSize (200, 200);
        startTimerHz (60);

        gen();
    }

    void active(const bool tf) {
        _active = tf;
    }

    void stretchPointTarget(const float x, const float y) {
        _stretchPointTarget.setXY(x, y);
    }

    void paint (juce::Graphics& g) override
    {
        // g.fillAll (juce::Colours::lightblue);
    
        g.setColour (juce::Colours::darkblue);
        // g.setFont (14.0f);
        // g.drawText ("Hello, World!", getLocalBounds(), juce::Justification::centred, true);

        float width = getBounds().getWidth();
        float height = getBounds().getHeight();
        float stretch = fabs((stretchPoint.x - 0.5) * width) + fabs((stretchPoint.y - 230.0 / 300.0) * height);

		// body
        g.setColour(bodyColor); // "#fed0";
        
        Path body;
        body.addLineSegment(juce::Line<float>(geo[6], geo[6]), 1.0);
        body.cubicTo(geo[7], geo[8], geo[9]);
        body.cubicTo(geo[10], geo[11], geo[6]);
        body.closeSubPath();
        g.fillPath(body);
        g.strokePath(body, PathStrokeType(1.0f));

		// mouth
        g.setColour(juce::Colour( 0xffbb77ff )); // "#fb7f";

        Path mouth;
		mouth.addLineSegment(juce::Line<float>(geo[0], geo[0]), 1.0);
        mouth.cubicTo(geo[1], geo[2], geo[3]);
        mouth.cubicTo(geo[4], geo[5], geo[0]);
        mouth.closeSubPath();
        g.fillPath(mouth);
        g.strokePath(mouth, PathStrokeType(1.0f));

		// eyes
		float eyeSpread = stretch / 10.0f + width / 10.0f;
		float closedEyeSize = width * (6.0f / 300.0f);
		float openEyeSize = width * (15.0f / 300.0f);
		float openPupilSize = width * (5.0f / 300.0f);
		float gazeEmphasis = width * (4.0f / 300.0f);
		float eyeYOffset = height / 10.0f;
        bool eyesClosed = stretchPoint.y < 0.2f;

        Path eyes;
		if (!eyesClosed) {
            g.setColour(juce::Colour( 0xffeeeeee ));
            eyes.addCentredArc(geo[9].x + eyeSpread, geo[9].y + eyeYOffset, openEyeSize, openEyeSize, 0, M_PI * 2.0, false);
            g.fillPath(eyes);

            eyes.clear();
            eyes.addCentredArc(geo[9].x - eyeSpread, geo[9].y + eyeYOffset, openEyeSize, openEyeSize, 0, M_PI * 2.0, false);
            g.fillPath(eyes);
			eyes.clear();
			
            g.setColour(juce::Colour( 0xff111111 ));
			eyes.addCentredArc(
				geo[9].x + eyeSpread + eyeFocus.x * gazeEmphasis,
				geo[9].y + eyeYOffset + eyeFocus.y * gazeEmphasis, openPupilSize, openPupilSize, 0, M_PI * 2, false); // Inner circle
            g.fillPath(eyes);

            eyes.clear();
			eyes.addCentredArc(
				geo[9].x - eyeSpread + eyeFocus.x * gazeEmphasis,
				geo[9].y + eyeYOffset + eyeFocus.y * gazeEmphasis, openPupilSize, openPupilSize, 0, M_PI * 2, false); // Inner circle
			g.fillPath(eyes);
		} else {
            g.saveState();
            g.setColour(juce::Colour( 0xff111111 ));
            eyes.addLineSegment(
                juce::Line<float>(
                    geo[9].x - (eyeSpread + closedEyeSize),
                    geo[9].y + eyeYOffset - closedEyeSize,
                    geo[9].x - (eyeSpread - closedEyeSize),
                    geo[9].y + eyeYOffset
                ),
                3.0f
            );
            eyes.lineTo(geo[9].x - (eyeSpread + closedEyeSize), geo[9].y + eyeYOffset + closedEyeSize);
            g.strokePath(eyes, PathStrokeType( 3.0f ));
            eyes.clear();

            eyes.addLineSegment(
                juce::Line<float>(
                    geo[9].x + (eyeSpread + closedEyeSize),
                    geo[9].y + eyeYOffset - closedEyeSize,
                    geo[9].x + (eyeSpread - closedEyeSize),
                    geo[9].y + eyeYOffset
                ),
                3.0f
            );
            eyes.lineTo(geo[9].x + (eyeSpread + closedEyeSize), geo[9].y + eyeYOffset + closedEyeSize);
            g.strokePath(eyes, PathStrokeType( 3.0f ));
            eyes.clear();
            g.restoreState();
		}
		hasDrawn = true;
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.

        gen();
    }

    void timerCallback() override
    {
        float width = getBounds().getWidth();
        float height = getBounds().getHeight();
        auto target = _active ? _stretchPointTarget : restingStretchPoint;

		if (hasDrawn) {
            auto a = (target - stretchPoint) * 0.05f;
            auto friction = -(stretchVelocity) * 0.5f;
            stretchVelocity += (a + friction);
            stretchPoint += (stretchVelocity);
		} else {
			stretchVelocity.setXY(0.0f, 0.0f);
            stretchPoint.setXY(target.x, target.y);
		}

		gen();
        repaint();
    }

private:
    const juce::Point<float> restingStretchPoint = juce::Point<float>(0.5f, 1.0f);
    juce::Point<float> stretchPoint = juce::Point<float>(restingStretchPoint);
    juce::Point<float> _stretchPointTarget = juce::Point<float>(restingStretchPoint);
    juce::Point<float> eyeFocus = juce::Point<float>(0.0f, 0.0f);
    juce::Point<float> stretchVelocity = juce::Point<float>(0.0f, 0.0f);

    std::array<juce::Point<float>, 12> baseGeo;
    std::array<juce::Point<float>, 12> wobbleVelocity;
    std::array<juce::Point<float>, 12> wobble;
    std::array<juce::Point<float>, 12> geo;

    juce::Random r;

    bool hasDrawn = false;
    bool _active = false;
    juce::Colour bodyColor;

    void gen() {
        float width = getBounds().getWidth();
        float height = getBounds().getHeight();
		float halfwidth = width / 2.0f;
		float halfy = height - 30.0f;
		float yoff = jmin(0.0f, stretchPoint.y * height - halfy);
		float partial = halfy + 0.1f * yoff;
		float curvo = fabs(yoff) * 0.4f + 5;
		float ax = ((stretchPoint.x - 0.5f) * width) * 0.75f + width / 2.0f;
		float ay = yoff * 0.75f + halfy;
        float noiseFactor = (1.0f - stretchPoint.y) * (1.0f - stretchPoint.y) * (width * 10.0f / 200.0f);
        
		baseGeo[0].setXY( halfwidth, partial );
		baseGeo[1].setXY( width / 2.0f - curvo * 1.5f, partial );
		baseGeo[2].setXY( ax - curvo, ay );
		baseGeo[3].setXY( ax, ay );
		baseGeo[4].setXY( ax + curvo, ay );
		baseGeo[5].setXY( width / 2.0f + curvo * 1.5f, partial );

		//body
		float mp = yoff > 0 ? -1.0f : 1.0f;
		float bodyp = halfy + 20.0f * mp + yoff * 0.1f;
		float corvu = fabs(yoff) * 0.4f + width / 6.0f;
		float bx = ((stretchPoint.x - 0.5f) * width) * 0.8f + width / 2.0f;
		float by = yoff * 0.76f + halfy;
		baseGeo[6].setXY( halfwidth, bodyp );
		baseGeo[7].setXY( width / 2.0f - corvu * 1.5f, bodyp );
		baseGeo[8].setXY( bx - corvu, by - height * (40.0f / 300.0f) * mp );
		baseGeo[9].setXY( bx, by - height * (40.0f / 300.0f) * mp );
		baseGeo[10].setXY( bx + corvu, by - height * (40.0f / 300.0f) * mp );
		baseGeo[11].setXY( width / 2.0f + corvu * 1.5f, bodyp );

        for (unsigned long i = 0; i < 12; i++) {
            wobbleVelocity[i].setXY(
				(r.nextFloat() - 0.5f) * noiseFactor,
				(r.nextFloat() - 0.5f) * noiseFactor
            );
			wobble[i].setXY(
				(wobble[i].x * 0.2f) + wobbleVelocity[i].x,
				(wobble[i].y * 0.2f) + wobbleVelocity[i].y
            );
			geo[i].setXY(
				baseGeo[i].x + wobble[i].x,
				baseGeo[i].y + wobble[i].y
            );
        }
	}

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlobComponent)
};
