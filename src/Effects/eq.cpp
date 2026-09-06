#include "eq.h"

EQ::EQ(){
    updateFilters();
}

void EQ::prepare(double newSampleRate){
    sampleRate = newSampleRate;

    for(int channel = 0; channel < 2; ++channel){
        lowFilter[channel].reset();
        midFilter[channel].reset();
        highFilter[channel].reset();
    }

    updateFilters();
}

void EQ::setLowGain(float gainDB){
    lowGainDB = gainDB;
    updateFilters();
}

void EQ::setMidGain(float gainDB){
    midGainDB = gainDB;
    updateFilters();
}
void EQ::setHighGain(float gainDB){
    highGainDB = gainDB;
    updateFilters();
}

float EQ::getLowGain() const{
    return lowGainDB;
}

float EQ::getMidGain() const{
    return midGainDB;
}

float EQ::getHighGain() const{
    return highGainDB;
}

void EQ::updateFilters(){
    auto lowCoefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 200.0f, 0.707f, 
    juce::Decibels::decibelsToGain(lowGainDB));

    auto midCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1000.0f, 1.0f, 
    juce::Decibels::decibelsToGain(midGainDB));

    auto highCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 4000.0f, 0.707f, 
    juce::Decibels::decibelsToGain(highGainDB));

    for(int channel = 0; channel < 2; ++channel){
        lowFilter[channel].coefficients = lowCoefficients;
        midFilter[channel].coefficients = midCoefficients;
        highFilter[channel].coefficients = highCoefficients;
    }
}

void EQ::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    for(int channel = 0; channel < buffer.getNumChannels(); ++channel){

        auto* data = buffer.getWritePointer(channel,startSample);

        for(int sample = 0; sample < numSamples; ++sample){

            float value = data[sample];

            value = lowFilter[channel].processSample(value);
            value = midFilter[channel].processSample(value);
            value = highFilter[channel].processSample(value);

            data[sample] = value;
        }
    }
}