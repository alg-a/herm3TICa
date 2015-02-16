#ifndef _VHP_HIEROFANTE
#define _VHP_HIEROFANTE

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"

//--------------------------------------------------------
class VHPhierofante {
    public:
    
        //constructor
        VHPhierofante();
        
        // variables
        ofVec3f center;
        int n;
        vector<ofImage> img_hierofante;
        vector<ofVec2f> img_margin;
        vector<ofVec2f> img_position;
        vector<ofVec2f> img_size;
        ofVec2f mouth;
        ofVec2f eyes;
        ofVec2f eyebrow;
        float jaw;
        ofxOscReceiver  receiver;
    
        // methods
        void setup(ofxXmlSettings _settings);
    
        void update();
    
        void scaleEyeL(float _l);
        void scaleEyeR(float _r);
        void scaleMouthW(float _w);
        void scaleMouthH(float _h);
        void scaleEyebrowW(float _w);
        void scaleEyebrowHL(float _h);
        void scaleEyebrowHR(float _h);
        void scaleJaw(float _j);
        void setCenter(float _x, float _y);
        void setScale(float _z);
    
        void draw();
    
    private:
	
};
//--------------------------------------------------------

#endif 