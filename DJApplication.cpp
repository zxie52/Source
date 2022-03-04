/*
  ==============================================================================

    DJApplication.cpp
    Created: 2 Mar 2022 1:24:39pm
    Author:  13z79

  ==============================================================================
*/

#include "DJApplication.h"

DJApplication::DJApplication(juce::AudioFormatManager& _formatManager) : formatManager(_formatManager) {

}

DJApplication::~DJApplication() {

}

//==============================================================================
void DJApplication::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
}
void DJApplication::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
}
void DJApplication::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}
//==============================================================================

void DJApplication::loadURL(juce::URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}
void DJApplication::setGain(double gain) {
    if (gain < 0 || gain > 1) {
        DBG("DJApplication::setGain the gain should be between 0 and 1!");
    }
    else {
        transportSource.setGain(gain);
    }
}
void DJApplication::setSpeed(double ratio) {
    if (ratio < 0 || ratio > 100.0) {
        DBG("DJApplication::setSpeed the ratio should be between 0 and 1!");
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJApplication::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}
void DJApplication::setPositionRelative(double pos) {
    if (pos < 0 || pos > 1.0) {
        DBG("DJApplication::setPositionRelative the ratio should be between 0 and 1!");
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}


// get the relative position of the playhead
double const DJApplication::getPositionRelative() {
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

void DJApplication::start() {
    transportSource.start();
}
void DJApplication::stop() {
    transportSource.stop();
}
