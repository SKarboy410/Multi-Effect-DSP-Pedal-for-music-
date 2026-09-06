#include "vibrato.h"

Vibrato::Vibrato(){

}

void Vibrato::prepare(double newSampleRate,int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    const int bufferSize = static_cast<int>(sampleRate * 0.02) + samplesPerBlockExpected;

    delayBuffer.setSize(2, bufferSize);
    delayBuffer.clear();

    writePos = 0;
    lfoPhase = 0.0f;
}

void Vibrato::setRate(float newRate){
    rate = newRate;
}

void Vibrato::setDepth(float newDepth){
    depth = newDepth;
}

void Vibrato::setMix(float newMix){
    mix = newMix;
}

float Vibrato::getRate() const{
    return rate;
}

float Vibrato::getDepth() const{
    return depth;
}

float Vibrato::getMix() const{
    return mix;
}

void Vibrato::processBlock(juce::AudioBuffer<float>& buffer, int startSample,int numSamples){
    const int bufferSize = delayBuffer.getNumSamples();
    const float phaseIncrement = rate / static_cast<float>(sampleRate);
    const float depthSamples = depth * 0.001f * static_cast<float>(sampleRate);

    for (int sample = 0; sample < numSamples; ++sample){
        float lfo = std::sin(2.0f * juce::MathConstants<float>::pi * lfoPhase);
        float delaySamples = depthSamples * 0.5f * (lfo + 1.0f);

        for (int channel = 0; channel < buffer.getNumChannels();++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            float input = inputData[sample];

            delayData[writePos] = input;

            float readPosition = static_cast<float>(writePos) - delaySamples;

            while (readPosition < 0.0f)
                readPosition += bufferSize;

            int index1 = static_cast<int>(readPosition);
            int index2 = (index1 + 1) % bufferSize;

            float fraction = readPosition - index1;
            float delayed = delayData[index1] + fraction * (delayData[index2] - delayData[index1]);
            float output = input * (1.0f - mix) + delayed * mix;

            inputData[sample] = output;
        }

        ++writePos;

        if (writePos >= bufferSize)
            writePos = 0;

        lfoPhase += phaseIncrement;

        if (lfoPhase >= 1.0f)
            lfoPhase -= 1.0f;
    }

}
