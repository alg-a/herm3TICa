#ifndef _VHP_DATA
#define _VHP_DATA

#include "ofMain.h"

//--------------------------------------------------------
class VHPdata {
    public:
    
        //constructor
        VHPdata();
        VHPdata(int _x, int _y, int _w, int _h);
    
        // variables
        ofVec2f         vector;
        int             width;
        int             height;
        bool            active;
        bool            on;
        bool            value;
        string          type;
        ofColor         color;
        ofColor         grey;
    
         
        // methods
        void draw();
        private:
	
};
//--------------------------------------------------------

#endif