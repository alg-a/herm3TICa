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
    
    threshold = 150;
    
    sender.setup("localhost", 8000);
    
    
    sierpinski_0.setAddress("/sierpinski_0");
    for (int i=0; i<3; i++){
        for (int u=0; u<3; u++){
            sierpinski_1[i][u].setAddress("/sierpinski_1/"+ofToString(i)+"/"+ofToString(u));
            for (int o=0; o<3; o++){
                for (int s=0; s<3; s++){
                    sierpinski_2[i][u][o][s].setAddress("/sierpinski_2/"+ofToString(i)+"/"+ofToString(u)+"/"+ofToString(o)+"/"+ofToString(s));
                    for (int q=0; q<3; q++){
                        for (int p=0; p<3; p++){
                            sierpinski_3[i][u][o][s][q][p].setAddress("/sierpinski_3/"+ofToString(i)+"/"+ofToString(u)+"/"+ofToString(o)+"/"+ofToString(s)+"/"+ofToString(q)+"/"+ofToString(p));
                            for (int t=0; t<3; t++){
                                for (int r=0; r<3; r++){
                                    sierpinski_4[i][u][o][s][q][p][t][r].setAddress("/sierpinski_4/"+ofToString(i)+"/"+ofToString(u)+"/"+ofToString(o)+"/"+ofToString(s)+"/"+ofToString(q)+"/"+ofToString(p)+"/"+ofToString(t)+"/"+ofToString(r));
                                }
                            }
                        }
                    }

                }
            }
        }
        
    }
    
    
    
}

//----------------------------------------------------------------
void VHPsierpinski::update(int _w, int _t, unsigned char * _p) {
    store(_w, _t, _p);
    average(_w, _t, _p);
    textureSierpinski.loadData(sierpinski, sizeSierpinski_0, sizeSierpinski_0, GL_RGB);
}

//----------------------------------------------------------------
void VHPsierpinski::store(int _w, int _t, unsigned char * _p) {
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
            sierpinski_0.add(0.2126 * _p[pos] + 0.7152 * _p[pos+1] + 0.0722 * _p[pos+2]);
        } else {
            n = sizeSierpinski_2 * 3;
            int x_1r = x_0r % n;
            int x_1 = (x_0r - x_1r) / n;
            int y_1r = y_0r % sizeSierpinski_2;
            int y_1 = (y_0r - y_1r) / sizeSierpinski_2;
            if ((x_1==1)&&(y_1==1)) {
                sierpinski_1[x_0][y_0].add(0.2126 * _p[pos] + 0.7152 * _p[pos+1] + 0.0722 * _p[pos+2]);
            } else {
                n = sizeSierpinski_3 * 3;
                int x_2r = x_1r % n;
                int x_2 = (x_1r - x_2r) / n;
                int y_2r = y_1r % sizeSierpinski_3;
                int y_2 = (y_1r - y_2r) / sizeSierpinski_3;
                if ((x_2==1)&&(y_2==1)) {
                    sierpinski_2[x_0][y_0][x_1][y_1].add(0.2126 * _p[pos] + 0.7152 * _p[pos+1] + 0.0722 * _p[pos+2]);
                } else {
                    n = sizeSierpinski_4 * 3;
                    int x_3r = x_2r % n;
                    int x_3 = (x_2r - x_3r) / n;
                    int y_3r = y_2r % sizeSierpinski_4;
                    int y_3 = (y_2r - y_3r) / sizeSierpinski_4;
                    if ((x_3==1)&&(y_3==1)) {
                        sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2].add(0.2126 * _p[pos] + 0.7152 * _p[pos+1] + 0.0722 * _p[pos+2]);
                    } else {
                        n = base * 3;
                        int x_4r = x_3r % n;
                        int x_4 = (x_3r - x_4r) / n;
                        int y_4r = y_3r % base;
                        int y_4 = (y_3r - y_4r) / base;
                        if ((x_4==1)&&(y_4==1)) {
                            sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3].add(0.2126 * _p[pos] + 0.7152 * _p[pos+1] + 0.0722 * _p[pos+2]);
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
            //sierpinski[i] = sierpinski_0/(sizeSierpinski_1*sizeSierpinski_1);
            //sierpinski[i+1] = sierpinski_0/(sizeSierpinski_1*sizeSierpinski_1);
            //sierpinski[i+2] = sierpinski_0/(sizeSierpinski_1*sizeSierpinski_1);
            updateSierpinski(sierpinski_0, sizeSierpinski_1, i);
            
        } else {
            n = sizeSierpinski_2 * 3;
            int x_1r = x_0r % n;
            int x_1 = (x_0r - x_1r) / n;
            int y_1r = y_0r % sizeSierpinski_2;
            int y_1 = (y_0r - y_1r) / sizeSierpinski_2;
            if ((x_1==1)&&(y_1==1)) {
                //sierpinski[i] = sierpinski_1[x_0][y_0]/(sizeSierpinski_2*sizeSierpinski_2);
                //sierpinski[i+1] = sierpinski_1[x_0][y_0]/(sizeSierpinski_2*sizeSierpinski_2);
                //sierpinski[i+2] = sierpinski_1[x_0][y_0]/(sizeSierpinski_2*sizeSierpinski_2);
                updateSierpinski(sierpinski_1[x_0][y_0], sizeSierpinski_2, i);
                
            } else {
                n = sizeSierpinski_3 * 3;
                int x_2r = x_1r % n;
                int x_2 = (x_1r - x_2r) / n;
                int y_2r = y_1r % sizeSierpinski_3;
                int y_2 = (y_1r - y_2r) / sizeSierpinski_3;
                if ((x_2==1)&&(y_2==1)) {
                    //sierpinski[i] = sierpinski_2[x_0][y_0][x_1][y_1]/(sizeSierpinski_3*sizeSierpinski_3);
                    //sierpinski[i+1] = sierpinski_2[x_0][y_0][x_1][y_1]/(sizeSierpinski_3*sizeSierpinski_3);
                    //sierpinski[i+2] = sierpinski_2[x_0][y_0][x_1][y_1]/(sizeSierpinski_3*sizeSierpinski_3);
                    updateSierpinski(sierpinski_2[x_0][y_0][x_1][y_1], sizeSierpinski_3, i);
                } else {
                    n = sizeSierpinski_4 * 3;
                    int x_3r = x_2r % n;
                    int x_3 = (x_2r - x_3r) / n;
                    int y_3r = y_2r % sizeSierpinski_4;
                    int y_3 = (y_2r - y_3r) / sizeSierpinski_4;
                    if ((x_3==1)&&(y_3==1)) {
                        //sierpinski[i] = sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2]/(sizeSierpinski_4*sizeSierpinski_4);
                        //sierpinski[i+1] = sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2]/(sizeSierpinski_4*sizeSierpinski_4);
                        //sierpinski[i+2] = sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2]/(sizeSierpinski_4*sizeSierpinski_4);
                        updateSierpinski(sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2], sizeSierpinski_4, i);
                    } else {
                        n = base * 3;
                        int x_4r = x_3r % n;
                        int x_4 = (x_3r - x_4r) / n;
                        int y_4r = y_3r % base;
                        int y_4 = (y_3r - y_4r) / base;
                        if ((x_4==1)&&(y_4==1)) {
                            //sierpinski[i] = sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3]/(base*base);
                            //sierpinski[i+1] = sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3]/(base*base);
                            //sierpinski[i+2] = sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3]/(base*base);
                            updateSierpinski(sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3], base, i);
                        } else {
                            n = 1*3;
                            int x_5r = x_4r % n;
                            int x_5 = (x_4r - x_5r) / n;
                            int y_5r = y_4r % 1;
                            int y_5 = (y_4r - y_5r) / 1;
                            if ((x_5==1)&&(y_5==1)) {
                                //sierpinski[i] = _p[pos];
                                //sierpinski[i+1] = _p[pos+1];
                                //sierpinski[i+2] = _p[pos+2];
                                if (0.2126 * _p[pos] + 0.7152 * _p[pos+1] + 0.0722 * _p[pos+2]<=threshold) {
                                    sierpinski[i] = 0;
                                    sierpinski[i+1] = 0;
                                    sierpinski[i+2] = 0;
                                } else {
                                    sierpinski[i] = 255;
                                    sierpinski[i+1] = 255;
                                    sierpinski[i+2] = 255;
                                }
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
void VHPsierpinski::updateSierpinski(VHPdata & _s, int _t, int _i) {
    if (_s.getAddition()!=0) {
        _s.setAverage(_t*_t);
        bool value;
        if (_s.getAverage()<=threshold) {
            sierpinski[_i] = 0;
            sierpinski[_i+1] = 0;
            sierpinski[_i+2] = 0;
            value = false;
        } else {
            sierpinski[_i] = 255;
            sierpinski[_i+1] = 255;
            sierpinski[_i+2] = 255;
            value = true;
        }
        if (_s.isActive()) {
            _s.setValue(value);
            sierpinski[_i+2] = 0;
            if(_s.isNew()) {
                ofxOscMessage msg;
                msg.setAddress(_s.address);
                cout << _s.address << endl;
                msg.addIntArg((int)value);
                sender.sendMessage(msg);
                _s.updateLast();
            }
        }
    } else {
        bool value;
        if (_s.getAverage()<=threshold) {
            sierpinski[_i] = 0;
            sierpinski[_i+1] = 0;
            sierpinski[_i+2] = 0;
            value = false;
        } else {
            sierpinski[_i] = 255;
            sierpinski[_i+1] = 255;
            sierpinski[_i+2] = 255;
            value = true;
        }
        if (_s.isActive()) {
            sierpinski[_i+2] = 0;
        }
    }
}

//----------------------------------------------------------------
void VHPsierpinski::draw() {
    textureSierpinski.draw(0, 0, sizeSierpinski_0, sizeSierpinski_0);
}

//----------------------------------------------------------------
void VHPsierpinski::setThreshold(int _t) {
    threshold = _t;
}
//----------------------------------------------------------------
