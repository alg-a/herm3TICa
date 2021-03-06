#ifndef VHP_OSC
#define VHP_OSC

#include "ofMain.h"
#include "ofxOsc.h"
#include "VHPcam.h"

//--------------------------------------------------------
class VHPosc {
    public:
    
        //constructor
        VHPosc();
    
        // variables
    
        // OSC
        ofxOscReceiver  receiver;
        ofxOscSender    sender;
        ofxOscSender    remoteSender;
    
        // Settings
        int contrast;
    
        // methods
        void setup(string _h, string _rh, int _sp, int _rsp, int _rp);
        void update(VHPcam & _cam);
        void sendSettings(int _stela, int _show, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3, float _b, float _rb, float _rw);
    
    private:
	
};
//--------------------------------------------------------

#endif 