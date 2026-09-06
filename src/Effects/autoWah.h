#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

class AutoWah{
    public:
       AutoWah();

       void prepare(double sampleRate, int samplesPerBlock, int numChannels);

       void setMinFrequency(float newFrequency);
       float getMinFrequency() const;

       void setMaxFrequency(float newFrequency);
       float getMaxFrequency() const;

       void setSensitivity(float newSensitivity);
       float getSensitivity() const;

       void setResonance(float newResonance);
       float getResonance() const;

       void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

       private:
        // float minFrequency = 300.0f;
        // float maxFrequency = 3000.0f;
        // float sensitivity = 2.0f;
        // float resonance = 5.0f;

        float minFrequency = 400.0f;
        float maxFrequency = 3500.0f;
        float sensitivity = 5.0f;
        float resonance = 6.0f;

        float attackTime = 0.01f;
        float releaseTime = 0.1f;

        float envelope = 0.0f;
        float currentSampleRate = 48000.0f;

        juce::dsp::StateVariableTPTFilter<float> filter;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutoWah)


};
