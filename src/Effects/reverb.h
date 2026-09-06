#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Reverb{
    public:
        Reverb();

        void prepare(double newSampleRate, int samplesPerBlockExpected);

        void setRoomSize(float newRoomSize);
        void setDamping(float newDamping);
        void setMix(float newMix);

        float getRoomSize() const;
        float getDamping() const;
        float getMix() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    
    private:
        double sampleRate = 44100.0;

        float roomSize = 0.5f;
        float damping = 0.5f;
        float mix = 0.3f;

        juce::AudioBuffer<float> delayBuffer;

        int writePos = 0;
        float previousOutput[2] = { 0.0f, 0.0f };

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Reverb);

};