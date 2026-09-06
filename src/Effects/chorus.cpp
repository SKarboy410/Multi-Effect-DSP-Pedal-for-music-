#include "chorus.h"
#include <cmath>

Chorus::Chorus(){

}

void Chorus::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    //Max delay:
    // 20ms base + 20ms depth = 40ms    
    int bufferSize = static_cast<int>(sampleRate * 0.05) + samplesPerBlockExpected;
    
    delayBuffer.setSize(2, bufferSize);
    delayBuffer.clear();

    writePos = 0;
    lfoPhase = 0.0f;
}

void Chorus::setRate(float newRate){
    rateHz = newRate;
}

void Chorus::setDepth(float newDepth){
    depthMs = newDepth;
}

void Chorus::setMix(float newMix){
    mix = newMix;
}

float Chorus::getRate() const{
    return rateHz;
}

float Chorus::getDepth() const{
    return depthMs;
}

float Chorus::getMix() const{
    return mix;
}

float Chorus::readSample(const float* data, int bufferSize, float delaySamples){
    float readPos = static_cast<float>(writePos) - delaySamples;

    while(readPos < 0.0f)
        readPos += bufferSize;
    
    while(readPos >= bufferSize)
        readPos -= bufferSize;
    
    int index1 = static_cast<int>(readPos);
    int index2 = (index1 + 1) % bufferSize;
    float fraction = readPos - static_cast<float>(index1);

    float sample1 = data[index1];
    float sample2 = data[index2];

    return sample1+fraction*(sample2 - sample1);
}

void Chorus::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const int bufferSize = delayBuffer.getNumSamples();

    for(int sample = 0; sample < numSamples; ++sample){
        //LFO from -1 to +1
        float lfo = std::sin(lfoPhase);

        //convert depth from ms to samples
        float depthSamples = depthMs * 0.001f * static_cast<float>(sampleRate);

        //base delay in samples
        float baseDelaySamples = baseDelayMs * static_cast<float>(sampleRate);

        //current modulated delay
        float delaySamples = baseDelaySamples + depthSamples*lfo;

        for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            float input = inputData[sample];

            //store current input
            delayData[writePos] = input;

            //read older sample
            float delayed = readSample(delayData, bufferSize, delaySamples);

            //dry + wet signal
            float output = input*(1.0f - mix) + delayed*mix;

            inputData[sample] = output;
        }

        //Advanced circular buffer
        writePos++;

        if(writePos >= bufferSize)
            writePos = 0;
        
        //advance LFO
        lfoPhase += 2.0f * juce::MathConstants<float>::pi * rateHz / static_cast<float>(sampleRate);

        if(lfoPhase >= 2.0f*juce::MathConstants<float>::pi)
            lfoPhase -= 2.0f * juce::MathConstants<float>::pi;
    }
}

