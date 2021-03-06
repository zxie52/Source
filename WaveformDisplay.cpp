/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 2 Mar 2022 7:47:09pm
    Author:  13z79

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse) : audioThumb(10, formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
    fileLoaded = false;
    position = 0;
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::purple);

    if (fileLoaded) {
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0, 0.5f);
        g.setColour(juce::Colours::orange);
        g.drawRect(position * getWidth(), 0, getWidth() / 50, getHeight());
    }
    else {
        g.setFont(20.0f);
        g.drawText("File not loaded yet", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }

}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::setPositionRelative(double pos) {
    if (pos != position) {
        position = pos;
        repaint();
    }

}

void WaveformDisplay::loadURL(juce::URL audioURL) {
    DBG("WaveformDisplay::loadURL");

    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded) {
        std::cout << "The music file is loaded." << std::endl;
    }
    else {
        std::cout << "The music file is not loaded yet." << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source) {
    repaint();
}
