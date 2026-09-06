#include "threeTapEcho.h"

ThreeTapEcho::ThreeTapEcho(){

}

void ThreeTapEcho::prepare(double newSampleRate, int samplePerBlockExpected){
    sampleRate = newSampleRate;

    const int bufferSize = static_cast<int>(sampleRate * 3.0f) + samplePerBlockExpected;

    delayBuffer.setSize(2, bufferSize);
    delayBuffer.clear();

    writePos = 0;
}

void ThreeTapEcho::setFeedback(float newFeedback){
    feedback = newFeedback;
}

void ThreeTapEcho::setMix(float newMix){
    mix = newMix;
}

float ThreeTapEcho::getTime() const{
    return time;
}

float ThreeTapEcho::getFeedback() const{
    return feedback;
}

float ThreeTapEcho::getMix() const{
    return mix;
}

void ThreeTapEcho::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const int bufferSize = delayBuffer.getNumSamples();

    const int delay1 = static_cast<int>(time * 0.001f * sampleRate);
    const int delay2 = delay1 * 2;
    const int delay3 = delay1 * 3;

    for (int sample = 0; sample < numSamples; ++sample){
        const int readPos1 = (writePos - delay1 + bufferSize) % bufferSize;
        const int readPos2 = (writePos - delay2 + bufferSize) % bufferSize;
        const int readPos3 = (writePos - delay3 + bufferSize) % bufferSize;

        for (int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            float input = inputData[sample];

            float tap1 = delayData[readPos1];
            float tap2 = delayData[readPos2];
            float tap3 = delayData[readPos3];

            float echoSignal = 0.5f * tap1 + 0.3f * tap2 + 0.2f * tap3;

            delayData[writePos] = input + echoSignal * feedback;

            float output = input * (1.0f - mix) + echoSignal * mix;

            inputData[sample] = output;
        }

        ++writePos;

        if (writePos >= bufferSize)
            writePos = 0;
    }
}