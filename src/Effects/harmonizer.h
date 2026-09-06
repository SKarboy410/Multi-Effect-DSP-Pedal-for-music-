#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Harmonizer
{
public:
    Harmonizer();

    void prepare(double newSampleRate, int samplesPerBlockExpected);

    void setScale(float newScale);
    void setMix(float newMix);
    void setLevel(float newLevel);

    float getScale() const;
    float getMix() const;
    float getLevel() const;

    void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

private:
    double sampleRate = 44100.0;

    float scale = 0.0f;
    float mix = 0.5f;
    float level = 0.7f;

    juce::AudioBuffer<float> thirdBuffer;
    juce::AudioBuffer<float> fifthBuffer;

    int writePosition = 0;

    float thirdReadPosition = 0.0f;
    float fifthReadPosition = 0.0f;
};