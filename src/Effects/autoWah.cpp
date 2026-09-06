#include "autoWah.h"

AutoWah::AutoWah(){

}

void AutoWah::setMinFrequency(float newFrequency){
    minFrequency = newFrequency;
}

float AutoWah::getMinFrequency() const{
    return minFrequency;
}

void AutoWah::setMaxFrequency(float newFrequency){
    maxFrequency = newFrequency;
}

float AutoWah::getMaxFrequency() const{
    return maxFrequency;
}

void AutoWah::setSensitivity(float newSensitivity){
    sensitivity = newSensitivity;
}

float AutoWah::getSensitivity() const{
    return sensitivity;
}

void AutoWah::setResonance(float newResonance){
    resonance = newResonance;
}

float AutoWah::getResonance() const{
    return resonance;
}

void AutoWah::prepare(double sampleRate, int samplesPerBlock, int numChannels)
{
    currentSampleRate = static_cast<float>(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(numChannels);

    filter.prepare(spec);
    filter.reset();

    filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    filter.setCutoffFrequency(minFrequency);
    filter.setResonance(resonance);

    envelope = 0.0f;
}

void AutoWah::processBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples){
    float attackCoeff = std::exp(-1.0f / (attackTime * currentSampleRate));
    float releaseCoeff = std::exp(-1.0f / (releaseTime * currentSampleRate));

    filter.setResonance(resonance);

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

            float controlledEnvelope = envelope * sensitivity;
            controlledEnvelope = juce::jlimit(0.0f, 1.0f, controlledEnvelope);

            float cutoffFrequency = minFrequency + controlledEnvelope * (maxFrequency - minFrequency);

            filter.setCutoffFrequency(cutoffFrequency);
            filter.setResonance(resonance);

            float filteredSample = filter.processSample(channel, inputSample);

            data[sample] = filteredSample;
        }
    }


}