#include "parameterKnob.h"

ParameterKnob::ParameterKnob(){

    knob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    knob.setRange(0.0, 1.0, 0.01);
    knob.onValueChange = [this]{
        if (onValueChange){
            onValueChange(
                static_cast<float>(knob.getValue()));
        }
    };

    addAndMakeVisible(knob);

    label.setJustificationType(juce::Justification::centred);
    label.setText("Parameter", juce::dontSendNotification);

    addAndMakeVisible(label);
}

void ParameterKnob::configure(const juce::String& parameterName, double minimum, double maximum, double defaultValue,
    double interval){

        label.setText(parameterName, juce::dontSendNotification);
        knob.setRange(minimum, maximum, interval);
        knob.setValue(defaultValue, juce::dontSendNotification);

}

void ParameterKnob::setValue(double newValue){
    knob.setValue(newValue, juce::dontSendNotification);
}

double ParameterKnob::getValue() const{
    return knob.getValue();
}

void ParameterKnob::resized(){
    auto area = getLocalBounds();
    auto labelArea = area.removeFromTop(25);

    label.setBounds(labelArea);
    knob.setBounds(area);
}