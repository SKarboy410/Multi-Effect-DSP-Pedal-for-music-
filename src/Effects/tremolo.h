#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Tremolo{
    public:
        Tremolo();

        void prepare(double newSampleRate, int samplesPerBlockExpected);

        void setRate(float newRate);
        void setDepth(float newDepth);

        float getRate() const;
        float getDepth() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

private:
    double sampleRate = 44100.0;

    float rate = 5.0f;
    float depth = 0.5f;

    float lfoPhase = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tremolo);

};