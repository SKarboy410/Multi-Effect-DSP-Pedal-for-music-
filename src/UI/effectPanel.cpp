#include "effectPanel.h"

EffectPanel::EffectPanel(){

    title.setJustificationType(juce::Justification::centred);
    title.setFont(juce::FontOptions(22.0f));

    addAndMakeVisible(title);

    addAndMakeVisible(knob1);
    addAndMakeVisible(knob2);
    addAndMakeVisible(knob3);
    addAndMakeVisible(knob4);
}

void EffectPanel::setTitle(const juce::String& newTitle){
    title.setText(newTitle, juce::dontSendNotification);
}

ParameterKnob& EffectPanel::getKnob(int index){
    switch(index){
        case 0: return knob1;
        case 1: return knob2;
        case 2: return knob3;
        case 3: return knob4;

        default: return knob1;
    }
}

void EffectPanel::resized(){
    auto area = getLocalBounds();
    auto titleArea = area.removeFromTop(50);

    title.setBounds(titleArea);

    auto topRow = area.removeFromTop(area.getHeight()/2);
    auto bottomRow = area;
    auto knobWidth = area.getWidth()/2;

    knob1.setBounds(topRow.removeFromLeft(knobWidth));
    knob2.setBounds(topRow);
    knob3.setBounds(bottomRow.removeFromLeft(knobWidth));
    knob4.setBounds(bottomRow);
}