#include "VHPstreamer.h"

//constructor

//----------------------------------------------------------------	
VHPstreamer::VHPstreamer() {
}
VHPstreamer::VHPstreamer(int _user_id, string _user_name) {
    user_id = _user_id;
    user_name = _user_name;
}

// methods

//----------------------------------------------------------------
ofxOscMessage VHPstreamer::setData(ofxJSONElement& _s) {
    
    ofxOscMessage msg;
    string data_name = _s["data_name"].asString();
    string data_type = _s["data_type"].asString();
    msg.setAddress("/" + user_name + "/" + data_name + "/" + data_type);
    string data_time = _s["insert_datetime"].asString();
    bool dataAdded = false;
    for (int i=0; i<data.size(); i++) {
        if ((data[i].name == data_name)&&(data[i].time!=data_time)) {
            data[i].setTime(data_time);
            if (data_type=="bool") {
                data[i].setData(ofToBool(_s["data_bool"].asString()));
                msg.addIntArg(ofToInt(_s["data_bool"].asString()));
            } else if (data_type=="int") {
                data[i].setData(ofToInt(_s["data_int"].asString()));
                msg.addIntArg(ofToInt(_s["data_int"].asString()));
            } else if (data_type=="float") {
                data[i].setData(ofToFloat(_s["data_float"].asString()));
                msg.addFloatArg(ofToFloat(_s["data_float"].asString()));
            } else if (data_type=="color") {
                data[i].setData(ofColor(ofToInt(_s["data_r"].asString()), ofToInt(_s["data_g"].asString()), ofToInt(_s["data_b"].asString())));
                msg.addIntArg(ofToInt(_s["data_r"].asString()));
                msg.addIntArg(ofToInt(_s["data_g"].asString()));
                msg.addIntArg(ofToInt(_s["data_b"].asString()));
            }
            data[i].info();
            dataAdded = true;
            break;
        }
    }
    
    if (!dataAdded) {
        data.push_back(VHPdata(data_name, data_type));
        cout << data_name << "created" <<endl;
        data[data.size()-1].setTime(data_time);
        if (data_type=="bool") {
            data[data.size()-1].setData(ofToBool(_s["data_bool"].asString()));
            msg.addIntArg(ofToInt(_s["data_bool"].asString()));
        } else if (data_type=="int") {
            data[data.size()-1].setData(ofToInt(_s["data_int"].asString()));
            msg.addIntArg(ofToInt(_s["data_int"].asString()));
        } else if (data_type=="float") {
            data[data.size()-1].setData(ofToFloat(_s["data_float"].asString()));
            msg.addFloatArg(ofToFloat(_s["data_float"].asString()));
        } else if (data_type=="color") {
            data[data.size()-1].setData(ofColor(ofToInt(_s["data_r"].asString()), ofToInt(_s["data_g"].asString()), ofToInt(_s["data_b"].asString())));
            msg.addIntArg(ofToInt(_s["data_r"].asString()));
            msg.addIntArg(ofToInt(_s["data_g"].asString()));
            msg.addIntArg(ofToInt(_s["data_b"].asString()));
        }
        data[data.size()-1].info();
    }
    
    return msg;
}

//----------------------------------------------------------------

void VHPstreamer::info() {
    cout << "user_id: " << user_id << endl;
}

string VHPstreamer::getData() {
    return "user_id: "+ ofToString(user_id);
}
