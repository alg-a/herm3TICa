#ifndef VHP_OSC
#define VHP_OSC

#include "ofMain.h"
#include "ofxOsc.h"

//--------------------------------------------------------
class VHPosc {
    public:
    
        //constructor
        VHPosc();
    
        // variables
    
        // OSC
        ofxOscReceiver  receiver;
        ofxOscSender    sender;
    
        // methods
        void setup(string _h, int _sp, int _rp);
        void update();
    
    private:
	
};
//--------------------------------------------------------

#endif 