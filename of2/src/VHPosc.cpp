#include "VHPosc.h"

//constructor

//----------------------------------------------------------------	
VHPosc::VHPosc() {
    
}

// methods

//----------------------------------------------------------------
void VHPosc::setup(string _h, string _rh, int _sp, int _rsp, int _rp) {
    sender.setup(_h, _sp);
    remoteSender.setup(_rh, _rsp);
    cout << "sender host: " << _h << ", " << _sp << endl;
    cout << "remote sender host: " << _h << ", " << _sp << endl;
    receiver.setup(_rp);
    cout << "receiver port: " << _rp << endl;
}

//----------------------------------------------------------------

void VHPosc::update(VHPcam & _cam) {
    while(receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if (m.getAddress() == "/contrast") {
            _cam.setContrast(m.getArgAsInt32(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
        } else if (m.getAddress() == "/save") {
            _cam.save(m.getArgAsInt32(0));
        } else if (m.getAddress() == "/stela") {
            _cam.percent[0] = m.getArgAsFloat(0);
        }  else if (m.getAddress() == "/mixture") {
            _cam.percent[1] = m.getArgAsFloat(0);
        } else if (m.getAddress() == "/play") {
            _cam.play(m.getArgAsInt32(0), m.getArgAsInt32(1));
        }  else if (m.getAddress() == "/playBkg") {
            _cam.playBkg(m.getArgAsInt32(0), m.getArgAsInt32(1));
        }else if (m.getAddress() == "/background") {
            _cam.updateBkg();
        } else if (m.getAddress() == "/blur") {
            _cam.blur = m.getArgAsFloat(0);
        } else if (m.getAddress() == "/recorte") {
            _cam.min = m.getArgAsFloat(0);
            _cam.max = m.getArgAsFloat(1);
        } else if (m.getAddress() == "/mode") {
            _cam.setMode(m.getArgAsInt32(0));
        } else if (m.getAddress() == "/threshold") {
            _cam.sierpinski.setThreshold(m.getArgAsInt32(0));
        } else if (m.getAddress() == "/color") {
            _cam.maskColor.set(m.getArgAsInt32(0), m.getArgAsInt32(1), m.getArgAsInt32(2));
        } else if (m.getAddress() == "/maskMode") {
            _cam.vidBackground = m.getArgAsInt32(0);
        } else if (m.getAddress() == "/sierpinski") {
            _cam.sierpinski.setActive(m.getArgAsInt32(0), m.getArgAsInt32(1), m.getArgAsInt32(2), m.getArgAsInt32(3));
        } else if (m.getAddress() == "/sierpinskiAlpha") {
            (m.getArgAsInt32(0)==0) ? _cam.doAlpha = 0 : _cam.doAlpha = 1;
            _cam.sierpinskiMixture = m.getArgAsFloat(1);
        } else if (m.getAddress() == "/velocity") {
            _cam.player.setSpeed(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/velocityBkg") {
            _cam.bkgPlayer.setSpeed(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/invert") {
            (m.getArgAsInt32(0)==0) ? _cam.invert = false : _cam.invert = true;
        } else if (m.getAddress() == "/streaming") {
            (m.getArgAsInt32(0)==0) ? _cam.streaming = false : _cam.streaming = true;
        } else if (m.getAddress() == "/syphon") {
            (m.getArgAsInt32(0)==0) ? _cam.syphon = false : _cam.syphon = true;
        } else if (m.getAddress() == "/sustract") {
            (m.getArgAsInt32(0)==0) ? _cam.sustract = false : _cam.sustract = true;
        } else if (m.getAddress() == "/negative") {
            (m.getArgAsInt32(0)==0) ? _cam.negative = false : _cam.negative = true;
        }
    }
    string newRecording = _cam.getNewRecording();
    if (newRecording!="") {
        //vector<string> result = ofSplitString(newRecording, "/");
        ofxOscMessage msg;
        msg.setAddress("/saved");
        msg.addStringArg(newRecording);
        //msg.addStringArg(result[result.size()-3]+"/"+result[result.size()-2]+"/"+result[result.size()-1]);
        //cout << " sending: " << msg.getArgAsString(0) << " to address: " << msg.getAddress() << endl;
        sender.sendMessage(msg);
        _cam.emptyNewRecording();
    }
}

//----------------------------------------------------------------

void VHPosc::sendSettings(int _stela, int _show, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3, float _b, float _rb, float _rw){
    ofxOscMessage msg;
    msg.setAddress("/of2_settings");
    msg.addIntArg(_stela);
    msg.addIntArg(_show);
    msg.addIntArg(_e0);
    msg.addIntArg(_f0);
    msg.addIntArg(_e1);
    msg.addIntArg(_f1);
    msg.addIntArg(_e2);
    msg.addIntArg(_f2);
    msg.addIntArg(_e3);
    msg.addIntArg(_f3);
    msg.addFloatArg(_b);
    msg.addFloatArg(_rb);
    msg.addFloatArg(_rw);
    cout << " sending: " << msg.getArgAsInt32(0) << ", " << msg.getArgAsInt32(1) << ", " << msg.getArgAsInt32(2) << ", " << msg.getArgAsInt32(3) << ", " << msg.getArgAsInt32(4) << ", " << msg.getArgAsInt32(5) << ", " << msg.getArgAsInt32(6) << ", " << msg.getArgAsInt32(7) << " to address: " << msg.getAddress() << endl;
    sender.sendMessage(msg);
}



//----------------------------------------------------------------
