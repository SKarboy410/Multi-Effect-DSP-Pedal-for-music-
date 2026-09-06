#include "compressor.h"

Compressor::Compressor(){

}

void Compressor::setThreshold(float newThreshold){
    thresholdDB = newThreshold;
}

float Compressor::getThreshold() const{
    return thresholdDB;
}

void Compressor::setRatio(float newRatio){
    ratio = newRatio;
}

float Compressor::getRatio() const{
    return ratio;
}

void Compressor::prepare(double sampleRate){
    currentSampleRate = static_cast<float>(sampleRate);
    currentGain = 1.0f;
}

void Compressor::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    float attackCoeff = std::exp(-1.0f / (attackTime * currentSampleRate));
    float releaseCoeff = std::exp(-1.0f / (releaseTime * currentSampleRate));
    
    for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
        auto* data = buffer.getWritePointer(channel, startSample);

        for(int sample = 0; sample < numSamples; ++sample){
            float inputSample = data[sample];


            float inputMagnitude = std::abs(inputSample);

            if (inputMagnitude > envelope){
                envelope = attackCoeff * envelope + (1.0f - attackCoeff) * inputMagnitude;
            }
            else{
                envelope = releaseCoeff * envelope + (1.0f - releaseCoeff) * inputMagnitude;
            }

float inputDB =
    juce::Decibels::gainToDecibels(envelope, -100.0f);

            float outputDB = inputDB;

            if (inputDB > thresholdDB){
                outputDB = thresholdDB + (inputDB - thresholdDB) / ratio;
            }
            float gainReductionDB = outputDB - inputDB;
            float gainReduction = juce::Decibels::decibelsToGain(gainReductionDB);

            if (gainReduction < currentGain){
                currentGain =
                    attackCoeff * currentGain
                    + (1.0f - attackCoeff) * gainReduction;
            }
            else{
                currentGain =
                    releaseCoeff * currentGain
                    + (1.0f - releaseCoeff) * gainReduction;
            }

            data[sample] = inputSample * currentGain;
        }
            

    }

}