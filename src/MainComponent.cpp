#include "MainComponent.h"

MainComponent::MainComponent(){

    noiseGate.setThreshold(-20.0f);
    gainEffect.setGain(1.0f);

    disort.setDrive(5.0f);
    disort.setMix(1.0f);
    disort.setOutputGain(0.7f);

    compress.setThreshold(-15.0f);
    compress.setRatio(2.0f);

    setAudioChannels(2, 2);

    audioDeviceSelector = 
        std::make_unique<juce::AudioDeviceSelectorComponent>(
            deviceManager,
            0,2,
            0,2,
            false,
            false,
            true,
            false
        );

    addAndMakeVisible(*audioDeviceSelector);


    continueButton.onClick = [this]{

        audioSetupComplete = true;

        audioDeviceSelector->setVisible(false);
        continueButton.setVisible(false);

        effectPanel.setVisible(true);

        gainButton.setVisible(true);
        distortionButton.setVisible(true);
        compressorButton.setVisible(true);
        autoWahButton.setVisible(true);
        eqButton.setVisible(true);
        delayButton.setVisible(true);
        chorusButton.setVisible(true);
        flangerButton.setVisible(true);
        reverbButton.setVisible(true);
        tremoloButton.setVisible(true);
        vibratoButton.setVisible(true);
        echoButton.setVisible(true);
        threeButton.setVisible(true);
        ringButton.setVisible(true);
        vocalButton.setVisible(true);
        pitchButton.setVisible(true);
        harmonizerButton.setVisible(true);

        resized();
    };

    addAndMakeVisible(continueButton);

    addChildComponent(gainButton);
    addChildComponent(distortionButton);
    addChildComponent(compressorButton);
    addChildComponent(autoWahButton);
    addChildComponent(eqButton);
    addChildComponent(delayButton);
    addChildComponent(chorusButton);
    addChildComponent(flangerButton);
    addChildComponent(reverbButton);
    addChildComponent(tremoloButton);
    addChildComponent(vibratoButton);
    addChildComponent(echoButton);
    addChildComponent(threeButton);
    addChildComponent(ringButton);
    addChildComponent(vocalButton);
    addChildComponent(pitchButton);
    addChildComponent(harmonizerButton);


    // Gain
    effectPanel.setTitle("GAIN");

    effectPanel.getKnob(0).configure(
        "Gain",
        0.0,
        2.0,
        1.0,
        0.01
    );

    effectPanel.getKnob(0).onValueChange = [this](float value){
        gainEffect.setGain(value);
    };

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(false);
    effectPanel.getKnob(2).setVisible(false);
    effectPanel.getKnob(3).setVisible(false);


    gainButton.onClick = [this]{
        activeEffect = ActiveEffect::Gain;
        effectPanel.setTitle("GAIN");

        effectPanel.getKnob(0).configure(
            "Gain",
            0.0,
            2.0,
            gainEffect.getGain(),
            0.01
        );

        effectPanel.getKnob(0).onValueChange = [this](float value){
            gainEffect.setGain(value);
        };

        effectPanel.getKnob(0).setVisible(true);
        effectPanel.getKnob(1).setVisible(false);
        effectPanel.getKnob(2).setVisible(false);
        effectPanel.getKnob(3).setVisible(false);
    };


    // Distortion
    distortionButton.onClick = [this]{

        activeEffect = ActiveEffect::Distortion;
        effectPanel.setTitle("DISTORTION");

        effectPanel.getKnob(0).configure(
            "Drive",
            1.0,
            20.0,
            5.0,
            0.1
        );

        effectPanel.getKnob(0).onValueChange = [this](float value){
            disort.setDrive(value);
        };

        effectPanel.getKnob(1).configure(
            "Mix",
            0.0,
            1.0,
            1.0,
            0.01
        );

        effectPanel.getKnob(1).onValueChange = [this](float value){
            disort.setMix(value);
        };


        effectPanel.getKnob(2).configure(
            "Output Gain",
            0.0,
            2.0,
            0.7,
            0.01
        );

        effectPanel.getKnob(2).onValueChange = [this](float value){
            disort.setOutputGain(value);
        };


        effectPanel.getKnob(0).setVisible(true);
        effectPanel.getKnob(1).setVisible(true);
        effectPanel.getKnob(2).setVisible(true);
        effectPanel.getKnob(3).setVisible(false);
    };


    // Compressor
    compressorButton.onClick = [this]{

        activeEffect = ActiveEffect::Compressor;
        effectPanel.setTitle("COMPRESSOR");

        effectPanel.getKnob(0).configure(
            "Threshold",
            -60.0,
            0.0,
            -15.0,
            1.0
        );

        effectPanel.getKnob(0).onValueChange = [this](float value){
            compress.setThreshold(value);
        };


        effectPanel.getKnob(1).configure(
            "Ratio",
            1.0,
            20.0,
            2.0,
            0.1
        );

        effectPanel.getKnob(1).onValueChange = [this](float value){
            compress.setRatio(value);
        };


        effectPanel.getKnob(0).setVisible(true);
        effectPanel.getKnob(1).setVisible(true);
        effectPanel.getKnob(2).setVisible(false);
        effectPanel.getKnob(3).setVisible(false);
    };


    // Auto-Wah
    autoWahButton.onClick = [this]{

        activeEffect = ActiveEffect::AutoWah;
        effectPanel.setTitle("AUTO-WAH");

        effectPanel.getKnob(0).configure(
            "Min Frequency",
            100.0,
            1000.0,
            300.0,
            10.0
        );

        effectPanel.getKnob(0).onValueChange = [this](float value){
            autowah.setMinFrequency(value);
        };


        effectPanel.getKnob(1).configure(
            "Max Frequency",
            1000.0,
            5000.0,
            3000.0,
            10.0
        );

        effectPanel.getKnob(1).onValueChange = [this](float value){
            autowah.setMaxFrequency(value);
        };

        effectPanel.getKnob(2).configure(
            "Sensitivity",
            0.1,
            10.0,
            2.0,
            0.1
        );

        effectPanel.getKnob(2).onValueChange = [this](float value){
            autowah.setSensitivity(value);
        };

        effectPanel.getKnob(3).configure(
            "Resonance",
            0.1,
            10.0,
            5.0,
            0.1
        );

        effectPanel.getKnob(3).onValueChange = [this](float value){
            autowah.setResonance(value);
        };


        effectPanel.getKnob(0).setVisible(true);
        effectPanel.getKnob(1).setVisible(true);
        effectPanel.getKnob(2).setVisible(true);
        effectPanel.getKnob(3).setVisible(true);
    };


    // EQ
    eqButton.onClick = [this]{
        activeEffect = ActiveEffect::EQ;
        effectPanel.setTitle("EQ");

        effectPanel.getKnob(0).configure(
            "Low Gain",
            -12.0,
            12.0,
            eq.getLowGain(),
            0.1
        );

        effectPanel.getKnob(0).onValueChange = [this](float value){ 
            eq.setLowGain(value);
        };

        effectPanel.getKnob(1).configure(
            "Mid Gain",
            -12.0,
            12.0,
            eq.getMidGain(),
            0.1
        );

        effectPanel.getKnob(1).onValueChange = [this](float value){ 
            eq.setMidGain(value);
        };

        effectPanel.getKnob(2).configure(
            "High Gain",
            -12.0,
            12.0,
            eq.getHighGain(),
            0.1
        );

        effectPanel.getKnob(2).onValueChange = [this](float value){ 
            eq.setHighGain(value);
        };

        effectPanel.getKnob(0).setVisible(true);
        effectPanel.getKnob(1).setVisible(true);
        effectPanel.getKnob(2).setVisible(true);
        effectPanel.getKnob(3).setVisible(false);
    };

    //Delay
    delayButton.onClick = [this]{
        activeEffect = ActiveEffect::Delay;
        effectPanel.setTitle("DELAY");

    effectPanel.getKnob(0).configure(
        "Delay Time",
        50.0,
        1000.0,
        delay.getDelayTime(),
        1.0
    );

    effectPanel.getKnob(0).onValueChange = [this](float value){
        delay.setDelayTime(value);
    };


    effectPanel.getKnob(1).configure(
        "Feedback",
        0.0,
        0.9,
        delay.getFeedback(),
        0.01
    );

    effectPanel.getKnob(1).onValueChange = [this](float value){
        delay.setFeedback(value);
    };


    effectPanel.getKnob(2).configure(
        "Mix",
        0.0,
        1.0,
        delay.getMix(),
        0.01
    );

    effectPanel.getKnob(2).onValueChange = [this](float value){
        delay.setMix(value);
    };

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(false);


    };

    //Chorus
    chorusButton.onClick = [this]{
        activeEffect = ActiveEffect::Chorus;
        effectPanel.setTitle("CHORUS");

        effectPanel.getKnob(0).configure(
        "Rate",
        0.1,
        5.0,
        chorus.getRate(),
        0.1
    );

    effectPanel.getKnob(0).onValueChange = [this](float value){
        chorus.setRate(value);
    };


    effectPanel.getKnob(1).configure(
        "Depth",
        1.0,
        20.0,
        chorus.getDepth(),
        0.1
    );

    effectPanel.getKnob(1).onValueChange = [this](float value){
        chorus.setDepth(value);
    };


    effectPanel.getKnob(2).configure(
        "Mix",
        0.0,
        1.0,
        chorus.getMix(),
        0.01
    );

    effectPanel.getKnob(2).onValueChange = [this](float value){
        chorus.setMix(value);
    };

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(false);

    };

    //Flanger
    flangerButton.onClick = [this]{
        activeEffect = ActiveEffect::Flanger;
        effectPanel.setTitle("FLANGER");

        effectPanel.getKnob(0).configure(
            "Rate",
            0.1,
            5.0,
            flanger.getRate(),
            0.1
    );

    effectPanel.getKnob(0).onValueChange = [this](float value){
        flanger.setRate(value);
    };


    effectPanel.getKnob(1).configure(
        "Depth",
        0.5,
        10.0,
        flanger.getDepth(),
        0.1
    );

    effectPanel.getKnob(1).onValueChange = [this](float value){
        flanger.setDepth(value);
    };


    effectPanel.getKnob(2).configure(
        "Feedback",
        0.0,
        0.9,
        flanger.getFeedback(),
        0.01
    );

    effectPanel.getKnob(2).onValueChange = [this](float value){
        flanger.setFeedback(value);
    };


    effectPanel.getKnob(3).configure(
        "Mix",
        0.0,
        1.0,
        flanger.getMix(),
        0.01
    );

    effectPanel.getKnob(3).onValueChange = [this](float value){
        flanger.setMix(value);
    };

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(true);


    };

    //Reverb
    reverbButton.onClick = [this]{
        activeEffect = ActiveEffect::Reverb;
        effectPanel.setTitle("REVERB");

        effectPanel.getKnob(0).configure(
            "Room Size",
            0.0,
            1.0,
            reverb.getRoomSize(),
            0.01
        );

        effectPanel.getKnob(0).onValueChange = [this](float value){
            reverb.setRoomSize(value);
        };


        effectPanel.getKnob(1).configure(
            "Damping",
            0.0,
            1.0,
            reverb.getDamping(),
            0.01
        );

        effectPanel.getKnob(1).onValueChange = [this](float value){
            reverb.setDamping(value);
        };


        effectPanel.getKnob(2).configure(
            "Mix",
            0.0,
            1.0,
            reverb.getMix(),
            0.01
        );

        effectPanel.getKnob(2).onValueChange = [this](float value){
            reverb.setMix(value);
        };

        effectPanel.getKnob(0).setVisible(true);
        effectPanel.getKnob(1).setVisible(true);
        effectPanel.getKnob(2).setVisible(true);
        effectPanel.getKnob(3).setVisible(false);

    };

    //Tremolo
    tremoloButton.onClick = [this]{
        activeEffect = ActiveEffect::Tremolo;
        effectPanel.setTitle("TREMOLO");

        effectPanel.getKnob(0).configure(
            "Rate",
            0.1,
            15.0,
            tremolo.getRate(),
            0.1
        );

        effectPanel.getKnob(1).configure(
            "Depth",
            0.0,
            1.0,
            tremolo.getDepth(),
            0.01
        );

        effectPanel.getKnob(0).setVisible(true);
        effectPanel.getKnob(1).setVisible(true);
        effectPanel.getKnob(2).setVisible(false);
        effectPanel.getKnob(3).setVisible(false);
    };

    //Vibrato
    vibratoButton.onClick = [this]{
        activeEffect = ActiveEffect::Vibrato;
        effectPanel.setTitle("VIBRATO");

        effectPanel.getKnob(0).configure(
            "Rate",
            0.1,
            10.0,
            vibrato.getRate(),
            0.1
    );

    effectPanel.getKnob(1).configure(
        "Depth",
        0.5,
        10.0,
        vibrato.getDepth(),
        0.1
    );

    effectPanel.getKnob(2).configure(
        "Mix",
        0.0,
        1.0,
        vibrato.getMix(),
        0.01
    );

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(false);

    };

    //Echo
    echoButton.onClick = [this]{
        activeEffect = ActiveEffect::Echo;
        effectPanel.setTitle("ECHO");

        effectPanel.getKnob(0).configure(
            "Time",
            100.0,
            1500.0,
            echo.getTime(),
            1.0
    );

    effectPanel.getKnob(1).configure(
        "Feedback",
        0.0,
        0.9,
        echo.getFeedback(),
        0.01
    );

    effectPanel.getKnob(2).configure(
        "Mix",
        0.0,
        1.0,
        echo.getMix(),
        0.01
    );

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(false);
    };

    //Three Tap Echo
    threeButton.onClick = [this]{
        activeEffect = ActiveEffect::ThreeTapEcho;
        effectPanel.setTitle("THREE TAP ECHO");

    effectPanel.getKnob(0).configure(
        "Time",
        100.0,
        1000.0,
        threeTapEcho.getTime(),
        1.0
    );

    effectPanel.getKnob(1).configure(
        "Feedback",
        0.0,
        0.8,
        threeTapEcho.getFeedback(),
        0.01
    );

    effectPanel.getKnob(2).configure(
        "Mix",
        0.0,
        1.0,
        threeTapEcho.getMix(),
        0.01
    );

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(false);
    };

    //Ring Modulator
    ringButton.onClick = [this]{
        activeEffect = ActiveEffect::RingModulator;
        effectPanel.setTitle("RING MODULATOR");

    effectPanel.getKnob(0).configure(
        "Frequency",
        20.0,
        2000.0,
        ringModulator.getFrequency(),
        1.0
    );

    effectPanel.getKnob(1).configure(
        "Mix",
        0.0,
        1.0,
        ringModulator.getMix(),
        0.01
    );

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(false);
    effectPanel.getKnob(3).setVisible(false);
    };

    //Vocal Doubler
    vocalButton.onClick = [this]{
        activeEffect = ActiveEffect::VocalDoubler;
        effectPanel.setTitle("VOCAL DOUBLER");

    effectPanel.getKnob(0).configure(
        "Delay",
        5.0,
        30.0,
        vocalDoubler.getDelay(),
        1.0
    );

    effectPanel.getKnob(1).configure(
        "Width",
        0.0,
        1.0,
        vocalDoubler.getWidth(),
        0.01
    );

    effectPanel.getKnob(2).configure(
        "Mix",
        0.0,
        1.0,
        vocalDoubler.getMix(),
        0.01
    );
    
    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(false);

    };

    //Pitch Shifter
    pitchButton.onClick = [this]{
        activeEffect = ActiveEffect::PitchShifter;
        effectPanel.setTitle("PITCH SHIFTER");

    effectPanel.getKnob(0).configure(
        "Pitch",
        -12.0,
        12.0,
        pitchShifter.getPitch(),
        1.0
    );

    effectPanel.getKnob(1).configure(
        "Mix",
        0.0,
        1.0,
        pitchShifter.getMix(),
        0.01
    );

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(false);
    effectPanel.getKnob(3).setVisible(false);

    };

    harmonizerButton.onClick = [this]{
        activeEffect = ActiveEffect::Harmonizer;
        effectPanel.setTitle("HARMONIZER");

    effectPanel.getKnob(0).configure(
        "Scale",
        0.0,
        1.0,
        harmonizer.getScale(),
        1.0
    );

    effectPanel.getKnob(1).configure(
        "Mix",
        0.0,
        1.0,
        harmonizer.getMix(),
        0.01
    );

    effectPanel.getKnob(2).configure(
        "Level",
        0.0,
        1.0,
        harmonizer.getLevel(),
        0.01
    );

    effectPanel.getKnob(0).setVisible(true);
    effectPanel.getKnob(1).setVisible(true);
    effectPanel.getKnob(2).setVisible(true);
    effectPanel.getKnob(3).setVisible(false);


    };



    addChildComponent(effectPanel);

    setSize(600, 400);
}

MainComponent::~MainComponent(){
    shutdownAudio();
}

//==============================================================================

void MainComponent::paint(juce::Graphics& g){

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::FontOptions(16.0f));
    g.setColour(juce::Colours::white);

    if(!audioSetupComplete){

        g.drawText(
            "Audio Setup",
            getLocalBounds().removeFromTop(50),
            juce::Justification::centred,
            true
        );
    }
    else{

        g.drawText(
            "DSP Guitar Pedal",
            getLocalBounds().removeFromTop(40),
            juce::Justification::centred,
            true
        );
    }
}

//==============================================================================

void MainComponent::resized(){

    auto area = getLocalBounds();

    if(!audioSetupComplete){

        area.removeFromTop(50);
        auto buttonArea = area.removeFromBottom(60);

        audioDeviceSelector->setBounds(area.reduced(20));
        continueButton.setBounds(buttonArea.reduced(200,10));
    }
    else{

        auto selectorArea = area.removeFromLeft(150);
        int buttonHeight = 50;

        gainButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        distortionButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        compressorButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        autoWahButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        eqButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        delayButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        chorusButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        flangerButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        reverbButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        tremoloButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        vibratoButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        echoButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        threeButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        ringButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        vocalButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        pitchButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));
        harmonizerButton.setBounds(selectorArea.removeFromTop(buttonHeight).reduced(5));

        effectPanel.setBounds(area.reduced(10));
    }
}

//==============================================================================

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate){
    noiseGate.prepare(sampleRate);
    autowah.prepare(sampleRate, samplesPerBlockExpected, 2);
    eq.prepare(sampleRate);
    delay.prepare(sampleRate,samplesPerBlockExpected);
    chorus.prepare(sampleRate,samplesPerBlockExpected);
    flanger.prepare(sampleRate,samplesPerBlockExpected);
    reverb.prepare(sampleRate,samplesPerBlockExpected);
    tremolo.prepare(sampleRate,samplesPerBlockExpected);
    vibrato.prepare(sampleRate,samplesPerBlockExpected);
    echo.prepare(sampleRate,samplesPerBlockExpected);
    threeTapEcho.prepare(sampleRate,samplesPerBlockExpected);
    ringModulator.prepare(sampleRate,samplesPerBlockExpected);
    vocalDoubler.prepare(sampleRate,samplesPerBlockExpected);
    pitchShifter.prepare(sampleRate,samplesPerBlockExpected);
    harmonizer.prepare(sampleRate,samplesPerBlockExpected);
}

//==============================================================================

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill){
    auto* buffer = bufferToFill.buffer;

    if(buffer == nullptr)
        return;

    auto* inputData = buffer->getReadPointer(0,bufferToFill.startSample);

    peakLevel = 0.0f;
    float sumSquares = 0.0f;

    for(int sample = 0; sample < bufferToFill.numSamples;++sample){

        float inputSample = inputData[sample];
        float absoluteVal = std::abs(inputSample);

        if(absoluteVal > peakLevel)
            peakLevel = absoluteVal;

        sumSquares += inputSample * inputSample;
    }

    rmsLevel = std::sqrt(sumSquares / bufferToFill.numSamples);

    rmsDB = juce::Decibels::gainToDecibels(rmsLevel, -100.0f);


    // Process selected effect
    switch(activeEffect){

        case ActiveEffect::Gain:
            gainEffect.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;

        case ActiveEffect::NoiseGate:
            noiseGate.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;

        case ActiveEffect::Distortion:
            disort.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;

        case ActiveEffect::Compressor:
            compress.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;

        case ActiveEffect::AutoWah:
            autowah.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;

        case ActiveEffect::EQ:
            eq.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::Delay:
            delay.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::Chorus:
            chorus.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;

        case ActiveEffect::Flanger:
            flanger.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::Reverb:
            reverb.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::Tremolo:
            reverb.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::Vibrato:
            vibrato.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::Echo:
            echo.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::ThreeTapEcho:
            echo.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::RingModulator:
            ringModulator.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::VocalDoubler:
            vocalDoubler.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
        
        case ActiveEffect::PitchShifter:
            pitchShifter.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
            
        
        case ActiveEffect::Harmonizer:
            harmonizer.processBlock(*buffer, bufferToFill.startSample, bufferToFill.numSamples);
            break;
    }
}

void MainComponent::releaseResources(){
}