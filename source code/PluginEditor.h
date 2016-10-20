
#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "skyComponent.H"


class PluginEditor  : public AudioProcessorEditor,
public Slider::Listener,
public Timer {
public:
    PluginEditor (Mu45effectAudioProcessor&);
    ~PluginEditor();
    
    void paint (Graphics&) override;
    void paintGreen (Graphics&);

    void resized() override;
    void sliderValueChanged(Slider*) override;
    void timerCallback() override;
    
    int w = 100, rain_index;
    
private:
    Mu45effectAudioProcessor& processor;
    
    ScopedPointer<Slider> feedbackSlider;
    ScopedPointer<Slider> delayTimeSlider;
    ScopedPointer<Slider> wetDrySlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
