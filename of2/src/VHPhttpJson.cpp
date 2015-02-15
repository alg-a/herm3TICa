#include "VHPhttpJson.h"

//constructor

//----------------------------------------------------------------	
VHPhttpJson::VHPhttpJson() {
}

// methods

//--------------------------------------------------------------

void VHPhttpJson::init(string _send_url, string _get_url, int _user_id, string _user_name, string _auth_key){
    send_url = _send_url;
    get_url = _get_url;
    user_id = _user_id;
    user_name = _user_name;
    auth_key = _auth_key;
    streaming = false;
    ofAddListener(httpUtils.newResponseEvent, this, &VHPhttpJson::newResponse);
}

//----------------------------------------------------------------

int VHPhttpJson::addData(string _data_name, string _data_type) {
    cout << "Adding data: " << _data_name << " " << _data_type << endl;
    send.push_back(false);
    data.push_back("");
    data_name.push_back(_data_name);
    data_type.push_back(_data_type);
    return send.size() - 1;
}

//----------------------------------------------------------------

void VHPhttpJson::setData(int _i, string _data) {
    if (_i<data.size()) {
        data[_i] = _data;
        send[_i] = true;
    }
}

//----------------------------------------------------------------

void VHPhttpJson::update() {
    for (int i=0; i<data.size(); i++) {
        if (send[i]) {
            sendData(i);
            send[i] = false;
        }
    }
}

//----------------------------------------------------------------

void VHPhttpJson::sendData(int _i){
    cout << "sendData: " << _i << endl;
    ofxHttpForm form;
    form.action = send_url;
    form.method = OFX_HTTP_POST;
    form.addFormField("auth_key",auth_key);
    form.addFormField("user_name",user_name);
    form.addFormField("data_name",data_name[_i]);
    form.addFormField("data_type",data_type[_i]);
    form.addFormField("data",data[_i]);
    httpUtils.addForm(form);
}

void VHPhttpJson::sendData(string _data_name, string _data_type, string _data) {
    cout << "sendData: " << _data_name << " " << _data << endl;
    ofxHttpForm form;
    form.action = send_url;
    form.method = OFX_HTTP_POST;
    form.addFormField("auth_key", auth_key);
    form.addFormField("user_name", user_name);
    form.addFormField("data_name", _data_name);
    form.addFormField("data_type", _data_type);
    form.addFormField("data", _data);
    httpUtils.addForm(form);
}

//----------------------------------------------------------------

void VHPhttpJson::getData(string _user_name, string _data_name){
    cout << "getData (user_name:" << _user_name << ", data_name:" << _data_name << ")" << endl;
    ofxHttpForm form;
    form.action = get_url;
    form.method = OFX_HTTP_POST;
    // form.addFormField("auth_key",auth_key);
    form.addFormField("last", "true");
    form.addFormField("user_name", _user_name);
    form.addFormField("data_name", _data_name);
    httpUtils.addForm(form);
}

//----------------------------------------------------------------

void VHPhttpJson::newResponse(ofxHttpResponse & response){
    // cout << ofToString(response.status) << endl;
    ofxJSONElement result;
    result.parse(response.responseBody);
    bool error = result["error"].asBool();
    if (error) {
        string msg = result["error_msg"].asString();
        cout << msg << endl;
    } else {
        if (result["process_id"]=="exec_update_data") {
            string d_name = result["data"]["data_name"].asString();
            string d_type = result["data"]["data_type"].asString();
            string d_value = result["data"]["data_"+d_type].asString();
            string d_time = result["data"]["insert_datetime"].asString();
            cout << "success to parse JSON after sending data: " << d_name << " " << d_type << " " << d_value << " " << d_time << endl;
        } else if (result["process_id"]=="exec_get_data") {
            string d_name = result["data"][0]["data_name"].asString();
            string d_type = result["data"][0]["data_type"].asString();
            string d_value = result["data"][0]["data_"+d_type].asString();
            string d_time = result["data"][0]["insert_datetime"].asString();
            cout << "success to parse JSON after gathering data: " << d_name << " " << d_type << " " << d_value << " " << d_time << endl;
        } else {
            cout << response.responseBody << endl;
        }
    }
    
}

//----------------------------------------------------------------

void VHPhttpJson::start() {
    cout << "VHPhttpJson: httpUtils.start()" << endl;
    httpUtils.start();
    streaming = true;
}

//----------------------------------------------------------------

void VHPhttpJson::stop() {
    cout << "VHPhttpJson: httpUtils.stop()" << endl;
    httpUtils.stop();
    streaming = false;
}

//----------------------------------------------------------------



