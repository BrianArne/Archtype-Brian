cmake_minimum_required(VERSION 3.15)

project(ArcheTypeBrian VERSION 0.0.1)

add_subdirectory(external/JUCE)

juce_add_plugin(ArcheTypeBrian
    PLUGIN_MANUFACTURER_CODE LRat
    PUGIN_CODE Ratt
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "ArcheTypeBrian"
    COPY_PLUGIN_AFTER_BUILD 1)

juce_add_binary_data(images
    SOURCES "images/Pedal.png" "images/Button.png")

set(SRC "../src")
target_sources(ArcheTypeBrian
    PRIVATE
        ${SRC}/PluginEditor.h
        ${SRC}/PluginEditor.cpp
        ${SRC}/PluginProcessor.h
        ${SRC}/PluginProcessor.cpp
        ${SRC}/ScopeComponent.h
        ${SRC}/ScopeComponent.cpp)

target_compile_definitions(ArcheTypeBrian
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

juce_generate_juce_header(ArcheTypeBrian)

target_link_libraries(ArcheTypeBrian
    PRIVATE
        juce::juce_audio_utils
        images
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)


