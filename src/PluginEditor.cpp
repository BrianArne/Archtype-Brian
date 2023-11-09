#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), oscScope(p.getAudioBufferQueue())
{
    addAndMakeVisible (gainDial);
    gainDial.setRange (-6.0f, 24.0f);
    gainDial.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainDial.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "GAIN", gainDial);
    
    auto pedal = juce::ImageCache::getFromMemory(BinaryData::Button_png, BinaryData::Button_pngSize);
    bypassButton.setImages(true,
                           false,
                           true,
                           pedal,
                           1.0f,
                           juce::Colours::transparentWhite,
                           pedal,
                           1.0f,
                           juce::Colours::transparentWhite,
                           pedal,
                           1.0f,
                           juce::Colours::transparentWhite);
    bypassButton.setToggleable(true);
    bypassButton.addListener(this);
    
    addAndMakeVisible(bypassButton);
    
    addAndMakeVisible(oscScope);
    
    setSize (350, 600);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    auto pedal = juce::ImageCache::getFromMemory(BinaryData::Pedal_png, BinaryData::Pedal_pngSize);
    g.drawImageWithin(pedal, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit, false);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    auto knobs = bounds.removeFromTop(bounds.getHeight() / 3.6);
    auto leftSide = knobs.removeFromLeft(knobs.getWidth() / 2.12);
    leftSide.removeFromTop(40);
    gainDial.setBounds(leftSide);
    
    auto oscBounds = bounds.removeFromTop(bounds.getHeight() / 1.8);
    oscBounds.removeFromLeft(25);
    oscBounds.removeFromRight(20);
    oscScope.setBounds(oscBounds);
    
    bypassButton.setBounds(bounds.removeFromTop(115));
}

void AudioPluginAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &bypassButton) {
        auto bypass = processorRef.bypass.get();
        processorRef.bypass.set(!bypass);
    }
}
