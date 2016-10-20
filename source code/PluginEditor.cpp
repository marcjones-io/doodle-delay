#include "PluginEditor.h"

PluginEditor::PluginEditor (Mu45effectAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)  {
    
    feedbackSlider = new Slider ("Feedback Slider");
    feedbackSlider->setRange(processor.feedbackPCT->getActualMinimum(),
                             processor.feedbackPCT->getActualMaximum(), 1);
    feedbackSlider->setTextValueSuffix(processor.feedbackPCT->getLabel());
    feedbackSlider->setSliderStyle(Slider::LinearHorizontal);
    feedbackSlider->setColour (Slider::thumbColourId, Colours::black);
    feedbackSlider->setColour (Slider::trackColourId, Colours::black);
    feedbackSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    feedbackSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    feedbackSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x404d4d4d));
    feedbackSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    feedbackSlider->addListener (this);
    
    wetDrySlider = new Slider ("Wet/Dry Slider");
    wetDrySlider->setRange(processor.wetDryPCT->getActualMinimum(),
                           processor.wetDryPCT->getActualMaximum(), 1);
    wetDrySlider->setTextValueSuffix(processor.wetDryPCT->getLabel());
    wetDrySlider->setSliderStyle(Slider::LinearHorizontal);
    wetDrySlider->setColour (Slider::thumbColourId, Colours::black);
    wetDrySlider->setColour (Slider::trackColourId, Colours::black);
    wetDrySlider->setColour (Slider::textBoxTextColourId, Colours::black);
    wetDrySlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    wetDrySlider->setColour (Slider::textBoxHighlightColourId, Colour (0x404d4d4d));
    wetDrySlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    wetDrySlider->addListener (this);
    
    delayTimeSlider = new Slider ("Delay Slider");
    delayTimeSlider->setRange(processor.delayTimeInMS->getActualMinimum(),
                              processor.delayTimeInMS->getActualMaximum(), 1);
    delayTimeSlider->setTextValueSuffix(processor.delayTimeInMS->getLabel());
    delayTimeSlider->setSliderStyle(Slider::LinearHorizontal);
    delayTimeSlider->setColour (Slider::thumbColourId, Colours::black);
    delayTimeSlider->setColour (Slider::trackColourId, Colours::black);
    delayTimeSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    delayTimeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    delayTimeSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x404d4d4d));
    delayTimeSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00ffffff));
    delayTimeSlider->addListener(this);

    addAndMakeVisible(feedbackSlider); addAndMakeVisible(wetDrySlider);
    addAndMakeVisible(delayTimeSlider);
    
    //used to cycle through arrays of pngs
    rain_index = rand() % 4 + 1;
    
    setSize (700, 400);
    startTimer(100);    // This sets how often (in msec) the timerCallback() gets called which directly affects animation
}

PluginEditor::~PluginEditor() {     }

//==============================================================================

void PluginEditor::paint (Graphics& g)    {
    
    //draw background paper texture
    g.setOpacity(1);
    g.drawImage (skyComponent().paper,0, 0, 700, 400, 0, 0, 700, 400);
    
    //reset to full opacity & check for heavy, medium, or light rain -> rain "gif" cycle
    g.setOpacity(1);
    rain_index++;
    if (rain_index > 4) {rain_index = 0;}
    if ( processor.wetGain > .93 ) {
        g.drawImage(skyComponent().heavyrain[rain_index], 0, 0, 700, 400, 0, 0, 700, 400);
    }  else if (processor.wetGain > .82) {
            if (processor.wetGain == .82) { g.drawImage(skyComponent().medrain[rain_index], 0, 0, 700, 400, 0, 0, 700, 400); }
            else if (processor.wetGain > .82) {
                if( rain_index%2==0 ){ g.drawImage(skyComponent().medrain[rain_index], processor.wetGain*496-250, 0, 700, 400, 0, 0, 700, 400); }
                else { g.drawImage(skyComponent().heavyrain[rain_index], 0, 0, processor.wetGain*496+250, 400, 0, 0, 700, 400);   }
            }
    }   else if (processor.wetGain > .61) {
            if (processor.wetGain == .61) { g.drawImage(skyComponent().medrain[rain_index], 0, 0, 700, 400, 0, 0, 700, 400); }
            else if (processor.wetGain > .61) {
                g.drawImage(skyComponent().medrain[rain_index], processor.wetGain*496-250, 0, 700, 400, 0, 0, 700, 400); }
    }   else if (processor.wetGain > .48) {
            if (processor.wetGain == .48) { g.drawImage(skyComponent().ulightrain[rain_index], 0, 0, 700, 400, 0, 0, 700, 400); }
            else if (processor.wetGain > .48) {
                g.drawImage(skyComponent().ulightrain[rain_index], processor.wetGain*496-250, 0, 700, 400, 0, 0, 700, 400); }
    }
    
    //check if its wet, we may need more clouds
    if (processor.wetGain > .93)
        g.drawImage(skyComponent().raincloud, 480, 10, 171, 123, 0, 0, 171, 123);
    if (processor.wetGain > .8)
        g.drawImage(skyComponent().raincloud, 415, 16, 171, 123, 0, 0, 171, 123);
    
    //og raincloud - always with us
    g.drawImage(skyComponent().raincloud, processor.wetGain*496+16, 16, 171, 123, 0, 0, 171, 123);
    
    //draw text into foreground
    g.drawImage(skyComponent().text, 0, 0, 700, 400, 0, 0, 700, 400);
    
    //scale the wet gain with the stormy texture (scaled up to 40% opacity = 65% wet)
    if ( processor.wetGain > .65 ) {
        g.setOpacity(.4);
    } else {
        g.setOpacity(processor.wetGain/1.625);
    }
    
    //draw stormy cloud texture
    g.drawImage (skyComponent().clouds, 0, 0, 700, 400, 0, 0, 700, 400);
    g.setColour (Colours::black);
    
}

void PluginEditor::resized()      {
    delayTimeSlider->setBounds(10, 265, 160, 25);
    feedbackSlider->setBounds(10, 295, 160, 25);
    wetDrySlider->setBounds(10, 370, getWidth()-10, 15);
}

void PluginEditor::sliderValueChanged(Slider* slider)     {
    PluginParameter* parameter = nullptr;
    if (slider == wetDrySlider) {
        parameter = processor.wetDryPCT;
    } else if (slider == delayTimeSlider) {
        parameter = processor.delayTimeInMS;
    } else if (slider == feedbackSlider) {
        parameter = processor.feedbackPCT;
    }
    if (parameter != nullptr) {
        parameter->setValueNotifyingHost(parameter->calculateValue(slider->getValue()));
    }
}

void PluginEditor::timerCallback()    {
    wetDrySlider->setValue(processor.wetDryPCT->getActualValue(), dontSendNotification);
    feedbackSlider->setValue(processor.feedbackPCT->getActualValue(), dontSendNotification);
    delayTimeSlider->setValue(processor.delayTimeInMS->getActualValue(), dontSendNotification);
    repaint(); // <- this method here allows for the conditional structure in the original paint method
}
