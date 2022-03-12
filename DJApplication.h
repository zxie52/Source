/*
  ==============================================================================
    DJApplication.h
    Created: 2 Mar 2022 1:24:39pm
    Author:  13z79
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DJApplication : public juce::AudioSource {

public:
    //==============================================================================
    DJApplication(juce::AudioFormatManager& _formatManager);
    ~DJApplication();

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // function to load the URL of the audio source
    void loadURL(juce::URL audioURL);

    // the function to change the volume of the audio
    void setGain(double gain);

    // the function to change the speed of the audio file
    void setSpeed(double ratio);

    // the function to obtain the position of the file(both for changing the position and for drawing the waveform)
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    // the function for start and stop the audio
    void start();
    void stop();

    // get the relative position of the playhead
    double const getPositionRelative();

private:
    // for playing the tracks of the playlist, or individual audios to each deck
    juce::AudioFormatManager & formatManager;

    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

};