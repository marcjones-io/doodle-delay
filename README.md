# doodle-delay
Custom illustrated &amp; animated VST/AU plugins written in C++

![Alt text](relative/path/to/img.screenshots.jpg?raw=true "Title")

### about:
Doodle delay is a creative peice in the form of a freeware audio effects processor. The plugin was built atop the JUCE Frameworks, using Xcode & Stanford's Synthesis Toolkit (Lite version 4.5.1). The illustrations are custom drawn and animated to a flip-book effect by iterating through an array of image objects represented in binary data - which saves memory and computation time. The 

### instructions:
Place the doodledelay.vst or .au file in the respective system plugin's folder. The plug-ins should then be accessible to your DAW (digital audio workstation). If your DAW can import plugins from a custom folder, feel free to do so without altering your system plugin folders. The provided source code is intended to serve as inspiration for anyone interested in creating a gif style animation in C++ or using JUCE. The code is for educational use only and will not compile as many project files were not included.

### notes:
For more information on the JUCE framework:
https://www.juce.com/features

For more information on the Stanford Synthesis ToolKit:
https://ccrma.stanford.edu/software/stk/
