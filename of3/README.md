#of3 - Narrative - herm3TICa
===========================

### About
OpenFrameworks application to show the performer a mixture of video and images as a result of what he/she is doing during herm3TICa event

Attribution-NonCommercial-ShareAlike 3.0
http://creativecommons.org/licenses/by-nc-sa/3.0/

Created by Horacio González Diéguez for [herm3TICa](http://herm3tica.tv/) project and licensed under Creative Commons

Contributors:


Date: Fri Jan 30 2015


Enjoy the code and drop us a line for comments and questions!
horaciogd at vhplab dot net


### How to

	1. Create an openframeworks project adding the following addons ofxOsc + ofxXmlSettings.
	2. Copy and remplace main.cpp, ofApp.cpp and ofApp.h from the repository to the src folder of your project.
	3. Add the remaining files (ofxVideoRecorder.cpp, ofxVideoRecorder.h, VHPcam.cpp, VHPcam.h, VHPcontrast.cpp, VHPcontrast.h, VHPosc.cpp, VHPosc.h) to your project.
	4. Copy the data folder from the repository to the bin folder of your project.
	5. Edit mySettings.xml to update FFMPEG field where you should have the full path to ffmpeg in your computer.
	
	
### Requirements

of3 uses [ofxVideoRecorder](https://github.com/timscaffidi/ofxVideoRecorder) by Timothy Scaffidi (already included) in order to record from frame buffer objects so you must have [ffmpeg](http://ffmpeg.org/) installed.