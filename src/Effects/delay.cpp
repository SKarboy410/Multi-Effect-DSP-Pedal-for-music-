#include "delay.h"

Delay::Delay(){
    updateDelaySamples();
}

void Delay::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    //max delay = 1s
    int bufferSize = static_cast<int>(sampleRate) + samplesPerBlockExpected;

    delayBuffer.setSize(2,bufferSize);
    delayBuffer.clear();

    writePos = 0;
    updateDelaySamples();
}

void Delay::setDelayTime(float milliseconds){
    delayTimeMs = milliseconds;
    updateDelaySamples();
}

void Delay::setFeedback(float newFeedback){
    feedback = newFeedback;
}

void Delay::setMix(float newMix){
    mix = newMix;
}

float Delay::getDelayTime() const{
    return delayTimeMs;
}

float Delay::getFeedback() const{
    return feedback;
}

float Delay::getMix()const{

    return mix;
}

void Delay::updateDelaySamples(){
    delaySamples = static_cast<int>(delayTimeMs * 0.001 * sampleRate);
}

void Delay::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const int bufferSize = delayBuffer.getNumSamples();

    for(int sample = 0; sample < numSamples; ++sample){

        const int readPosition = (writePos - delaySamples + bufferSize) % bufferSize;

        for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputData =
                buffer.getWritePointer(channel, startSample);

            auto* delayData =
                delayBuffer.getWritePointer(channel);

            float input = inputData[sample];

            float delayed = delayData[readPosition];

            delayData[writePos] =
                input + delayed * feedback;

            float output =
                input * (1.0f - mix)
                + delayed * mix;

            inputData[sample] = output;
        }

        writePos++;

        if(writePos >= bufferSize)
            writePos = 0;
    }
}