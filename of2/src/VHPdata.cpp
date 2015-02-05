#include "VHPdata.h"

//constructor

//----------------------------------------------------------------	
VHPdata::VHPdata() : grey(128, 255) {
}

VHPdata::VHPdata(int _x, int _y, int _w, int _h) : grey(128, 255), vector(_x, _y), width(_w), height(_h) {

}

// methods

//----------------------------------------------------------------	
void VHPdata::draw() {
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(1.8);
    ofSetColor(color);
    ofRect(vector.x*width+1, vector.y*height+1, width-2, height-2);
    ofPopStyle();
}
//----------------------------------------------------------------	

//----------------------------------------------------------------	