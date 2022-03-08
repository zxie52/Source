/*
  ==============================================================================

    DeckGUI.cpp
    Created: 2 Mar 2022 3:14:33pm
    Author:  13z79

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJApplication* _player,
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse) : player(_player), 
                                                          waveformDisplay(formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // make the button visible
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    // make the slider visible 
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    // set the waveform visible on the right side of the GUI
    addAndMakeVisible(waveformDisplay);

    // add event listeners to the buttons and sliders
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    // Slider color
    volSliderLook.setColour(juce::Slider::thumbColourId, juce::Colours::red);
    speedSliderLook.setColour(juce::Slider::thumbColourId, juce::Colours::blue);
    posSliderLook.setColour(juce::Slider::thumbColourId, juce::Colours::orange);

    // set the range for sliders
    volSlider.setRange(0, 100);
    speedSlider.setRange(0.0, 10.0);
    posSlider.setRange(0.0, 5.0);

    // start the timer for the first 500 ms
    startTimer(500);// in milliseconds

}

DeckGUI::~DeckGUI()
{
    // stop the timer in the destructor function
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Player", getLocalBounds(),
                juce::Justification::left, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    // set the bound for each section

    double rowH = getHeight() / 8;

    loadButton.setBounds(0, 0, getWidth() / 2, rowH);
    playButton.setBounds(0, rowH, getWidth() / 2, rowH);
    stopButton.setBounds(0, rowH * 2, getWidth() / 2, rowH);

    volSlider.setSliderStyle(juce::Slider::Rotary);
    volSlider.setBounds(0, rowH * 3, getWidth() / 6, rowH * 4);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    volSlider.setLookAndFeel(&volSliderLook);

    speedSlider.setSliderStyle(juce::Slider::Rotary);
    speedSlider.setBounds(getWidth() / 6, rowH * 3, getWidth() / 6, rowH * 4);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    speedSlider.setLookAndFeel(&speedSliderLook);

    posSlider.setSliderStyle(juce::Slider::Rotary);
    posSlider.setBounds(getWidth() / 3, rowH * 3, getWidth() / 6, rowH * 4);
    posSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    posSlider.setLookAndFeel(&posSliderLook);

    waveformDisplay.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        DBG("The play button is clicked by the user");
        //use the pointer to run the start function
        player->start();
    }
    if (button == &stopButton)
    {
        DBG("The stop button is clicked by the user");
        //use the pointer to run the stop function
        player->stop();

    }
    if (button == &loadButton)
    {
        // load the music file 
        juce::FileChooser chooser{ "What file do you want..." };
        if (chooser.browseForFileToOpen())
        {
            // load the music to the player cache and waveform cache
            
            player->loadURL(juce::URL{ chooser.getResult() });
            waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        // change the volume of the music
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        // change the speed of the music
        player->setSpeed(slider->getValue());
    }

    if (slider == &posSlider)
    {
        // change the position of the music for possible playing forward or playing back
        player->setPositionRelative(slider->getValue());
    }
}

void DeckGUI::timerCallback() {
    DBG("DeckGUI::timerCallback");
    // set the position of the music file
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files) {
    // user can directly drag the file to the deck
    DBG("DeckGUI::isInterestedInFileDrag");
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y) {
    DBG("DeckGUI::filesDropped");
    if (files.size() == 1) {
        // load the file and waveform
        player->loadURL(juce::URL(juce::File{files[0]}));
        waveformDisplay.loadURL(juce::URL(juce::File{ files[0] }));
    }
}