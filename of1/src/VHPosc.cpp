#include "VHPosc.h"

//constructor

//----------------------------------------------------------------	
VHPosc::VHPosc() {
    
}

// methods

//----------------------------------------------------------------
void VHPosc::setup(string _h, int _sp, int _rp) {
    sender.setup(_h, _sp);
    cout << "sender host: " << _h << ", " << _sp << endl;
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
        } else if (m.getAddress() == "/show") {
            (m.getArgAsInt32(0)==0) ? _cam.show = false : _cam.show = true;
        } else if (m.getAddress() == "/play") {
            _cam.play(m.getArgAsInt32(0), m.getArgAsInt32(1));
        } else if (m.getAddress() == "/showplayer") {
            (m.getArgAsInt32(0)==0) ? _cam.showPlayer = false : _cam.showPlayer = true;
        } else if (m.getAddress() == "/adjust") {
            (m.getArgAsInt32(0)==0) ? _cam.bkgAdjustment = 0 : _cam.bkgAdjustment = 1;
        } else if (m.getAddress() == "/velocity") {
            _cam.player.setSpeed(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/invert") {
            (m.getArgAsInt32(0)==0) ? _cam.invert = false : _cam.invert = true;
        }
    }
    string newRecording = _cam.getNewRecording();
    if (newRecording!="") {
        //vector<string> result = ofSplitString(newRecording, "/");
        ofxOscMessage msg;
        msg.setAddress("/saved");
        msg.addStringArg(newRecording);
        //msg.addStringArg(result[result.size()-3]+"/"+result[result.size()-2]+"/"+result[result.size()-1]);
        cout << " sending: " << msg.getArgAsString(0) << " to address: " << msg.getAddress() << endl;
        sender.sendMessage(msg);
        _cam.emptyNewRecording();
    }
}

//----------------------------------------------------------------

void VHPosc::sendSettings(int _stela, int _show, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3){
    ofxOscMessage msg;
    msg.setAddress("/of1_settings");
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
    cout << " sending: " << msg.getArgAsInt32(0) << ", " << msg.getArgAsInt32(1) << ", " << msg.getArgAsInt32(2) << ", " << msg.getArgAsInt32(3) << ", " << msg.getArgAsInt32(4) << ", " << msg.getArgAsInt32(5) << ", " << msg.getArgAsInt32(6) << ", " << msg.getArgAsInt32(7) << " to address: " << msg.getAddress() << endl;
    sender.sendMessage(msg);
}


//----------------------------------------------------------------
