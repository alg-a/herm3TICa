#ifndef _VHP_CONTRAST
#define _VHP_CONTRAST

#include "ofMain.h"

//--------------------------------------------------------
class VHPcontrast {
    public:
    
        //constructor
        VHPcontrast();
        
        // variables
        float       conversionValues	[256];              // conversion values for constants input values
        int         contrasteExponencial [256][256][256];   //	already calculated data for matrix conversion
        ofTexture   texture[256];
    
        // methods
        void        setup();
        void        ajusteExponencial(unsigned char * _p, int _t, int _e[3], int _f[3]);
        void        ajusteExponencial(unsigned char * _p, int _t, int _e, int _f);
        int         ajusteExponencial(int _p, int _e, int _f);
        int         calculaExponencial (int p, float e, float f);
    
    private:
	
};
//--------------------------------------------------------

#endif 