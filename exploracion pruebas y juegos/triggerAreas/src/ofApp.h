#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "VHPtriggerArea.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // variables
    
        // Cam
        ofVideoGrabber 		vidGrabber;
        ofTexture			videoTexture;
        int 				camWidth;
        int 				camHeight;
        int                 totalPixels;
    
        // triggerArea
        VHPtriggerArea      area;
    
        // OSC
        ofxOscReceiver receiver;
    
        // info
        ofTrueTypeFont		font;
    
        // settings
        ofxXmlSettings XML;
		
};
