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

void VHPosc::update() {
    while(receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if (m.getAddress() == "/") {
            
        } else if (m.getAddress() == "/") {
            
        }
    }

}

//----------------------------------------------------------------
