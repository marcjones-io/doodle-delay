#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Math.h"

//constructor
PluginProcessor::PluginProcessor()    {
    /**    initialize plugin paramters an set default vaulues
     Param = new PP( Paramter_ID, Default_Value, Minimum_Value, Maximum_Value, Parameter_Name, Parameter_Label )**/
    wetDryPCT = new PluginParameter("wetDry", 0, 0, 100, "wet_dry_pct", "%");
    feedbackPCT = new PluginParameter("feedback", 0, 0, 95, "feedback_pct", "%");
    delayTimeInMS = new PluginParameter("delayTime", 1, 1, 999, "delayTimeInMS", "ms");
    addParameter(delayTimeInMS); addParameter(feedbackPCT); addParameter(wetDryPCT);
}

//destructor
PluginProcessor::~PluginProcessor()   {   }

// function to calculate delay in samples from the given time (ms) value
void PluginProcessor::calcDelays(){
    float ms = delayTimeInMS->getActualValue();
    int lsamples = calcSampsFromMS(ms);
    int rsamples = calcSampsFromMS(ms);
    leftDelayLine.setDelay(lsamples);
    rightDelayLine.setDelay(rsamples);

}

// function to calculate how much wet vs dry signal is outputted
void PluginProcessor::calcGains(){
    wetGain = 0.01 * wetDryPCT->getActualValue();
    dryGain = 1-wetGain;
}

// function called in process block to combine above functions into a cleaner line of code
void PluginProcessor::calcAlgorithmParams()    {
    feedback = 0.01 * feedbackPCT->getActualValue();
    calcDelays();
    calcGains();
}

// function to initialize delays and gain parameters before output is released
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)  {
    fs = sampleRate;
    int lsamples = calcSampsFromMS(delayTimeInMS->getActualValue());
    int rsamples = calcSampsFromMS(delayTimeInMS->getActualValue());
    leftDelayLine.setMaximumDelay(lsamples);
    rightDelayLine.setMaximumDelay(rsamples);
    calcGains();
}



// main loop for the plugin
void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)       {
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    calcAlgorithmParams();

    float* left = buffer.getWritePointer (0);
    float* right = buffer.getWritePointer (1);
    const int numSamps = buffer.getNumSamples();

    
    for (int samp = 0; samp < numSamps; samp++)     {

        //ping pong delay
        tempL = leftDelayLine.nextOut();
        tempR = rightDelayLine.nextOut();
        
        tempL = leftDelayLine.tick(right[samp]+feedback*tempL);
        tempR = rightDelayLine.tick(left[samp]+feedback*tempR);
        
        left[samp] = (dryGain * left[samp]) + (wetGain  *tempL);
        right[samp] = (dryGain * right[samp]) + (wetGain *tempR);
    }
}

bool PluginProcessor::hasEditor() const    {   return true;    }

AudioProcessorEditor* PluginProcessor::createEditor() { return new PluginProcessorEditor (*this); }

void PluginProcessor::getStateInformation (MemoryBlock& destData)  {   }

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)  {   }

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {   return new PluginProcessor();  }

const String PluginProcessor::getName() const  {   return JucePlugin_Name;     }

bool PluginProcessor::acceptsMidi() const  {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::silenceInProducesSilenceOut() const {   return false;   }

double PluginProcessor::getTailLengthSeconds() const{   return 0.0; }

int PluginProcessor::getNumPrograms() { return 1; }

int PluginProcessor::getCurrentProgram() {   return 0;   }

void PluginProcessor::setCurrentProgram (int index) { }

const String PluginProcessor::getProgramName (int index) { return String(); }

void PluginProcessor::changeProgramName (int index, const String& newName) {   }

int PluginProcessor::calcSampsFromMS(float ms) {    return ms/1000*fs;      }

void PluginProcessor::releaseResources()  {    }
