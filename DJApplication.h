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

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    void start();
    void stop();

    // get the relative position of the playhead
    double const getPositionRelative();

private:
    juce::AudioFormatManager & formatManager;

    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

};