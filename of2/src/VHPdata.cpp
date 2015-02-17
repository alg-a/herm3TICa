#include "VHPdata.h"

//constructor

//----------------------------------------------------------------	
// type: 0 grid, 1 toggle, 2 trigger, 3 average

VHPdata::VHPdata() : grey(128, 255), type(0), active(false), on(false), average(0), lastAverage(0), value(false), lastValue(false) {

}

VHPdata::VHPdata(int _n, int _x, int _y, int _w, int _h, string _a, int _l) : grey(128, 255), position(_x, _y), width(_w), height(_h), type(2), active(false), on(false), average(0), lastAverage(0), value(false), lastValue(false), pixelNum(_n), address(_a), l(_l) {
    // trigger
}

VHPdata::VHPdata(int _x, int _y, int _w, int _h) : grey(128, 255), position(_x, _y), width(_w), height(_h), type(0), active(false), on(false), average(0), lastAverage(0), value(false), lastValue(false) {
    // grid
}

// methods

//----------------------------------------------------------------	

void VHPdata::draw() {
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(color);
    ofRect(position.x*width+1, position.y*height+1, width-2, height-2);
    ofPopStyle();
}

void VHPdata::drawColor(int _n) {
    
    ofPushStyle();
    ofSetColor(color.r, color.g, color.b, color.a*0.6);
    ofFill();
    ofRect(position.x*width+1, position.y*height+1, width-2, height-2);
    // cout << "rectangle: " << position.x*width+1 << " " << position.y* height+1 << " " << width-2 << " " << height-2 << endl;
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(color.r, color.g, color.b, 255);
    ofNoFill();
    ofSetLineWidth(2);
    ofRect(position.x*width+1, position.y*height+1, width-2, height-2);
    ofPopStyle();
    
    if (active){
        ofPushStyle();
        ofSetHexColor(0xffffff);
        //ofToString(pixelNum)
        //ofToString(_n)
        ofDrawBitmapString("value: "+ ofToString(value), position.x*width + 4, position.y*height + 14);
        ofDrawBitmapString("on: "+ ofToString(on), position.x*width + 4, position.y*height + 14 + 14);
        switch (type) {
            case 1:
                ofDrawBitmapString("type: toggle", position.x*width + 4, position.y*height + 14 + 14*2);
                break;
            case 2:
                ofDrawBitmapString("type: trigger", position.x*width + 4, position.y*height + 14 + 14*2);
                break;
            case 3:
                ofDrawBitmapString("type: average", position.x*width + 4, position.y*height + 14 + 14*2);
                break;
            default:
                break;
        }
        ofDrawBitmapString("average: "+ ofToString(average), position.x*width + 4, position.y*height + 14 + 14*3);
        ofPopStyle();
    }
    
}

//----------------------------------------------------------------

void VHPdata::setActive(bool _a) {
    active = _a;
    cout << "setActive(" << active << ")" << endl;
}

bool VHPdata::isActive() {
    return active;
}

//----------------------------------------------------------------

void VHPdata::setAverage(int _a) {
    average = _a;
    // cout << "setAverage(" << average << ")" << endl;
}

int VHPdata::getAverage() {
    return average;
}

//----------------------------------------------------------------

void VHPdata::setOn(bool _o) {
    on = _o;
}

bool VHPdata::getOn() {
    return on;
}

//----------------------------------------------------------------

void VHPdata::setValue(bool _v) {
    value = _v;
}

bool VHPdata::getValue() {
    return value;
}

//----------------------------------------------------------------

void VHPdata::setAddress(string _a) {
    address = _a;
}

string VHPdata::getAddress() {
    return address;
}

//----------------------------------------------------------------

void VHPdata::setType(int _t) {
    // type: 0 grid, 1 toggle, 2 trigger, 3 average
    type = _t;
    on = false;
    cout << "setType(" << type << ")" << endl;
}

int VHPdata::getType() {
    return type;
}

//----------------------------------------------------------------

void VHPdata::setLastValue(bool _l){
    lastValue = _l;
}

void VHPdata::setLastAverage(int _a){
    lastAverage = _a;
}

void VHPdata::updateLast() {
    setLastValue(value);
    setLastAverage(average);
}

bool VHPdata::getLastValue() {
    return lastValue;
}

int VHPdata::getLastAverage() {
    return lastAverage;
}

bool VHPdata::isNew(){
    // cout << " lastValue: " << lastValue << " value: " << value << " on: " << on << endl;
    bool r = false;
    switch (type) {
        case 0: // 0 grid
            r = false;
            break;
        case 1: // 1 toggle
            if (lastValue != value) {
                if (!value) {
                    on ? on = false : on= true;
                    by = "hermetica";
                    cout << "!value + !on " +ofToString(on)<< endl;
                    r = true;
                } else {
                    cout << "updateLast()" << endl;
                    updateLast();
                }
                cout << "lastValue != value" << endl;
            }
            break;
        case 2: // 2 trigger
            if (lastValue != value) r = true;
            break;
        case 3: // 3 average
            if (lastAverage != average) r = true;
            break;
        default:
            break;
    }
    return r;
}

//----------------------------------------------------------------