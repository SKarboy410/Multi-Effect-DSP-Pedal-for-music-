#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class RingModulator
{
public:
    RingModulator();

    void prepare(double newSampleRate, int samplesPerBlockExpected);

    void setFrequency(float newFrequency);
    void setMix(float newMix);

    float getFrequency() const;
    float getMix() const;

    void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

private:
    double sampleRate = 44100.0;

    float frequency = 100.0f;
    float mix = 0.5f;

    float phase = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RingModulator);

};