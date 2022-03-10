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


    // build up the columns for the playlist
    // column to show the tile of the audio file
    tableComponent.getHeader().addColumn("Track title", 0, 500);
    // column to show the URL file location
    tableComponent.getHeader().addColumn("URL", 1, 300);
    // column to show the length of the audio file
    tableComponent.getHeader().addColumn("length", 2, 120);
    // button to load the audio file to the upper deck
    tableComponent.getHeader().addColumn("Load to the Up Deck", 3, 180);
    // button to load the audio file to the lower deck
    tableComponent.getHeader().addColumn("Load to the down Deck", 4, 180);

    // set the model to build the table for the playlist
    tableComponent.setModel(this);

    // make the table component visible in the constructor function
    addAndMakeVisible(searchButton);
    addAndMakeVisible(importButton);
    addAndMakeVisible(exportButton);
    addAndMakeVisible(tableComponent);

    // add listeners to extra buttons
    importButton.onClick = [this] {importButtonClicked(); };
    exportButton.onClick = [this] {exportButtonClicked(); };
    searchButton.onClick = [this] {searchButtonClicked(); };
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

    double rowH = getHeight() / 8;
    double rowL = getWidth() / 8;

    searchButton.setBounds(0, 0, rowL * 2, rowH);
    importButton.setBounds(rowL*6, 0, rowL, rowH);
    exportButton.setBounds(rowL * 7, 0, rowL, rowH);

    tableComponent.setBounds(0, rowH, getWidth(), rowH*7);
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
    if (columnId == 0) {
        g.drawText(trackTitles[rowNumber], 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
}

juce::Component* Playlist::refreshComponentForCell(int 	rowNumber,
                                                   int 	columnId,
                                                   bool 	isRowSelected,
                                                   Component* existingComponentToUpdate) {
    if (columnId == 3) {
        if (existingComponentToUpdate == nullptr) {
            // if there is no load button on the playlist, add the load button at the end of each row
            juce::TextButton* upbtn = new juce::TextButton{ "Load to Up Deck" };

            // transform the int rowNumber to string and the get the component's ID
            juce::String id{ std::to_string(rowNumber) };
            upbtn->setComponentID(id);

            // add the listener to the button
            upbtn->addListener(this);
            existingComponentToUpdate = upbtn;
        }
    }
    
    if (columnId == 4) {
        if (existingComponentToUpdate == nullptr) {
            // if there is no load button on the playlist, add the load button at the end of each row
            juce::TextButton *downbtn = new juce::TextButton{ "Load to Down Deck" };

            // transform the int rowNumber to string and the get the component's ID
            juce::String id{ std::to_string(rowNumber) };
            downbtn->setComponentID(id);

            // add the listener to the button
            downbtn->addListener(this);
            existingComponentToUpdate = downbtn;
        }
    }
    // return the stored components
    return existingComponentToUpdate;
}

// listener for the play button
void Playlist::buttonClicked(juce::Button* button) {
    // convert the juce::string to the std::string
    if (button == downbtn) {
        juce::FileChooser chooser{ "What file do you want..." };
        if (chooser.browseForFileToOpen()) {
            int id = std::stoi(button->getComponentID().toStdString());
            //player->loadURL(juce::URL{ trackFiles[id] });
            //waveformDisplay.loadURL(juce::URL{ trackFiles[id] });
        }


    }
    else if (button == upbtn) {

    }

}

void Playlist::importButtonClicked() {
    juce::FileChooser chooser{ "What file do you want..." };

    if (chooser.browseForMultipleFilesToOpen()) {
        setTracks(chooser.getResults());
    }
}
void Playlist::exportButtonClicked() {

}
void Playlist::searchButtonClicked() {

}


void Playlist::setTracks(juce::Array<juce::File> trackFiles){

    for (int i = 0; i < trackFiles.size(); i++)
    {
        trackTitles.push_back(trackFiles[i].getFileName());
    }
    tableComponent.updateContent();
}
