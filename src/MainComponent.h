#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "Effects/noiseGate.h"
#include "Effects/gain.h"
#include "Effects/distortion.h"
#include "Effects/compressor.h"
#include "Effects/autoWah.h"
#include "Effects/eq.h"
#include "Effects/delay.h"
#include "Effects/chorus.h"
#include "Effects/flanger.h"
#include "Effects/reverb.h"
#include "Effects/tremolo.h"
#include "Effects/vibrato.h"
#include "Effects/echo.h"
#include "Effects/threeTapEcho.h"
#include "Effects/ringModulator.h"
#include "Effects/vocalDoubler.h"
#include "Effects/pitchShifter.h"
#include "Effects/harmonizer.h"

#include "UI/parameterKnob.h"
#include "UI/effectPanel.h"


class MainComponent final : public juce::AudioAppComponent
{
public:

    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void prepareToPlay(
        int samplesPerBlockExpected,
        double sampleRate
    ) override;

    void getNextAudioBlock(
        const juce::AudioSourceChannelInfo& bufferToFill
    ) override;

    void releaseResources() override;


private:

    // Metering

    float peakLevel = 0.0f;
    float rmsLevel = 0.0f;
    float rmsDB = -100.0f;


    // Active effect
    enum class ActiveEffect
    {
        Gain,
        NoiseGate,
        Distortion,
        Compressor,
        AutoWah,
        EQ,
        Delay,
        Chorus,
        Flanger,
        Reverb,
        Tremolo,
        Vibrato,
        Echo,
        ThreeTapEcho,
        RingModulator,
        VocalDoubler,
        PitchShifter,
        Harmonizer
    };

    ActiveEffect activeEffect = ActiveEffect::Gain;


    // DSP effects
    Gain gainEffect;
    noiseGate noiseGate;
    Distortion disort;
    Compressor compress;
    AutoWah autowah;
    EQ eq;
    Delay delay;
    Chorus chorus;
    Flanger flanger;
    Reverb reverb;
    Tremolo tremolo;
    Vibrato vibrato;
    Echo echo;
    ThreeTapEcho threeTapEcho;
    RingModulator ringModulator;
    VocalDoubler vocalDoubler;
    PitchShifter pitchShifter;
    Harmonizer harmonizer;

    // Audio setup
    juce::TextButton continueButton { "Continue" };

    bool audioSetupComplete = false;

    std::unique_ptr<juce::AudioDeviceSelectorComponent>audioDeviceSelector;


    // Effect selector buttons
    juce::TextButton gainButton {"Gain"};
    juce::TextButton distortionButton {"Distortion"};
    juce::TextButton compressorButton {"Compressor"};
    juce::TextButton autoWahButton {"Auto-Wah"};
    juce::TextButton eqButton {"EQ"};
    juce::TextButton delayButton {"Delay"};
    juce::TextButton chorusButton {"Chorus"};
    juce::TextButton flangerButton {"Flanger"};
    juce::TextButton reverbButton {"Reverb"};
    juce::TextButton tremoloButton {"Tremolo"};
    juce::TextButton vibratoButton {"Vibrato"};
    juce::TextButton echoButton {"Echo"};
    juce::TextButton threeButton {"Three Tap Echo"};
    juce::TextButton ringButton {"Ring Modulator"};
    juce::TextButton vocalButton {"Vocal Doubler"};
    juce::TextButton pitchButton {"Pitch Shifter"};
    juce::TextButton harmonizerButton {"Harmonizer"};

    // Effect parameter panel
    EffectPanel effectPanel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};