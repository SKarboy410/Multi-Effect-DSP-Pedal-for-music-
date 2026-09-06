#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Chorus{
    public:
        Chorus();

        void prepare(double newSampleRate, int samplesPerBlockExpected);

        void setRate(float rateHz);
        void setDepth(float depthMs);
        void setMix(float newMix);

        float getRate() const;
        float getDepth() const;
        float getMix() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    
    private:
        double sampleRate = 44100.0f;

        float rateHz = 1.0f;
        float depthMs = 8.0f;
        float mix = 0.5f;

        float lfoPhase = 0.0f;
        const float baseDelayMs = 20.0f;

        juce::AudioBuffer<float> delayBuffer;

        int writePos = 0;
        
        float readSample(const float* data, int bufferSize, float delaySample);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Chorus);
};

