#include "ringModulator.h"

RingModulator::RingModulator(){

}

void RingModulator::prepare(double newSampleRate, int){
    sampleRate = newSampleRate;
    phase = 0.0f;
}

void RingModulator::setFrequency(float newFrequency){
    frequency = newFrequency;
}

void RingModulator::setMix(float newMix){
    mix = newMix;
}

float RingModulator::getFrequency() const{
    return frequency;
}

float RingModulator::getMix() const{
    return mix;
}

void RingModulator::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const float phaseIncrement = frequency / static_cast<float>(sampleRate);

    for(int sample = 0; sample < numSamples; ++sample){
        float carrier = std::sin(2.0f * juce::MathConstants<float>::pi * phase);

        for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* data = buffer.getWritePointer(channel, startSample);
            
            float input = data[sample];
            float modulated = input * carrier;

            float output = input * (1.0f - mix) + modulated * mix;
            
            data[sample] = output;
        }

        phase += phaseIncrement;

        if(phase >= 1.0f)
            phase -= 1.0f;

    }
}