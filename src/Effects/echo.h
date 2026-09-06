#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Echo{
public:
    Echo();

    void prepare(double newSampleRate, int samplesPerBlockExpected);

    void setTime(float newTime);
    void setFeedback(float newFeedback);
    void setMix(float newMix);

    float getTime() const;
    float getFeedback() const;
    float getMix() const;

    void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

private:
    double sampleRate = 44100.0;

    float time = 500.0f;
    float feedback = 0.4f;
    float mix = 0.4f;

    juce::AudioBuffer<float> delayBuffer;

    int writePos = 0;

    float previousEcho[2] = { 0.0f, 0.0f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Echo);
};