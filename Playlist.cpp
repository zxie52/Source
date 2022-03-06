/*
  ==============================================================================

    Playlist.cpp
    Created: 6 Mar 2022 11:03:41am
    Author:  13z79

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Playlist.h"

//==============================================================================
Playlist::Playlist()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // create the track titles
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");

    // build up the columns for the playlist
    tableComponent.getHeader().addColumn("Track title", 0, 400);
    tableComponent.getHeader().addColumn("artist", 1, 300);
    tableComponent.getHeader().addColumn("album", 2, 300);
    tableComponent.getHeader().addColumn("length", 3, 180);
    tableComponent.getHeader().addColumn("", 4, 100);

    // set the model to build the table for the playlist
    tableComponent.setModel(this);

    // make the table component visible in the constructor function
    addAndMakeVisible(tableComponent);
}

Playlist::~Playlist()
{
}

void Playlist::paint (juce::Graphics& g)
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
    g.setFont (20.0f);
    g.drawText ("Playlist", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Playlist::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int Playlist::getNumRows() {
    return trackTitles.size();
}

void Playlist::paintRowBackground(juce::Graphics& g,
                                  int rowNumber,
                                  int width,
                                  int height,
                                  bool rowIsSelected) {
    if (rowIsSelected) {
        g.fillAll(juce::Colours::blue);
    }
    else {
        g.fillAll(juce::Colours::grey);
    }
}

void Playlist::paintCell(juce::Graphics& g,
                         int rowNumber,
                         int columnId,
                         int width,
                         int height,
                         bool rowIsSelected) {
    g.drawText(trackTitles[rowNumber], 2, 0, width - 4, height, juce::Justification::centred, true);
}

juce::Component* Playlist::refreshComponentForCell(int 	rowNumber,
                                                   int 	columnId,
                                                   bool 	isRowSelected,
                                                   Component* existingComponentToUpdate) {
    if (columnId == 5) {
        if (existingComponentToUpdate == nullptr) {
            // if there is no play button on the playlist, add the play button at the end of each row
            juce::TextButton* bin = new juce::TextButton{ "Play" };

            // transform the int rowNumber to string and the get the component's ID
            juce::String id{ std::to_string(rowNumber) };
            bin->setComponentID(id);

            // add the listener to the button
            bin->addListener(this);
            existingComponentToUpdate = bin;
        }
    }
    
    // return the stored components
    return existingComponentToUpdate;
}

// listener for the play button
void Playlist::buttonClicked(juce::Button* button) {
    // convert the juce::string to the std::string
    int id = std::stoi(button->getComponentID().toStdString());

    DBG("Playlist::buttonClicked" << trackTitles[id]);

}
