#ifndef _VHP_HTTPJSON
#define _VHP_HTTPJSON

#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxJSON.h"

//--------------------------------------------------------
class VHPhttpJson {
public:
    
    //constructor
    VHPhttpJson();
    
    // variables
    vector<bool>        send;
    vector<string>      data;
    vector<string>      data_name;
    vector<string>      data_type;
    string              send_url;
    string              get_url;
    int                 user_id;
    string              user_name;
    string              auth_key;
    ofxHttpUtils        httpUtils;
    bool                streaming;
    
    // methods
    void init(string _send_url, string _get_url, int _user_id, string _user_name, string _auth_key);
    int addData(string _name, string _type);
    void setData(int _i, string _data);
    void update();
    void sendData(int _i);
    void sendData(string _data_name, string _data_type, string _data);
    void getData(string _user_name, string _data_name);
    void newResponse(ofxHttpResponse & response);
    void start();
    void stop();
    
private:
	
};
//--------------------------------------------------------

#endif