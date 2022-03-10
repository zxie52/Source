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
    DJApplication(juce::AudioFormatManager &_formatManager);
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
    
    juce::AudioFormatManager& formatManager;

    // the transportSource is also needed in DeckGUI.h, I put it in public 
    juce::AudioTransportSource transportSource;



private:
<<<<<<< HEAD
    juce::AudioFormatManager& formatManager;

    juce::AudioTransportSource transportSource;
=======
>>>>>>> 96e8898fbc77a0c893771a075642ca4dfbd4ecec
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

};