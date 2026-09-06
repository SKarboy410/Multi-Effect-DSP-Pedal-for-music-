#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Flanger{
    public:
        Flanger();

        void prepare(double newSampleRate, int samplesPerBlockExpected);

        void setRate(float rateHz);
        void setDepth(float depthMs);
        void setFeedback(float newFeedback);
        void setMix(float newMix);

        float getRate() const;
        float getDepth() const;
        float getFeedback() const;
        float getMix() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

    private:
        double sampleRate = 44100.0;

        float rateHz = 0.5f;
        float depthMs = 3.0f;
        float feedback = 0.3f;
        float mix = 0.5f;

        const float baseDelayMs = 5.0f;

        float lfoPhase = 0.0f;

        juce::AudioBuffer<float> delayBuffer;

        int writePos = 0;

        float readSample(const float* data, int bufferSize, float delaySamples);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Flanger);


};