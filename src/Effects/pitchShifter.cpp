#include "pitchShifter.h"

PitchShifter::PitchShifter(){

}

void PitchShifter::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    const int maxDelaySamples = static_cast<int>(0.1 * sampleRate) + samplesPerBlockExpected + 2;

    delayBuffer.setSize(2, maxDelaySamples);
    delayBuffer.clear();

    writePosition = 0;
    readPosition1 = 0.0f;
    readPosition2 = 0.5f;
    phase = 0.0f;
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
    const float windowSize = 0.02f * static_cast<float>(sampleRate);
    const float phaseIncrement = 1.0f / windowSize;

    for (int sample = 0; sample < numSamples; ++sample){
        const float window1 = 0.5f * (1.0f - std::cos(2.0f * juce::MathConstants<float>::pi * phase));

        float phase2 = phase + 0.5f;

        if (phase2 >= 1.0f)
            phase2 -= 1.0f;

        const float window2 = 0.5f * (1.0f - std::cos(2.0f * juce::MathConstants<float>::pi * phase2));

        for (int channel = 0; channel < 2; ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            const float input = inputData[sample];

            delayData[writePosition] = input;

            float readPos1 = static_cast<float>(writePosition) - baseDelay + readPosition1;
            float readPos2 = static_cast<float>(writePosition) - baseDelay + readPosition2;

            while (readPos1 < 0.0f)
                readPos1 += delayBufferSize;

            while (readPos1 >= delayBufferSize)
                readPos1 -= delayBufferSize;

            while (readPos2 < 0.0f)
                readPos2 += delayBufferSize;

            while (readPos2 >= delayBufferSize)
                readPos2 -= delayBufferSize;

            const int index1A = static_cast<int>(readPos1);
            const int index2A = (index1A + 1) % delayBufferSize;
            const float fractionA = readPos1 - index1A;

            const float shifted1 = delayData[index1A] + fractionA * (delayData[index2A] - delayData[index1A]);

            const int index1B = static_cast<int>(readPos2);
            const int index2B = (index1B + 1) % delayBufferSize;
            const float fractionB = readPos2 - index1B;

            const float shifted2 = delayData[index1B] + fractionB * (delayData[index2B] - delayData[index1B]);

            const float shifted = shifted1 * window1 + shifted2 * window2;

            inputData[sample] = input * (1.0f - mix) + shifted * mix;
        }

        readPosition1 += (pitchRatio - 1.0f) * 0.5f;
        readPosition2 += (pitchRatio - 1.0f) * 0.5f;

        if (readPosition1 > baseDelay)
            readPosition1 -= baseDelay * 2.0f;

        if (readPosition1 < -baseDelay)
            readPosition1 += baseDelay * 2.0f;

        if (readPosition2 > baseDelay)
            readPosition2 -= baseDelay * 2.0f;

        if (readPosition2 < -baseDelay)
            readPosition2 += baseDelay * 2.0f;

        phase += phaseIncrement;

        if (phase >= 1.0f)
            phase -= 1.0f;

        ++writePosition;

        if (writePosition >= delayBufferSize)
            writePosition = 0;
    }
}