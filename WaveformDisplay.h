/*
  ==============================================================================

    WaveformDisplay.h
    Created: 2 Mar 2022 7:47:09pm
    Author:  13z79

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                    juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // similar function with the DJApplication, for loading the audio
    void loadURL(juce::URL);

    // virtual function to set the listener for drawing the waveforms
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    // set the relaive position of the playhead
    void setPositionRelative(double pos);

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
