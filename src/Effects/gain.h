#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Gain
{
public:
    Gain();

    void setGain(float newGain);

    float getGain() const;

    void processBlock(
        juce::AudioBuffer<float>& buffer,
        int startSample,
        int numSamples
    );

private:
    float gain = 1.0f;
};