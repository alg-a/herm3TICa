#include "VHPgrid.h"

//constructor

//----------------------------------------------------------------	
VHPgrid::VHPgrid() {
    
}


// methods

//----------------------------------------------------------------

void VHPgrid::init(int _w, int _h, int _aw, int _ah) {
    
    gridSize = _w * _h;
    width = _w;
    height = _h;
    pixW = _w * _aw;
    pixH = _h * _ah;
    
    for (int i=0; i<gridSize; i++) {
        int x = i % _w;
        int y = (i - x) / _w;
        area.push_back(VHPdata(x, y, _aw, _ah));
    }
    
    // Json
    streamer.init("http://test.escoitar.org/exec/update_data.php", "http://test.escoitar.org/exec/update_data2.php", 0, "hermetica", "vhplab_0000");
    streamer.addData("grid-vector-x", "float");
    streamer.addData("grid-vector-y", "float");
    
}

//----------------------------------------------------------------

void VHPgrid::draw() {
    for (int i=0; i<gridSize; i++) {
        area[i].draw();
    }
    if ((position.x>0.0)&&(position.y>0.0)){
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(1.8);
        ofSetColor(255,255,255);
        ofLine(0, 0, position.x, position.y);
        ofLine(pixW, pixH, position.x, position.y);
        ofLine(pixW, 0, position.x, position.y);
        ofLine(0, pixH, position.x, position.y);
        ofPopStyle();
    }
}

//----------------------------------------------------------------

void VHPgrid::update(const unsigned char * _d, int _o, ofxOscSender & _sender) {
    ofVec2f v;
    int n;
    total_weight = 0.00001;
    for (int i=0; i<gridSize; i++) {
        int n = area[i].position.y * (width+_o) * 3 + area[i].position.x * 3;
        float grey = 0.2126 * _d[n] + 0.7152 * _d[n+1] + 0.0722 * _d[n+2];
        area[i].grey.set(grey);
        area[i].color.set(_d[n], _d[n+1], _d[n+2]);
        float weight = grey/255.0;
        v += area[i].position * weight;
        total_weight += weight;
        /*
        ofVec2f d = area[i].position - v;
        v += d * grey/255;
        */
    }
    position.set(v.x*area[0].width/total_weight, v.y*area[0].height/total_weight);
    if ((position.x>0.0)|(position.y>0.0)) {
        streamer.setData(0, ofToString(position.x/pixW));
        streamer.setData(1, ofToString(position.y/pixH));
        ofxOscMessage msg;
        msg.setAddress("/grid/vector");
        msg.addFloatArg(position.x/pixW);
        msg.addFloatArg(position.y/pixH);
        //cout << " sending: " << msg.getArgAsFloat(0) << " " << msg.getArgAsFloat(1) << " to address: " << msg.getAddress() << endl;
        _sender.sendMessage(msg);
    }
    //if (total_weight > 0.00001) {
        ofxOscMessage msg;
        msg.setAddress("/grid/weight");
        msg.addFloatArg(total_weight);
        _sender.sendMessage(msg);
    //}
    streamer.update();
}

//----------------------------------------------------------------

ofVec2f VHPgrid::getVector() {
    return ofVec2f(position.x/pixW, position.y/pixH);
}
