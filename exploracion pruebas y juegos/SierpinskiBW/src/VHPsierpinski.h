#ifndef VHP_SIERPINSKI
#define VHP_SIERPINSKI

#include "ofMain.h"
#include "VHPdata.h"
#include "ofxOsc.h"

//--------------------------------------------------------
class VHPsierpinski {
    public:
    
        //constructor
        VHPsierpinski();
    
        // variables
        ofTexture			textureSierpinski;      // video texture
        unsigned char *     sierpinski;             // buffer
    
        VHPdata				sierpinski_0;
        VHPdata				sierpinski_1[3][3];
        VHPdata				sierpinski_2[3][3][3][3];
        VHPdata				sierpinski_3[3][3][3][3][3][3];
        VHPdata				sierpinski_4[3][3][3][3][3][3][3][3];
        int                 base;
        int                 sizeSierpinski_0;
        int                 sizeSierpinski_1;
        int                 sizeSierpinski_2;
        int                 sizeSierpinski_3;
        int                 sizeSierpinski_4;
        int                 totalSierpinski;
        
        int                 threshold;
        ofxOscSender        sender;
        vector<VHPdata*>    active;
    
        // methods
        void setup();
        void update(int _w, int _t, unsigned char * _p);
        void updateSierpinski(VHPdata & _s, int _t, int _i);
        void store(int _w, int _t, unsigned char * _p);
        void average(int _w, int _t, unsigned char * _p);
        void draw();
        void setThreshold(int _t);
    
    private:
	
};
//--------------------------------------------------------

#endif 