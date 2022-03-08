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
#include "Playlist.h"

//==============================================================================

// extend the necessary classes for the deckGUI
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::LookAndFeel_V4,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
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

    // implement the timer function 
    void timerCallback() override;

private:

    // Your private member variables go here
    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };

    // three slider for the audio sample
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    // Look for the three different sliders
    juce::LookAndFeel_V4 volSliderLook;
    juce::LookAndFeel_V4 speedSliderLook;
    juce::LookAndFeel_V4 posSliderLook;

    // pointer for the player and also need to be called in the constructor function
    DJApplication* player;

    // waveformdisplay object, further for the WaveformDisplay.cpp
    WaveformDisplay waveformDisplay;

    Playlist playlist;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
