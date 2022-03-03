/*
  ==============================================================================

    DeckGUI.h
    Created: 2 Mar 2022 3:14:33pm
    Author:  13z79

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJApplication.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget
{
public:
    DeckGUI(DJApplication* player,
            juce::AudioFormatManager &formatManagerToUse,
            juce::AudioThumbnailCache &cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** implement Button::Listener */
    void buttonClicked(juce::Button*) override;

    /** implement Slider::Listener */
    void sliderValueChanged(juce::Slider* slider) override;

    // implement drag function
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

private:

    // Your private member variables go here
    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    DJApplication* player;

    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
