#include "tremolo.h"

Tremolo::Tremolo()
{
}

void Tremolo::prepare(double newSampleRate,int){
    sampleRate = newSampleRate;
    lfoPhase = 0.0f;
}

void Tremolo::setRate(float newRate){
    rate = newRate;
}

void Tremolo::setDepth(float newDepth){
    depth = newDepth;
}

float Tremolo::getRate() const{
    return rate;
}

float Tremolo::getDepth() const{
    return depth;
}

void Tremolo::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const float phaseIncrement = rate/static_cast<float>(sampleRate);

    for(int sample = 0; sample < numSamples; ++sample){
        float lfo = std::sin(2.0f * juce::MathConstants<float>::pi * lfoPhase);
        float lfoUnipolar = (lfo + 1.0f) * 0.5f;
        float amplitude = (1.0f - depth) + depth * lfoUnipolar;

        for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* data = buffer.getWritePointer(channel, startSample);

            data[sample] *= amplitude;
        }
        lfoPhase += phaseIncrement;

        if(lfoPhase >= 1.0f)
            lfoPhase -= 1.0f;
    }
}