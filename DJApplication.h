/*
  ==============================================================================

    DJApplication.h
    Created: 2 Mar 2022 1:24:39pm
    Author:  13z79

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DJApplication : public juce::AudioSource{
    
public:
    //==============================================================================
    DJApplication();
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

private:

    juce::AudioFormatManager formatManager;

    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};