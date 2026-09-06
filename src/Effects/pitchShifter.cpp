#include "pitchShifter.h"

PitchShifter::PitchShifter(){

}

void PitchShifter::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    const int maxDelaySamples = static_cast<int>(0.1 * sampleRate) + samplesPerBlockExpected + 2;

    delayBuffer.setSize(2, maxDelaySamples);
    delayBuffer.clear();

    writePosition = 0;
    readPosition = 0.0f;
}

void PitchShifter::setPitch(float newPitch){
    pitch = newPitch;
}

void PitchShifter::setMix(float newMix){
    mix = newMix;
}

float PitchShifter::getPitch() const{
    return pitch;
}

float PitchShifter::getMix() const{
    return mix;
}

void PitchShifter::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const float pitchRatio = std::pow(2.0f, pitch / 12.0f);

    const int delayBufferSize = delayBuffer.getNumSamples();

    const float baseDelay = 0.05f * static_cast<float>(sampleRate);

    for (int sample = 0; sample < numSamples; ++sample){
        for (int channel = 0; channel < 2; ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            const float input = inputData[sample];

            delayData[writePosition] = input;

            float readPos = static_cast<float>(writePosition) - baseDelay + readPosition;

            while (readPos < 0.0f)
                readPos += delayBufferSize;

            while (readPos >= delayBufferSize)
                readPos -= delayBufferSize;

            const int index1 = static_cast<int>(readPos);
            const int index2 = (index1 + 1) % delayBufferSize;
            const float fraction = readPos - index1;

            const float shifted = delayData[index1] + fraction * (delayData[index2] - delayData[index1]);

            inputData[sample] = input * (1.0f - mix) + shifted * mix;
        }

        readPosition += pitchRatio - 1.0f;

        const float maxReadOffset = baseDelay * 0.5f;

        if (readPosition > maxReadOffset)
            readPosition = -maxReadOffset;

        if (readPosition < -maxReadOffset)
            readPosition = maxReadOffset;

        ++writePosition;

        if (writePosition >= delayBufferSize)
            writePosition = 0;
    }
}
