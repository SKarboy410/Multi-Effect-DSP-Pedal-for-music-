#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Vibrato
{
public:
    Vibrato();

    void prepare(double newSampleRate,int samplesPerBlockExpected);

    void setRate(float newRate);
    void setDepth(float newDepth);
    void setMix(float newMix);

    float getRate() const;
    float getDepth() const;
    float getMix() const;

    void processBlock(juce::AudioBuffer<float>& buffer, int startSample,int numSamples);

private:
    double sampleRate = 44100.0;

    float rate = 5.0f;
    float depth = 3.0f;
    float mix = 1.0f;

    float lfoPhase = 0.0f;

    juce::AudioBuffer<float> delayBuffer;

    int writePos = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Vibrato);
};