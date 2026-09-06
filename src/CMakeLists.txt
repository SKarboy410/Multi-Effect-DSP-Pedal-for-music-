set(JUMAKE_TEMPLATE "GuiApplication")

juce_add_gui_app(${PROJECT_NAME}
    PRODUCT_NAME ${PROJECT_NAME})

target_sources(${PROJECT_NAME}

    PRIVATE
        Main.cpp
        MainComponent.cpp
        Effects/noiseGate.cpp
        Effects/gain.cpp
        Effects/distortion.cpp
        Effects/compressor.cpp
        Effects/autoWah.cpp
        Effects/eq.cpp
        Effects/delay.cpp
        Effects/chorus.cpp
        Effects/flanger.cpp
        Effects/reverb.cpp
        Effects/tremolo.cpp
        Effects/vibrato.cpp
        Effects/echo.cpp
        Effects/threeTapEcho.cpp
        Effects/ringModulator.cpp
        Effects/vocalDoubler.cpp
        Effects/pitchShifter.cpp
        Effects/harmonizer.cpp
        
        UI/parameterKnob.cpp
        UI/effectPanel.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        # JUCE_ASIO = 1
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_gui_extra
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
