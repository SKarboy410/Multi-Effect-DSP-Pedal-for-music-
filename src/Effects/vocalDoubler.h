#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class VocalDoubler
{
public:
    VocalDoubler();

    void prepare(double newSampleRate, int samplesPerBlockExpected);

    void setDelay(float newDelay);
    void setWidth(float newWidth);
    void setMix(float newMix);

    float getDelay() const;
    float getWidth() const;
    float getMix() const;

    void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

private:
    double sampleRate = 44100.0;

    float delayMs = 15.0f;
    float width = 0.7f;
    float mix = 0.5f;

    float lfoPhase = 0.0f;

    juce::AudioBuffer<float> delayBuffer;

    int writePosition = 0;
};