#pragma once


#include "ofThread.h"
#include "ofxJSONElement.h"


class VHPthreadedJson: public ofThread {
public:
    VHPthreadedJson() {
    }
    
    void init(string _url, int _user_id, string _user_name, string _auth_key) {
        url = _url;
        user_id = _user_id;
        user_name = _user_name;
        auth_key = _auth_key;
    }

    void start() {
        cout << "VHPthreadedJson startThread()" << endl;
        startThread();
    }

    void stop() {
        cout << "VHPthreadedJson stopThread()" << endl;
        stopThread();
    }

    void threadedFunction() {
        while(isThreadRunning()) {
            if(lock()) {
                for (int i=0; i<data.size(); i++) {
                    if (send[i]) {
                        ofxJSONElement  response;
                        if (!response.open(data_url[i] + data[i])) {
                            // cout << "Failed to parse JSON" << endl;
                            ofLogWarning("threadedFunction()") << "Failed to parse JSON.";
                        } else {
                            bool error = response["error"].asBool();
                            if (error) {
                                string msg = response["error_msg"].asString();
                                // cout << msg << endl;
                                ofLogWarning("threadedFunction()") << msg;
                            } else {
                                cout << "success to parse JSON: " << data[i] << endl;
                            }
                        }
                        send[i] = false;
                    }
                }
                unlock();
                sleep(20);
            } else {
                ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
            }
        }
    }

    void setData(int _n, string _data) {
        if (_n<data.size()) {
            data[_n] = _data;
            send[_n] = true;
        }
    }
    int addData(string _name, string _type) {
        cout << "Adding data: " << _name << " " << _type << endl;
        send.push_back(false);
        data.push_back("");
        data_url.push_back(url +"?auth_key="+ auth_key +"&user_name="+ user_name +"&data_name="+ _name +"&data_type="+ _type +"&data=");
        return data_url.size() - 1;
        unlock();
    }
    vector<bool>        send;
    vector<string>      data;
    string              url;
    int                 user_id;
    string              user_name;
    string              auth_key;
    vector<string>      data_url;
    
protected:
    
};
