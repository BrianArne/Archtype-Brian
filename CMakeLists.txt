cmake_minimum_required(VERSION 3.15)

project(ArcheTypeBrian VERSION 0.0.1)

add_subdirectory(external/JUCE)

juce_add_plugin(ArcheTypeBrian
    PLUGIN_MANUFACTURER_CODE LRat
    PUGIN_CODE Ratt
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "ArcheTypeBrian")

set(SRC "../src")
target_sources(ArcheTypeBrian
    PRIVATE
        ${SRC}/PluginEditor.cpp
        ${SRC}/PluginProcessor.cpp)

target_compile_definitions(ArcheTypeBrian
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

  target_link_libraries(ArcheTypeBrian
      PRIVATE
          juce::juce_audio_utils
      PUBLIC
          juce::juce_recommended_config_flags
          juce::juce_recommended_lto_flags
          juce::juce_recommended_warning_flags)


