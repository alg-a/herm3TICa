#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void loadImage(string _image);
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
    
        int 				camWidth;
        int 				camHeight;
        int                 totalPixels;
        int                 w[6];
        int                 h[6];
        float                     th[6];
    
        // settings
        ofxXmlSettings settings;
    
        // info
        ofTrueTypeFont		font;
    
        // shaders
        ofShader            shader;
    
        // Fbo
        ofFbo                   Fbo[6];
        ofPixels                Pix[6];
        ofTexture               Texture[6];
    
        // images
        vector<ofImage>         tarot;
        int                     ntarot;
        bool                     showTarot;
    
};