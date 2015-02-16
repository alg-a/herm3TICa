#ifndef _VHP_SIERPINSKI
#define _VHP_SIERPINSKI

#include "ofMain.h"
#include "VHPdata.h"
#include "ofxOsc.h"
#include "VHPhttpJson.h"

//--------------------------------------------------------
class VHPsierpinski {
    public:
    
        //constructor
        VHPsierpinski();
        
        // variables
        vector<VHPdata>             L_0;
        vector<VHPdata>             L_1;
        vector<VHPdata>             L_2;
        int                         threshold;
    
        // Json
        VHPhttpJson                 streamer;
        string                      data;
        string                      last;
    
        // methods
        void init();
        void draw();
        void update(const unsigned char * _l0, const unsigned char * _l1, const unsigned char * _l2, ofxOscSender & _sender);
        void updateData(VHPdata & _d, int _r, int _g, int _b, ofxOscSender & _sender);
        void updateStreamerData(VHPdata & _d, int _on, ofxOscSender & _sender);
        void setActive(int _l, int _n, int _a, int _t);
        void setThreshold(int _t);
        void sendJson();
    
    private:
	
};
//--------------------------------------------------------

#endif 