#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class noiseGate{
    public:
        noiseGate();
        
       void prepare(double sampleRate); // prepare gate

       void setThreshold(float newThresholdDB); // changes threshold value

       float getThreshold() const; // read current threshold value

       void processBlock(juce::AudioBuffer<float>& buffer, int startSample, 
        int numSamples); // apply noise gate
        
    private:
        float thresholdDB = -40.0f;
        float hysteresisDB = 5.0f;
        
        bool gateOpen = false;

        float gateGain = 0.0f;

        float attackTime = 0.08f;   // 80 ms
        float releaseTime = 0.3f;   // 300 ms

        float currentSampleRate = 48000.0f;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(noiseGate)
};