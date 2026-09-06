#include "noiseGate.h"

noiseGate::noiseGate(){
    
}

void noiseGate::prepare(double sampleRate){
    currentSampleRate = static_cast<float>(sampleRate);
}

void noiseGate::setThreshold(float newThresholdDB){
    thresholdDB = newThresholdDB;
}

float noiseGate::getThreshold() const{
    return thresholdDB;
}

void noiseGate::processBlock(juce::AudioBuffer<float>& buffer, int startSample, 
    int numSamples){
        if(numSamples <= 0)
            return;
        
        auto* inputData = buffer.getReadPointer(0, startSample);
        auto* outputData = buffer.getWritePointer(0, startSample);

        //calculate RMS 
        float sumSquare = 0.0f;

        for(int sample = 0; sample < numSamples; ++sample){
            float inputSample = inputData[sample];

            sumSquare += inputSample*inputSample;
        }

        float rmsLevel = std::sqrt(sumSquare/numSamples);

        float rmsDB = juce::Decibels::gainToDecibels(rmsLevel, -100.0f);

        // gate open condition
        float closeThreshold = thresholdDB - hysteresisDB;

        if(!gateOpen){
            // gate is currently closed
            // only open when we cross opening threshold
            if(rmsDB > thresholdDB)
                gateOpen = false;
        }
        else{
            // Gate is currently open.
            // Keep it open until the signal drops lower.
            if (rmsDB < closeThreshold)
                gateOpen = false;
        }
        float targetGain;

        if(rmsDB > thresholdDB)
            targetGain = 1.0f;
        else
            targetGain = 0.0f;

        // smoothly open gate
        for(int sample = 0; sample < numSamples; ++sample){
            if(targetGain > gateGain){
                float attackStep = 1.0f/(attackTime * currentSampleRate);

                gateGain += attackStep;

                if(gateGain > 1.0f)
                    gateGain = 1.0f;
            }
            else if(targetGain < gateGain){
                float releaseStep = 1.0f / (releaseTime * currentSampleRate);

                gateGain -= releaseStep;

                if(gateGain< 0.0f)
                    gateGain = 0.0f;

            }

            outputData[sample] = inputData[sample] * gateGain;
        }

}