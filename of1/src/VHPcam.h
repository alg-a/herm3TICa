#ifndef VHP_CAM
#define VHP_CAM

#include "ofMain.h"
#include "ofxOpenCv.h"

//--------------------------------------------------------
class VHPcam {
    public:
    
        //constructor
        VHPcam();
    
        // variables
    
        // Cam
        ofVideoGrabber 		vidGrabber;
        ofxCvColorImage     imageBuffer;
        ofTexture			videoTexture;
        int 				camWidth;
        int 				camHeight;
        int                 totalPixels;
    
        // methods
        void setup(int _w, int _h, int _d, int _f);
        void update();
        void draw();
    
    private:
	
};
//--------------------------------------------------------

#endif 