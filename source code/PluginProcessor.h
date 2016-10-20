#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginParameter.h"
#include "Delay.h"


class PluginProcessor  : public AudioProcessor {
public:
    PluginProcessor();
    ~PluginProcessor();
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    const String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;
    
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    PluginParameter* wetDryPCT;
    PluginParameter* feedbackPCT;
    PluginParameter* delayTimeInMS;
    
    float _DEBUGASSISTVALUE_, _DEBUGASSISTVALUE2_;
    float wetGain, feedback, leftDelay, dryGain, tempL, tempR;

    
private:
    stk::Delay rightDelayLine, leftDelayLine; // uses delays creaetd with Stanford's Synthesis Toolkit (stklite 4.5.1)
    float fs; // the sample rate of the DAW
    
    void calcAlgorithmParams();
    int calcSampsFromMS(float ms);
    void calcDelays();
    void calcGains();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
