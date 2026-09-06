#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Delay{
    public:
        Delay();

        void prepare(double sampleRate, int samplesPerBlockExpected);

        void setDelayTime(float milliseconds);
        void setFeedback(float feedback);
        void setMix(float mix);

        float getDelayTime() const;
        float getFeedback() const;
        float getMix() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    
    private:
        double sampleRate = 44100.0f;

        float delayTimeMs = 400.0f;
        float feedback = 0.3f;
        float mix = 0.3f;

        juce::AudioBuffer<float> delayBuffer;

        int writePos = 0;
        int delaySamples = 17640;

        void updateDelaySamples();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Delay);

};