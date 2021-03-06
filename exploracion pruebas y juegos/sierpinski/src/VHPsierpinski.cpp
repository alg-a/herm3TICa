#include "VHPsierpinski.h"

//constructor

//----------------------------------------------------------------	
VHPsierpinski::VHPsierpinski() {
    
}

// methods

//----------------------------------------------------------------
void VHPsierpinski::setup() {
    base                = 3;
    sizeSierpinski_4    = base * 3; // 9
    sizeSierpinski_3    = base * 3 * 3; // 27
    sizeSierpinski_2    = base * 3 * 3 * 3; // 81
    sizeSierpinski_1    = base * 3 * 3 * 3 * 3; // 243
    sizeSierpinski_0    = base * 3 * 3 * 3 * 3 * 3; // 729
    totalSierpinski     = sizeSierpinski_0 * sizeSierpinski_0 * 3; // Width * Height * RGB
    
    textureSierpinski.allocate(sizeSierpinski_0, sizeSierpinski_0, GL_RGB);
    sierpinski = new unsigned char[sizeSierpinski_0 * sizeSierpinski_0 * 3];
    
    // initializing storage arrays
    resetArrays();
}

//----------------------------------------------------------------
void VHPsierpinski::resetArrays() {
    memset(sierpinski_0, 0, sizeof(sierpinski_0));
    memset(sierpinski_1, 0, sizeof(sierpinski_1));
    memset(sierpinski_2, 0, sizeof(sierpinski_2));
    memset(sierpinski_3, 0, sizeof(sierpinski_3));
    memset(sierpinski_4, 0, sizeof(sierpinski_4));

}

//----------------------------------------------------------------
void VHPsierpinski::update(int _w, int _t, unsigned char * _p) {
    store(_w, _t, _p);
    average(_w, _t, _p);
    textureSierpinski.loadData(sierpinski, sizeSierpinski_0, sizeSierpinski_0, GL_RGB);
}

//----------------------------------------------------------------
void VHPsierpinski::store(int _w, int _t, unsigned char * _p) {
    resetArrays();
    for (int i=0; i<totalSierpinski; i+=3){
        int n = sizeSierpinski_0 * 3;
        int x = i % n;
        int y = (i - x) / n;
        int pos = (y * _w * 3 + x)%_t;
        n = sizeSierpinski_1 * 3;
        int x_0r = x % n;
        int x_0 = (x - x_0r) / n;
        int y_0r = y % sizeSierpinski_1;
        int y_0 = (y - y_0r) / sizeSierpinski_1;
        if ((x_0==1)&&(y_0==1)) {
            sierpinski_0[0] += _p[pos];
            sierpinski_0[1] += _p[pos+1];
            sierpinski_0[2] += _p[pos+2];
        } else {
            n = sizeSierpinski_2 * 3;
            int x_1r = x_0r % n;
            int x_1 = (x_0r - x_1r) / n;
            int y_1r = y_0r % sizeSierpinski_2;
            int y_1 = (y_0r - y_1r) / sizeSierpinski_2;
            if ((x_1==1)&&(y_1==1)) {
                sierpinski_1[x_0][y_0][0] += _p[pos];
                sierpinski_1[x_0][y_0][1] += _p[pos+1];
                sierpinski_1[x_0][y_0][2] += _p[pos+2];
            } else {
                n = sizeSierpinski_3 * 3;
                int x_2r = x_1r % n;
                int x_2 = (x_1r - x_2r) / n;
                int y_2r = y_1r % sizeSierpinski_3;
                int y_2 = (y_1r - y_2r) / sizeSierpinski_3;
                if ((x_2==1)&&(y_2==1)) {
                    sierpinski_2[x_0][y_0][x_1][y_1][0] += _p[pos];
                    sierpinski_2[x_0][y_0][x_1][y_1][1] += _p[pos+1];
                    sierpinski_2[x_0][y_0][x_1][y_1][2] += _p[pos+2];
                } else {
                    n = sizeSierpinski_4 * 3;
                    int x_3r = x_2r % n;
                    int x_3 = (x_2r - x_3r) / n;
                    int y_3r = y_2r % sizeSierpinski_4;
                    int y_3 = (y_2r - y_3r) / sizeSierpinski_4;
                    if ((x_3==1)&&(y_3==1)) {
                        sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2][0] += _p[pos];
                        sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2][1] += _p[pos+1];
                        sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2][2] += _p[pos+2];
                    } else {
                        n = base * 3;
                        int x_4r = x_3r % n;
                        int x_4 = (x_3r - x_4r) / n;
                        int y_4r = y_3r % base;
                        int y_4 = (y_3r - y_4r) / base;
                        if ((x_4==1)&&(y_4==1)) {
                            sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3][0] += _p[pos];
                            sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3][1] += _p[pos+1];
                            sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3][2] += _p[pos+2];
                        }
                    }
                }
            }
        }
    }
}

//----------------------------------------------------------------
void VHPsierpinski::average(int _w, int _t, unsigned char * _p) {
    for (int i=0; i<totalSierpinski; i+=3){
        int n = sizeSierpinski_0 * 3;
        int x = i % n;
        int y = (i - x) / n;
        int pos = (y * _w * 3 + x)%_t;
        n = sizeSierpinski_1 * 3;
        int x_0r = x % n;
        int x_0 = (x - x_0r) / n;
        int y_0r = y % sizeSierpinski_1;
        int y_0 = (y - y_0r) / sizeSierpinski_1;
        if ((x_0==1)&&(y_0==1)) {
            //sierpinski[i] = pixels[pos];
            //sierpinski[i+1] = pixels[pos+1];
            //sierpinski[i+2] = pixels[pos+2];
            sierpinski[i] = sierpinski_0[0]/(sizeSierpinski_1*sizeSierpinski_1);
            sierpinski[i+1] = sierpinski_0[1]/(sizeSierpinski_1*sizeSierpinski_1);
            sierpinski[i+2] = sierpinski_0[2]/(sizeSierpinski_1*sizeSierpinski_1);
            
        } else {
            n = sizeSierpinski_2 * 3;
            int x_1r = x_0r % n;
            int x_1 = (x_0r - x_1r) / n;
            int y_1r = y_0r % sizeSierpinski_2;
            int y_1 = (y_0r - y_1r) / sizeSierpinski_2;
            if ((x_1==1)&&(y_1==1)) {
                //sierpinski[i] = pixels[pos];
                //sierpinski[i+1] = pixels[pos+1];
                //sierpinski[i+2] = pixels[pos+2];
                //sierpinski[i] = sierpinski_1[x_0][y_0][0]/(sizeSierpinski_2*sizeSierpinski_2);
                //sierpinski[i+1] = sierpinski_1[x_0][y_0][1]/(sizeSierpinski_2*sizeSierpinski_2);
                //sierpinski[i+2] = sierpinski_1[x_0][y_0][2]/(sizeSierpinski_2*sizeSierpinski_2);
                sierpinski[i] = sierpinski_1[x_0][y_0][0]/(sizeSierpinski_2*sizeSierpinski_2);
                sierpinski[i+1] = sierpinski_1[x_0][y_0][1]/(sizeSierpinski_2*sizeSierpinski_2);
                sierpinski[i+2] = sierpinski_1[x_0][y_0][2]/(sizeSierpinski_2*sizeSierpinski_2);
            } else {
                n = sizeSierpinski_3 * 3;
                int x_2r = x_1r % n;
                int x_2 = (x_1r - x_2r) / n;
                int y_2r = y_1r % sizeSierpinski_3;
                int y_2 = (y_1r - y_2r) / sizeSierpinski_3;
                if ((x_2==1)&&(y_2==1)) {
                    //sierpinski[i] = 0;
                    //sierpinski[i+1] = 0;
                    //sierpinski[i+2] = 0;
                    //sierpinski[i] = pixels[pos];
                    //sierpinski[i+1] = pixels[pos+1];
                    //sierpinski[i+2] = pixels[pos+2];
                    sierpinski[i] = sierpinski_2[x_0][y_0][x_1][y_1][0]/(sizeSierpinski_3*sizeSierpinski_3);
                    sierpinski[i+1] = sierpinski_2[x_0][y_0][x_1][y_1][1]/(sizeSierpinski_3*sizeSierpinski_3);
                    sierpinski[i+2] = sierpinski_2[x_0][y_0][x_1][y_1][2]/(sizeSierpinski_3*sizeSierpinski_3);
                } else {
                    n = sizeSierpinski_4 * 3;
                    int x_3r = x_2r % n;
                    int x_3 = (x_2r - x_3r) / n;
                    int y_3r = y_2r % sizeSierpinski_4;
                    int y_3 = (y_2r - y_3r) / sizeSierpinski_4;
                    if ((x_3==1)&&(y_3==1)) {
                        //sierpinski[i] = 0;
                        //sierpinski[i+1] = 0;
                        //sierpinski[i+2] = 0;
                        //sierpinski[i] = pixels[pos];
                        //sierpinski[i+1] = pixels[pos+1];
                        //sierpinski[i+2] = pixels[pos+2];
                        sierpinski[i] = sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2][0]/(sizeSierpinski_4*sizeSierpinski_4);
                        sierpinski[i+1] = sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2][1]/(sizeSierpinski_4*sizeSierpinski_4);
                        sierpinski[i+2] = sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2][2]/(sizeSierpinski_4*sizeSierpinski_4);
                    } else {
                        n = base * 3;
                        int x_4r = x_3r % n;
                        int x_4 = (x_3r - x_4r) / n;
                        int y_4r = y_3r % base;
                        int y_4 = (y_3r - y_4r) / base;
                        if ((x_4==1)&&(y_4==1)) {
                            //sierpinski[i] = 0;
                            //sierpinski[i+1] = 0;
                            //sierpinski[i+2] = 0;
                            //sierpinski[i] = pixels[pos];
                            //sierpinski[i+1] = pixels[pos+1];
                            //sierpinski[i+2] = pixels[pos+2];
                            sierpinski[i] = sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3][0]/(base*base);
                            sierpinski[i+1] = sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3][1]/(base*base);
                            sierpinski[i+2] = sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3][2]/(base*base);
                        } else {
                            n = 1*3;
                            int x_5r = x_4r % n;
                            int x_5 = (x_4r - x_5r) / n;
                            int y_5r = y_4r % 1;
                            int y_5 = (y_4r - y_5r) / 1;
                            if ((x_5==1)&&(y_5==1)) {
                                //sierpinski[i] = 0;
                                //sierpinski[i+1] = 0;
                                //sierpinski[i+2] = 0;
                                sierpinski[i] = _p[pos];
                                sierpinski[i+1] = _p[pos+1];
                                sierpinski[i+2] = _p[pos+2];
                            } else {
                                //sierpinski[i] = pixels[pos];
                                //sierpinski[i+1] = pixels[pos+1];
                                //sierpinski[i+2] = pixels[pos+2];
                            }
                        }
                    }
                }
            }
        }
    }
}

//----------------------------------------------------------------
void VHPsierpinski::draw() {
    textureSierpinski.draw(0, 0, sizeSierpinski_0, sizeSierpinski_0);
}

//----------------------------------------------------------------
