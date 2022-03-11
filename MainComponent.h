/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

// The maincompenet .cpp and .h are the highest hierarchy for the juce DJ application 
#pragma once

#include <JuceHeader.h>
#include "DJApplication.h"
#include "DeckGUI.h"
#include "Playlist.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    // the function for preparing the sample of music
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    // the function for getting ready for the next sample
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    // the function for removing the cache(e.g in the destructor function)
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // formatManager is the first crucial component for loading audio files
    juce::AudioFormatManager formatManager;
    // the thumbCache can be 100-1000, means the number of pieces of sample could be loaded at the same time
    juce::AudioThumbnailCache thumbCache{100};

    // create the 1st player and the deckGUI
    DJApplication player1{formatManager};
    DeckGUI deckGUI1{&player1, formatManager, thumbCache};

    // create the 2nd player and the deckGUI
    DJApplication player2{formatManager};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};

    // the mixer for combining the left and right channel
    // the juce could automatically combine the left and right channle in MixerAudioSource class
    juce::MixerAudioSource mixerSource;

    // add the component for the playlist
    Playlist playlist{formatManager};

    //macro fuction
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
