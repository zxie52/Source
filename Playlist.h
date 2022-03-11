/*
  ==============================================================================

    Playlist.h
    Created: 6 Mar 2022 11:03:41am
    Author:  13z79

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"

//==============================================================================
/*
*/
class Playlist  : public juce::Component,
                  public juce::TableListBoxModel,
                  public juce::Button::Listener
{
public:
    Playlist();
    ~Playlist() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // from the TableListBoxModel class, copy all inherited functions 
    int getNumRows() override;

    void paintRowBackground(juce::Graphics&,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;

    void paintCell(juce::Graphics&,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;

    Component* refreshComponentForCell(int 	rowNumber,
                                       int 	columnId,
                                       bool 	isRowSelected,
                                       Component* existingComponentToUpdate) override;

    // listener for the play button
    void buttonClicked(juce::Button* button) override;

    // set the tracks for the added file
    void setTracks(juce::Array<juce::File> trackFiles);

    // create the array to store the track titles in the playlist
    std::vector <juce::String> trackTitles;
    std::vector <juce::String> trackPaths;
    std::vector <juce::String> trackTypes;

    juce::Array <juce::File> trackFiles;

    // functions for extra buttons onClick
    void importButtonClicked();
    void exportButtonClicked();

private:

    juce::Label searchButton;

    juce::TextButton importButton{ "Import Playlist" };
    juce::TextButton exportButton{ "Export Playlist" };

    juce::TextButton* upbtn;
    juce::TextButton* downbtn;

    // create the table list box
    juce::TableListBox tableComponent;

    // have the transportSource to seek the duration of th track in the audio library
    juce::AudioTransportSource transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Playlist)
};
