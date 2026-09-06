#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <functional>

class ParameterKnob : public juce::Component{
    public:
        ParameterKnob();

        void configure(const juce::String& parameterName, double minimum, double maximum, double defaultValue,
        double interval = 0.01);

        void setValue(double newValue);
        double getValue() const;

        void resized() override;

        std::function<void(float)> onValueChange;

    private:
            juce::Slider knob;
            juce::Label label;
};