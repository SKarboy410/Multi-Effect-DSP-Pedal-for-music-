#include "vocalDoubler.h"

VocalDoubler::VocalDoubler(){

}

void VocalDoubler::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    const int maxDelaySamples = static_cast<int>(0.030 * sampleRate) + samplesPerBlockExpected + 2;

    delayBuffer.setSize(2, maxDelaySamples);
    delayBuffer.clear();

    writePosition = 0;
    lfoPhase = 0.0f;
}

void VocalDoubler::setDelay(float newDelay){
    delayMs = newDelay;
}

void VocalDoubler::setWidth(float newWidth){
    width = newWidth;
}

void VocalDoubler::setMix(float newMix){
    mix = newMix;
}

float VocalDoubler::getDelay() const{
    return delayMs;
}

float VocalDoubler::getWidth() const{
    return width;
}

float VocalDoubler::getMix() const{
    return mix;
}

void VocalDoubler::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){

    const float lfoRate = 0.25f;
    const float phaseIncrement = lfoRate / static_cast<float>(sampleRate);
    const int delayBufferSize = delayBuffer.getNumSamples();

    for (int sample = 0; sample < numSamples; ++sample){
        const float lfo = std::sin(2.0f * juce::MathConstants<float>::pi * lfoPhase);

        const float modulation = lfo * 2.0f;
        const float currentDelayMs = delayMs + modulation;
        const float delaySamples = currentDelayMs * 0.001f * static_cast<float>(sampleRate);
        const float readPosition = static_cast<float>(writePosition) - delaySamples;

        float wrappedReadPosition = readPosition;

        while (wrappedReadPosition < 0.0f)
            wrappedReadPosition += delayBufferSize;

        while (wrappedReadPosition >= delayBufferSize)
            wrappedReadPosition -= delayBufferSize;

        const int index1 = static_cast<int>(wrappedReadPosition);
        const int index2 = (index1 + 1) % delayBufferSize;

        const float fraction = wrappedReadPosition - index1;

        for (int channel = 0; channel < 2; ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            const float input = inputData[sample];

            delayData[writePosition] = input;

            const float delayed = delayData[index1] + fraction * (delayData[index2] - delayData[index1]);

            float doubled = delayed;

            if (channel == 0)
                doubled *= (1.0f - width * 0.5f);
            else
                doubled *= (1.0f + width * 0.5f);
            
            inputData[sample] = input * (1.0f - mix) + doubled * mix;
        }

        ++writePosition;

        if (writePosition >= delayBufferSize)
            writePosition = 0;

        lfoPhase += phaseIncrement;

        if (lfoPhase >= 1.0f)
            lfoPhase -= 1.0f;
    }
}