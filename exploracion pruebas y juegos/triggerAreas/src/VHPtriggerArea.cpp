#include "VHPtriggerArea.h"

//constructor

//----------------------------------------------------------------
VHPtriggerArea::VHPtriggerArea() {
    
}

// methods

//----------------------------------------------------------------

void VHPtriggerArea::setup(int _x, int _y, int _w, int _h, string _host, int _port, string _address) {
    setPosition(_x, _y);
    setSize(_w, _h);
    sender.setup(_host, _port);
    cout << "sender host: " << _host << ", " << _port << endl;
    data.setAddress("/"+_address);
    threshold = 150;
}

//----------------------------------------------------------------

void VHPtriggerArea::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}

int VHPtriggerArea::getX() {
    return x;
}

int VHPtriggerArea::getY() {
    return y;
}

//----------------------------------------------------------------

void VHPtriggerArea::setSize(int _w, int _h) {
    width = _w;
    height = _h;
    size = width * height * 3;
}

void VHPtriggerArea::setWidth(int _w) {
    width = _w;
    size = width * height * 3;
}

void VHPtriggerArea::setHeight(int _h) {
    height = _h;
    size = width * height * 3;
}

int VHPtriggerArea::getWidth() {
    return width;
}

int VHPtriggerArea::getHeight() {
    return height;
}

//----------------------------------------------------------------

void VHPtriggerArea::update(int _w, int _h, int _t, unsigned char * _p) {
    for (int i=0; i<size; i+=3){
        int px = i % (width * 3);
        int py = (i - px) / (width * 3);
        px += x*3;
        py += y;
        int pos = (py * _w * 3 + px) % _t;
        // Add grey scale value to data
        data.add(0.2126 * _p[pos] + 0.7152 * _p[pos+1] + 0.0722 * _p[pos+2]);
        //_p[pos] = 255;
        //_p[pos+1] = 255;
        //_p[pos+2] = 0;
    }
    data.setAverage(width*height);
    data.setValue(data.getAverage()>=threshold);
    if (data.isActive()) {
        if(data.isNew()) {
            ofxOscMessage msg;
            msg.setAddress(data.getAddress());
            msg.addIntArg((int)data.getValue());
            cout << msg.getAddress() << " " << msg.getArgAsInt32(0) << endl;
            sender.sendMessage(msg);
            data.updateLast();
        }
    }
    
}

//----------------------------------------------------------------

void VHPtriggerArea::draw() {
    ofPushStyle();
    //ofFill();
    ofNoFill();
    ofSetLineWidth(1.8);
    //ofSetColor(ofColor(data.getAverage(), data.getAverage(), data.getAverage()));
    if (data.getValue()) {
        ofSetColor(ofColor(255, 255, 255));
        if (data.isActive()) {
            ofSetColor(ofColor(255, 255, 0));
        }
    } else {
        ofSetColor(ofColor(0, 0, 0));
    }
    ofRect(x, y, width, height);
    ofPopStyle();
}

//----------------------------------------------------------------
void VHPtriggerArea::setThreshold(int _t) {
    threshold = _t;
    cout << "setThreshold(" << threshold << ")" << endl;
}

//----------------------------------------------------------------
