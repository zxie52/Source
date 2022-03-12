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
    Playlist(juce::AudioFormatManager& _formatManager);
    ~Playlist() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // from the TableListBoxModel class, copy all inherited functions 
    int getNumRows() override;

    // the virtuial function from TableListBoxModel class for paint the background of the playlist
    void paintRowBackground(juce::Graphics&,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;

    // paint each row of the playlist, if there is any music loaded
    void paintCell(juce::Graphics&,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;

    // update the row of the playlist(e.g called when user wants to load new audio files)
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
    std::vector <std::string> trackDurations;
    std::vector <juce::String> trackTypes;

    juce::Array <juce::File> trackFiles;

    // functions for extra buttons onClick
    void importButtonClicked();
    void exportButtonClicked();

    // function to have the trackduration
    std::string getDuration(juce::URL audioURL);

private:

    // the button for the search function
    juce::Label searchButton;

    // button to import the playlist audios and export a .csv file of the playlist(hopefully)
    juce::TextButton importButton{ "Import Playlist" };
    juce::TextButton exportButton{ "Export Playlist" };

    // the button for load library audio to updeck(deck1) or downdeck(deck2)
    juce::TextButton* upbtn;
    juce::TextButton* downbtn;

    // create the table list box
    juce::TableListBox tableComponent;

    // have the transportSource to seek the duration of th track in the audio library
    juce::AudioFormatManager& formatManager;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

    // macro function
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Playlist)
};
