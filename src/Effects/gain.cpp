#include "gain.h"

Gain::Gain(){

}

void Gain::setGain(float newGain){
    gain = newGain;
}

float Gain::getGain() const{
    return gain;
}

void Gain::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
        auto* data = buffer.getWritePointer(channel, startSample);

        for(int sample = 0; sample < numSamples; ++sample)
            data[sample]*=gain;
    }

}
