#pragma once

#include "ofMain.h"

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
        ofTexture			textureSierpinski;
    
        unsigned char *     sierpinski;
    
        int 				camWidth;
        int 				camHeight;
        int                 totalPixels;
        int                 totalSierpinski;
    
        int					sierpinski_0[3];
        int					sierpinski_1[3][3][3];
        int					sierpinski_2[3][3][3][3][3];
        int					sierpinski_3[3][3][3][3][3][3][3];
        int					sierpinski_4[3][3][3][3][3][3][3][3][3];
    
        int                 base;
        int                 sizeSierpinski_0;
        int                 sizeSierpinski_1;
        int                 sizeSierpinski_2;
        int                 sizeSierpinski_3;
        int                 sizeSierpinski_4;
        int                 n[6];
    
    
};
