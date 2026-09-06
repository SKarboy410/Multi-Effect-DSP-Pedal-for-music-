#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "parameterKnob.h"

class EffectPanel : public juce::Component{
    public:
        EffectPanel();

        void setTitle(const juce::String& newTitle);
        ParameterKnob& getKnob(int index);
        void resized() override;
    
    private:
        juce::Label title;

        ParameterKnob knob1;
        ParameterKnob knob2;
        ParameterKnob knob3;
        ParameterKnob knob4;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectPanel)
};
