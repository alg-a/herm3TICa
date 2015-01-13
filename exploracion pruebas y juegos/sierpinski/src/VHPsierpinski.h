#ifndef VHP_SIERPINSKI
#define VHP_SIERPINSKI

#include "ofMain.h"

//--------------------------------------------------------
class VHPsierpinski {
    public:
    
        //constructor
        VHPsierpinski();
    
        // variables
        ofTexture			textureSierpinski;      // video texture
        unsigned char *     sierpinski;             // buffer
    
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
        int                 totalSierpinski;
    
        // methods
        void setup();
        void resetArrays();
        void update(int _w, int _t, unsigned char * _p);
        void store(int _w, int _t, unsigned char * _p);
        void average(int _w, int _t, unsigned char * _p);
        void draw();
    
    private:
	
};
//--------------------------------------------------------

#endif 