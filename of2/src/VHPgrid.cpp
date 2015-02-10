#include "VHPgrid.h"

//constructor

//----------------------------------------------------------------	
VHPgrid::VHPgrid() {
    
}


// methods

//----------------------------------------------------------------

void VHPgrid::init(int _w, int _h, int _aw, int _ah) {
    
    size = _w * _h;
    width = _w;
    height = _h;
    pixW = _w * _aw;
    pixH = _h * _ah;
    
    for (int i=0; i<size; i++) {
        int x = i % _w;
        int y = (i - x) / _w;
        area.push_back(VHPdata(x, y, _aw, _ah));
    }
}

//----------------------------------------------------------------

void VHPgrid::draw() {
    for (int i=0; i<size; i++) {
        area[i].draw();
    }
    if ((vector.x>0.0)&&(vector.y>0.0)){
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(1.8);
        ofSetColor(255,255,255);
        ofLine(0, 0, vector.x, vector.y);
        ofLine(pixW, pixH, vector.x, vector.y);
        ofLine(pixW, 0, vector.x, vector.y);
        ofLine(0, pixH, vector.x, vector.y);
        ofPopStyle();
    }
}

//----------------------------------------------------------------

void VHPgrid::update(const unsigned char * _d, int _o) {
    ofVec2f v;
    int n;
    float total_weight = 0.0001;
    for (int i=0; i<size; i++) {
        int n = area[i].vector.y * (width+_o) * 3 + area[i].vector.x * 3;
        float grey = 0.2126 * _d[n] + 0.7152 * _d[n+1] + 0.0722 * _d[n+2];
        area[i].grey.set(grey);
        area[i].color.set(_d[n], _d[n+1], _d[n+2]);
        float weight = grey/255.0;
        v += area[i].vector * weight;
        total_weight += weight;
        /*
        ofVec2f d = area[i].vector - v;
        v += d * grey/255;
        */
    }
    vector.set(v.x*area[0].width/total_weight, v.y*area[0].height/total_weight);
}

//----------------------------------------------------------------

ofVec2f VHPgrid::getVector() {
    return ofVec2f(vector.x/pixW, vector.y/pixH);
}
