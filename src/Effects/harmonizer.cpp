#include "harmonizer.h"

Harmonizer::Harmonizer(){

}

void Harmonizer::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    const int maxDelaySamples = static_cast<int>(0.1 * sampleRate) + samplesPerBlockExpected + 2;

    thirdBuffer.setSize(2, maxDelaySamples);
    fifthBuffer.setSize(2, maxDelaySamples);

    thirdBuffer.clear();
    fifthBuffer.clear();

    writePosition = 0;

    thirdReadPosition = 0.0f;
    fifthReadPosition = 0.0f;
}

void Harmonizer::setScale(float newScale){
    scale = newScale;
}

void Harmonizer::setMix(float newMix){
    mix = newMix;
}

void Harmonizer::setLevel(float newLevel){
    level = newLevel;
}

float Harmonizer::getScale() const{
    return scale;
}

float Harmonizer::getMix() const{
    return mix;
}

float Harmonizer::getLevel() const{
    return level;
}

void Harmonizer::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const float thirdSemitones = scale == 0.0f ? 4.0f : 3.0f;
    const float fifthSemitones = 7.0f;

    const float thirdRatio = std::pow(2.0f, thirdSemitones / 12.0f);
    const float fifthRatio = std::pow(2.0f,fifthSemitones / 12.0f);

    const int bufferSize = thirdBuffer.getNumSamples();
    const float baseDelay = 0.05f * static_cast<float>(sampleRate);

    for (int sample = 0; sample < numSamples; ++sample){
        float thirdVoice[2] = { 0.0f, 0.0f };
        float fifthVoice[2] = { 0.0f, 0.0f };

        for (int channel = 0; channel < 2; ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* thirdData = thirdBuffer.getWritePointer(channel);
            auto* fifthData = fifthBuffer.getWritePointer(channel);

            const float input = inputData[sample];

            thirdData[writePosition] = input;
            fifthData[writePosition] = input;

            float thirdRead = static_cast<float>(writePosition) - baseDelay + thirdReadPosition;
            float fifthRead = static_cast<float>(writePosition) - baseDelay + fifthReadPosition;

            while (thirdRead < 0.0f)
                thirdRead += bufferSize;

            while (thirdRead >= bufferSize)
                thirdRead -= bufferSize;

            while (fifthRead < 0.0f)
                fifthRead += bufferSize;

            while (fifthRead >= bufferSize)
                fifthRead -= bufferSize;

            const int thirdIndex1 = static_cast<int>(thirdRead);
            const int thirdIndex2 = (thirdIndex1 + 1) % bufferSize;
            const float thirdFraction = thirdRead - thirdIndex1;

            thirdVoice[channel] = thirdData[thirdIndex1] + thirdFraction * (thirdData[thirdIndex2] - thirdData[thirdIndex1]);

            const int fifthIndex1 = static_cast<int>(fifthRead);
            const int fifthIndex2 = (fifthIndex1 + 1) % bufferSize;
            const float fifthFraction = fifthRead - fifthIndex1;

            fifthVoice[channel] = fifthData[fifthIndex1] + fifthFraction * (fifthData[fifthIndex2] - fifthData[fifthIndex1]);
        }

        const float harmony = (thirdVoice[0] + thirdVoice[1] + fifthVoice[0] + fifthVoice[1]) * 0.25f;

        for (int channel = 0; channel < 2; ++channel){
            auto* inputData = buffer.getWritePointer(channel,startSample);

            const float input = inputData[sample];

            inputData[sample] = input * (1.0f - mix) + harmony * mix * level;
        }

        thirdReadPosition += thirdRatio - 1.0f;

        fifthReadPosition += fifthRatio - 1.0f;

        const float maxReadOffset = baseDelay * 0.5f;

        if (thirdReadPosition > maxReadOffset)
            thirdReadPosition = -maxReadOffset;

        if (thirdReadPosition < -maxReadOffset)
            thirdReadPosition = maxReadOffset;

        if (fifthReadPosition > maxReadOffset)
            fifthReadPosition = -maxReadOffset;

        if (fifthReadPosition < -maxReadOffset)
            fifthReadPosition = maxReadOffset;

        ++writePosition;

        if (writePosition >= bufferSize)
            writePosition = 0;
    }
}

