#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Distortion{
    public:
        Distortion();

        void setDrive(float newDrive);
        float getDrive() const;

        void setMix(float newMix);
        float getMix() const;

        void setOutputGain(float newOutputGain);
        float getOutputGain() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, 
        int numSamples);
    
    private:
        float drive = 5.0f;
        float mix = 1.0f;
        float outputGain = 0.7f;

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Distortion)
};