#include "VHPcontrast.h"

//constructor

//----------------------------------------------------------------	
VHPcontrast::VHPcontrast() {
}

// methods

//----------------------------------------------------------------	

void VHPcontrast::setup() {
    // conversion float values for input 0-255 values to use in functiona as constants
	for (int i=0; i<32; i++) {
		conversionValues[i] = 0.01 + 0.01*i;
	}
	for (int i=32; i<64; i++) {
		conversionValues[i] = conversionValues[31] + 0.02*(i-31);
	}
	for (int i=64; i<96; i++) {
		conversionValues[i] = conversionValues[63] + 0.04*(i-63);
	}
	for (int i=96; i<128; i++) {
		conversionValues[i] = conversionValues[95] + 0.08*(i-95);
	}
	for (int i=128; i<160; i++) {
		conversionValues[i] = conversionValues[127] + 0.16*(i-127);
	}
	for (int i=160; i<192; i++) {
		conversionValues[i] = conversionValues[159] + 0.32*(i-159);
	}
	for (int i=192; i<224; i++) {
		conversionValues[i] = conversionValues[191] + 0.64*(i-191);
	}
	for (int i=224; i<256; i++) {
		conversionValues[i] = conversionValues[223] + 1.28*(i-223);
	}
    // buffered calculations in a matrix for contrasteLineal, contrasteCoseno, contrasteExponencial
    
    unsigned char * val;
	for (int e=0; e<256; e++) {
        texture[e].allocate(256,256, GL_RGB);
        val = new unsigned char[256*256*3];
		for (int f=0; f<256; f++) {
			for (int i=0; i<256; i++) {
                int pos = f*256*3 + i*3;
				contrasteExponencial[i][e][f] = calculaExponencial(i, conversionValues[e], conversionValues[f]*10.0);
                val[pos] = calculaExponencial(i, conversionValues[e], conversionValues[f]*10.0);
                val[pos+1] = calculaExponencial(i, conversionValues[e], conversionValues[f]*10.0);
                val[pos+2] = calculaExponencial(i, conversionValues[e], conversionValues[f]*10.0);
                //cout << calculaExponencial(i, conversionValues[e], conversionValues[f]*10.0) << endl;
			}
		}
        texture[e].loadData(val, 256,256, GL_RGB);
	}

}

//----------------------------------------------------------------

void VHPcontrast::ajusteExponencial(unsigned char * _p, int _t, int _e[3], int _f[3]) {
	for (int i=0; i<_t; i+=3) {
		// 3) Consecución de alto contraste dinamico mediante funcion exponencial
		// contrasteExponencial[256][e][f];
		_p[i] = contrasteExponencial[_p[i]][_e[0]][_f[0]];
		_p[i+1] = contrasteExponencial[_p[i+1]][_e[1]][_f[1]];
		_p[i+2] = contrasteExponencial[_p[i+2]][_e[2]][_f[2]];
	}
}
void VHPcontrast::ajusteExponencial(unsigned char * _p, int _t, int _e, int _f) {
	for (int i=0; i<_t; i++) {
		// 3) Consecución de alto contraste dinamico mediante funcion exponencial
		// contrasteExponencial[256][e][f];
		_p[i] = contrasteExponencial[_p[i]][_e][_f];
	}
}
int VHPcontrast::ajusteExponencial(int _p, int _e, int _f) {
	return contrasteExponencial[_p][_e][_f];
}

//----------------------------------------------------------------

int VHPcontrast::calculaExponencial(int _p, float _e, float _f){
	float min_rgb_value = 255/(pow(255/_f,_e)+1);
	float rgb_value = 255/(pow((255-_p)/_f,_e)+1);
	rgb_value = 255 * (rgb_value - min_rgb_value)/(255 - min_rgb_value);
	return (int) rgb_value;
}

//----------------------------------------------------------------	