#include "reverb.h"

Reverb::Reverb(){

}

void Reverb::prepare(double newSampleRate, int samplesPerBlockExpected){
    sampleRate = newSampleRate;

    // Maximum delay is approximately 100 ms
    int bufferSize =
        static_cast<int>(sampleRate * 0.1)
        + samplesPerBlockExpected;

    delayBuffer.setSize(2,bufferSize);

    delayBuffer.clear();
    writePos = 0;

    previousOutput[0] = 0.0f;
    previousOutput[1] = 0.0f;
}

void Reverb::setRoomSize(float newRoomSize){
    roomSize = newRoomSize;
}

void Reverb::setDamping(float newDamping){
    damping = newDamping;
}

void Reverb::setMix(float newMix){
    mix = newMix;
}

float Reverb::getRoomSize() const{
    return roomSize;
}

float Reverb::getDamping() const{
    return damping;
}

float Reverb::getMix() const{
    return mix;
}

void Reverb::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    const int bufferSize = delayBuffer.getNumSamples();
    
    const int delay1 = static_cast<int>(sampleRate * 0.030 * (0.5 + roomSize));
    const int delay2 = static_cast<int>(sampleRate * 0.045 * (0.5 + roomSize));
    const int delay3 = static_cast<int>(sampleRate * 0.060 * (0.5 + roomSize));

    float feedback = 0.2f + roomSize * 0.7f;

    for(int sample = 0; sample < numSamples; ++sample){
        for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputData = buffer.getWritePointer(channel, startSample);
            auto* delayData = delayBuffer.getWritePointer(channel);

            float input = inputData[sample];

            int readPos1 = (writePos - delay1 + bufferSize) % bufferSize;
            int readPos2 = (writePos - delay2 + bufferSize) % bufferSize;
            int readPos3 = (writePos - delay3 + bufferSize) % bufferSize;

            float reflection1 = delayData[readPos1];
            float reflection2 = delayData[readPos2];
            float reflection3 = delayData[readPos3];

            float reverbSignal = (reflection1 + reflection2 + reflection3)/3.0f;

            //simple damping
            float dampedSignal = previousOutput[channel]*damping + reverbSignal*(1.0f - damping);

            previousOutput[channel] = dampedSignal;

            delayData[writePos] = input + dampedSignal*feedback;
            
            float output = input*(1.0f - mix) + dampedSignal*mix;
            inputData[sample] = output;
        }
        writePos++;

        if(writePos >= bufferSize)
            writePos = 0;
    }
}