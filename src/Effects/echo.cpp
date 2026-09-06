#include "echo.h"

Echo::Echo(){

}

void Echo::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    const int bufferSize = static_cast<int>(sampleRate * 1.5) + samplesPerBlockExpected;
    
    delayBuffer.setSize(2, bufferSize);
    delayBuffer.clear();

    writePos = 0;

    previousEcho[0] = 0.0f;
    previousEcho[1] = 0.0f;
}

void Echo::setTime(float newTime){
    time = newTime;
}

void Echo::setFeedback(float newFeedback){
    feedback = newFeedback;
}

void Echo::setMix(float newMix){
    mix = newMix;
}

float Echo::getTime() const{
    return time;
}

float Echo::getFeedback() const{
    return feedback;
}

float Echo::getMix() const{

    return mix;
}

void Echo::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const int bufferSize = delayBuffer.getNumSamples();
    const int delaySamples = static_cast<int>(time * 0.001f * sampleRate);

    for(int sample = 0; sample < numSamples; ++sample){
        const int readPos = (writePos - delaySamples + bufferSize)%bufferSize;

        for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            float input = inputData[sample];
            float delayed = delayData[readPos];

            //simple damping
            //smooth the previous echo before
            // sending it back to delay
            float dampedEcho = previousEcho[channel] * 0.7f + delayed * 0.3f;
            previousEcho[channel] = dampedEcho;
            delayData[writePos] = input + dampedEcho * feedback;

            float output = input * (1.0f - mix) + delayed * mix;
            
            inputData[sample] = output;
        }

        ++writePos;

        if(writePos >= bufferSize)
            writePos = 0;
    }
}