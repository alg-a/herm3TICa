#pragma once

#include "ofMain.h"
#include "VHPsierpinski.h"
#include "ofxOsc.h"

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
    
        ofVideoGrabber 		vidGrabber;
    
        ofTexture			videoTexture;
        VHPsierpinski       sierpinski;
    
        int 				camWidth;
        int 				camHeight;
        int                 totalPixels;
        
        ofxOscReceiver receiver;
    
        // info
        ofTrueTypeFont		font;
    
};
