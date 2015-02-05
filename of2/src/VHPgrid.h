#ifndef _VHP_GRID
#define _VHP_GRID

#include "ofMain.h"
#include "VHPdata.h"

//--------------------------------------------------------
class VHPgrid {
    public:
    
        //constructor
        VHPgrid();
    
        // variables
        vector<VHPdata>             area;
        int                         size;
        int                         width;
        int                         height;
        int                         pixW;
        int                         pixH;
        ofVec2f                     vector;
    
        // methods
        void init(int _w, int _h, int _aw, int _ah);
        void draw();
        void update(const unsigned char * _d, int _o);
        ofVec2f getVector();
    
    private:
	
};
//--------------------------------------------------------

#endif 