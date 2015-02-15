#include "VHPsierpinski.h"

//constructor

//----------------------------------------------------------------	
VHPsierpinski::VHPsierpinski() {
}

// methods

//----------------------------------------------------------------	

void VHPsierpinski::init() {
    // sierpinski pixel matrix have +2 pixels width size due to video card bugs using multiples of three
    // lets work with L_2 and do just one loop, L_2 sierpinski should have 54 x 27 square areas
    int width = 54;
    int height = 27;
    int total = width * height;
    int n;
    int pos;
    vector<int> pos_l0;
    vector<int> pos_l1;
    threshold = 150;
    
    // Json
    streamer.init("http://test.escoitar.org/exec/update_data.php", "http://test.escoitar.org/exec/get_data.php", 0, "hermetica", "vhplab_0000");
    
    for (int i=0; i<total; i++) {
        
        int x = i % width; // 0 - 53
        int y = (i - x) / width; // 0 - 26

        n = 9; // size of the L_0 square area
        
        int x_0r = x % n; // resto para poder obtener una división entera 0 - 8
        int x_0 = (x - x_0r) / n; // división entera 53/9, 0 - 5
        int x_0s = x_0 % 3; // %3, 0 - 2
        
        int y_0r = y % n; // resto para poder obtener una división entera 0 - 8
        int y_0 = (y - y_0r) / n; // 26/9, 0 - 2
        // no hace falta hacer el %3
        
        if ((x_0s==1)&&(y_0==1)) {
            pos = y_0 * 8 * 3 + x_0 * 3; // L_0 8 x 3 RGB
            // we dont want to add de same area several times
            bool already = false;
            for (int u=0; u<pos_l0.size(); u++) {
                if (pos_l0[u]==pos) {
                    already = true;
                    break;
                }
            }
            if (!already) {
                //int l = streamer.addData("L0-"+ ofToString(L_0.size()), "string");
                int l = L_0.size();
                L_0.push_back(VHPdata(pos, x_0, y_0, 243, 243,"/sierpinski_0/"+ofToString(L_0.size()),l));
                pos_l0.push_back(pos);
            }
        } else {
            
            n = 3; // size of the L_1 square area
            
            int x_1r = x % n; // resto para poder obtener una división entera 0 - 8
            int x_1 = (x - x_1r) / n; // división entera 53/3, 0 - 17
            int x_1s = x_1 % 3; // %3, 0 - 2
            
            int y_1r = y % n; // resto para poder obtener una división entera 0 - 8
            int y_1 = (y - y_1r) / n; // 26/3, 0 - 8
            int y_1s = y_1 % 3; // %3, 0 - 2
            
            if ((x_1s==1)&&(y_1s==1)) {
                pos = y_1 * 20 * 3 + x_1 * 3; // L_1 20 x 9 RGB
                // we dont want to add de same area several times
                bool already = false;
                for (int u=0; u<pos_l1.size(); u++) {
                    if (pos_l1[u]==pos) {
                        already = true;
                        break;
                    }
                }
                if (!already) {
                    //int l = streamer.addData("L1-"+ ofToString(L_1.size()), "string");
                    int l = L_1.size();
                    L_1.push_back(VHPdata(pos, x_1, y_1, 81, 81,"/sierpinski_1/"+ofToString(L_1.size()),l));
                    pos_l1.push_back(pos);
                }
            } else {
                
                int x_2s = x % 3; // %3, 0 - 2
                int y_2s = y % 3; // %3, 0 - 2
                
                if ((x_2s==1)&&(y_2s==1)) {
                    pos = y * 56 * 3 + x * 3; // L_2 56 x 27 RGB
                    L_2.push_back(VHPdata(pos, x, y, 27, 27,"/sierpinski_2/"+ofToString(L_2.size()),L_2.size()));
                }
                
            }
        }
    }
    cout << "L0.size(): " << L_0.size() << endl;
    cout << "L1.size(): " << L_1.size() << endl;
    cout << "L2.size(): " << L_2.size() << endl;
    
}

//----------------------------------------------------------------

void VHPsierpinski::draw() {
    for (int u=0; u<L_0.size(); u++) {
        L_0[u].drawColor(u);
    }
    for (int u=0; u<L_1.size(); u++) {
        L_1[u].drawColor(u);
    }
    for (int u=0; u<L_2.size(); u++) {
        L_2[u].drawColor(u);
    }
}

//----------------------------------------------------------------

void VHPsierpinski::update(const unsigned char * _l0, const unsigned char * _l1, const unsigned char * _l2, ofxOscSender & _sender) {
    data = "";
    for (int u=0; u<L_0.size(); u++) {
        updateData(L_0[u], _l0[L_0[u].pixelNum], _l0[L_0[u].pixelNum+1], _l0[L_0[u].pixelNum+2], _sender);
    }
    for (int u=0; u<L_1.size(); u++) {
        updateData(L_1[u], _l1[L_1[u].pixelNum], _l1[L_1[u].pixelNum+1], _l1[L_1[u].pixelNum+2], _sender);
    }
    for (int u=0; u<L_2.size(); u++) {
        updateData(L_2[u], _l2[L_2[u].pixelNum], _l2[L_2[u].pixelNum+1], _l2[L_2[u].pixelNum+2], _sender);
    }
    if (data!="") {
       streamer.sendData("sierpinski", "text", data); 
    }
}

void VHPsierpinski::updateData(VHPdata & _d, int _r, int _g, int _b, ofxOscSender & _sender){
    float grey = 0.2126 * _r + 0.7152 * _g + 0.0722 * _b;
    bool value;
    if (grey<=threshold) {
        value = false;
        _d.grey.set(grey, 0);
        //_d.color.set(_r, _g, _b, 0);
        _d.color.set(grey, grey, grey, 0);
    } else {
        value = true;
        if (_d.active) {
            _d.grey.set(grey, 255);
            //_d.color.set(_r, _g, _b, 255);
            _d.color.set(grey, grey, grey, 255);
        } else {
            _d.grey.set(grey, 80);
            //_d.color.set(_r, _g, _b, 80);
            _d.color.set(grey, grey, grey, 80);
        }
    }
    _d.setValue(value);
    _d.setAverage((int) grey);
    if (_d.isActive()) {
        if(_d.isNew()) {
            if (streamer.streaming) {
                if (data!="") data += "_";
                data += ofToString(_d.l) + "-" + ofToString((int)_d.on) + "-" + ofToString((int)value) + "-" + ofToString((int)grey);
            }
            //streamer.setData(_d.l, ofToString((int)value)+"-"+ofToString(grey)+"-"+ofToString((int)_d.on));
            ofxOscMessage msg;
            msg.setAddress(_d.address);
            cout << "Address: " << _d.address << endl;
            msg.addIntArg((int)value);
            msg.addFloatArg(grey);
            msg.addIntArg((int)_d.on);
            _sender.sendMessage(msg);
            _d.updateLast();
            
        }
        // type: 0 grid, 1 toggle, 2 trigger, 3 average
        switch (_d.type) {
            case 1:
                if (_d.on) _d.color.set(255, 255, 0, 255);
                break;
            case 2:
                if ((_d.on)||(_d.getLastValue())) _d.color.set(255, 255, 0, 255);
                break;
            case 3:
                _d.color.set(0, grey, grey, 255);
                break;
            default:
                break;
        }
    }
}

void VHPsierpinski::sendJson(){
    cout << "sierpinski.sendJson()" << endl;
    streamer.setData(0, ofToString(ofRandom(2)));
    streamer.setData(2, ofToString(ofRandom(2)));
    streamer.setData(1, ofToString(ofRandom(2)));
    streamer.getData("santiago", "L1-0");
}

//----------------------------------------------------------------

void VHPsierpinski::setActive(int _l, int _n, int _a, int _t){
    switch (_l) {
        case 0:
            if (_n<L_0.size()) {
                (_a==0) ? L_0[_n].setActive(false) : L_0[_n].setActive(true);
                L_0[_n].setType(_t);
            }
            break;
        case 1:
            if (_n<L_1.size()) {
                (_a==0) ? L_1[_n].setActive(false) : L_1[_n].setActive(true);
                L_1[_n].setType(_t);
            }
            break;
        case 2:
            if (_n<L_2.size()) {
                (_a==0) ? L_2[_n].setActive(false) : L_2[_n].setActive(true);
                L_2[_n].setType(_t);
            }
            break;
        default:
            break;
    }

}

//----------------------------------------------------------------

void VHPsierpinski::setThreshold(int _t) {
    threshold = _t;
}

//----------------------------------------------------------------