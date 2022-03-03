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
class WaveformDisplay  : public juce::Component
{
public:
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                    juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void loadURL(juce::URL);

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
