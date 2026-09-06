#include "distortion.h"
#include <cmath>

Distortion::Distortion(){

}

void Distortion::setDrive(float newDrive){
    drive = newDrive;
}

float Distortion::getDrive() const{
    return drive;
}

void Distortion::setMix(float newMix){ 
    mix = newMix;
}

float Distortion::getMix() const{
    return mix;
}

void Distortion::setOutputGain(float newOutputGain){
    outputGain = newOutputGain;
}

float Distortion::getOutputGain() const{
    return outputGain;
}

void Distortion::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
        auto* data = buffer.getWritePointer(channel, startSample);

        for(int sample = 0; sample < numSamples; ++sample){
            float inputSample = data[sample];
            float driveSample = inputSample * drive;
            float distortSample = std::tanh(driveSample);
            float mixSample = (mix * distortSample) + ((1.0f - mix)*inputSample);
            data[sample] = mixSample * outputGain;
        }
            

    }

}