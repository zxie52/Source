/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJApplication.h"
#include "DeckGUI.h"

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
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{10};

    DJApplication player1{};
    DeckGUI deckGUI1{&player1, formatManager, thumbCache};

    DJApplication player2{};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};

    juce::MixerAudioSource mixerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
