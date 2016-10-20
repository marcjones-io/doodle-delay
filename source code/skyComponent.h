// doodle delay gui component by marc jones 2015
// for educational use only

#ifndef __JUCE_HEADER_EB03334879D3321C__
#define __JUCE_HEADER_EB03334879D3321C__

#include "JuceHeader.h"

class skyComponent  : public Component {
public:
    //contructor & destructor
    skyComponent ();
    ~skyComponent();

    //methods
    void paint (Graphics& g) override;
    void resized() override;

    // binary resources:
    static const char* clouds_png;
    static const int clouds_pngSize;
    static const char* paper_png;
    static const int paper_pngSize;
    static const char* raincloud_png;
    static const int raincloud_pngSize;
    static const char* text_png;
    static const int text_pngSize;
    static const char* heavyrain1_png;
    static const int heavyrain1_pngSize;
    static const char* heavyrain2_png;
    static const int heavyrain2_pngSize;
    static const char* heavyrain3_png;
    static const int heavyrain3_pngSize;
    static const char* heavyrain4_png;
    static const int heavyrain4_pngSize;
    static const char* heavyrain5_png;
    static const int heavyrain5_pngSize;
    static const char* ulightrain1_png;
    static const int ulightrain1_pngSize;
    static const char* ulightrain2_png;
    static const int ulightrain2_pngSize;
    static const char* ulightrain3_png;
    static const int ulightrain3_pngSize;
    static const char* ulightrain4_png;
    static const int ulightrain4_pngSize;
    static const char* ulightrain5_png;
    static const int ulightrain5_pngSize;
    static const char* med1_png;
    static const int med1_pngSize;
    static const char* med2_png;
    static const int med2_pngSize;
    static const char* med3_png;
    static const int med3_pngSize;
    static const char* med4_png;
    static const int med4_pngSize;
    static const char* med5_png;
    static const int med5_pngSize;

    Image paper, clouds, raincloud, text;
    Image heavyrain[5], medrain[5], ulightrain[5];


private:
    Image cachedImage_paper_png_1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (skyComponent)
};

#endif   // __JUCE_HEADER_EB03334879D3321C__
