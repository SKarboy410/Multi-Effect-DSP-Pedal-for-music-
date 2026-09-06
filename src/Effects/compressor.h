#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Compressor{
    public:
        Compressor();

        void setThreshold(float newThreshold);
        float getThreshold() const;

        void setRatio(float newRatio);
        float getRatio() const;

        void prepare(double sampleRate);

        void setAttack(float newAttack);
        void getAttack() const;

        void setRelease(float newRelease);
        float getRelease() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    
    private:
        float thresholdDB = -20.0f;
        float ratio = 4.0f;

        float attackTime = 0.01f;
        float releaseTime = 0.1f;
        float envelope = 0.0f;
        
        float currentGain = 1.0f;
        float currentSampleRate = 48000.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Compressor)
 
};