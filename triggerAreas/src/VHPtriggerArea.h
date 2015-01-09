#ifndef VHP_TRIGGERAREA
#define VHP_TRIGGERAREA

#include "ofMain.h"
#include "VHPdata.h"
#include "ofxOsc.h"

//--------------------------------------------------------
class VHPtriggerArea {
    public:
    
        //constructor
        VHPtriggerArea();
    
        // variables
        int x;
        int y;
        int width;
        int height;
        int size;
        VHPdata data;
        int                 threshold;
        ofxOscSender        sender;
    
        // methods
        void setup(int _x, int _y, int _w, int _h, string _host, int _port, string _address);
        void setPosition(int _x, int _y);
        int getX();
        int getY();
    
        void setSize(int _w, int _h);
        void setWidth(int _w);
        void setHeight(int _h);
        int getWidth();
        int getHeight();
    
        void update(int _w, int _h, int _t, unsigned char * _p);
        void draw();
        void setThreshold(int _t);
    
    private:
	
};
//--------------------------------------------------------

#endif 