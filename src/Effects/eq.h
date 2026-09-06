#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

class EQ{
    public:
        EQ();

        void prepare(double sampleRate);

        void setLowGain(float gainDB);
        void setMidGain(float gainDB);
        void setHighGain(float gainDB);

        float getLowGain() const;
        float getMidGain() const;
        float getHighGain() const;

        void processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSample);

    private:
        double sampleRate = 44100.0f;
        
        float lowGainDB = 0.0f;
        float midGainDB = 0.0f;
        float highGainDB = 0.0f;

        juce::dsp::IIR::Filter<float> lowFilter[2];
        juce::dsp::IIR::Filter<float> midFilter[2];
        juce::dsp::IIR::Filter<float> highFilter[2];

        void updateFilters();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EQ);
};