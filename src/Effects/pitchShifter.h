#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class PitchShifter{
public:
    PitchShifter();

    void prepare(double newSampleRate, int samplesPerBlockExpected);

    void setPitch(float newPitch);
    void setMix(float newMix);

    float getPitch() const;
    float getMix() const;

    void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

private:
    double sampleRate = 44100.0;

    float pitch = 0.0f;
    float mix = 1.0f;

    juce::AudioBuffer<float> delayBuffer;

    int writePosition = 0;
    float readPosition = 0.0f;
};