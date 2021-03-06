#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofAddListener(updateData.newResponseEvent,this,&ofApp::newResponse);
    updateData.start();
    
    if( XML.loadFile("mySettings.xml") ){
        cout << "mySettings.xml loaded from documents folder!" << endl;
    }else{
        cout << "unable to load mySettings.xml check data/ folder" << endl;
    }
    
    string h = XML.getValue("HOST", "localhost");
    user_name = XML.getValue("USER", "horacio");
    getdata_URL = XML.getValue("GETDATAURL", "http://test.escoitar.org/exec/get_data.php");
    update_URL = XML.getValue("UPDATEURL", "http://test.escoitar.org/exec/update_data.php");
    int rport = XML.getValue("RPORT", 8000);
    int sport = XML.getValue("SPORT", 9000);
    
    auth_key = "your auth_key here";
    
    host = ofSplitString(h, ",");
    for (int i=0; i<host.size(); i++) {
        sender.push_back(ofxOscSender());
        // open an outgoing connection to HOST:PORT
        sender[i].setup(host[i], sport);
        cout << "host" << i << ": " << host[i] << ", " << sport << endl;
        ofxOscMessage m;
        m.setAddress("/tech");
        m.addStringArg("start");
        sender[i].sendMessage(m);
    }
    // open the input connection to PORT
    cout << "receiver port: " << rport << endl;
    receiver.setup(rport);
    
    timer = 0;
    loaded = false;
    
}

//--------------------------------------------------------------
void ofApp::getResponse() {
    string url = update_URL + "?user_name=" + user_name + "&last=true";
    if (!response.open(url)) {
        cout << "Failed to parse JSON" << endl;
        loaded = false;
    } else {
        bool error = response["error"].asBool();
        cout << error << endl;
        if (error) {
            string msg = response["error_msg"].asString();
            cout << msg << endl;
        } else {
            int n = response["data"].size();
            cout << n << " elements being streamed" << endl;
            for(int i = 0; i < n; i++) {
                ofxJSONElement s = response["data"][i];
                addStreamer(s);
            }
        }
        loaded = true;
    }
}

//--------------------------------------------------------------
void ofApp::newResponse(ofxHttpResponse & response){
    cout << (string)response.responseBody <<endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    timer++;
    if ((loaded)&&(timer>10)) {
        timer = 0;
        getResponse();
    } else if (timer>500) {
        timer = 0;
        getResponse();
    }
    
}

//--------------------------------------------------------------
void ofApp::addStreamer(ofxJSONElement& _s) {
    int id = ofToInt(_s["id"].asString());
    int user_id = ofToInt(_s["user_id"].asString());
    bool added = false;
    for (int i=0; i<streamers.size(); i++) {
        if (streamers[i].user_id == user_id) {
            ofxOscMessage m = streamers[i].setData(_s);
            for (int i=0; i<host.size(); i++) {
               sender[i].sendMessage(m);
            }
            streamers[i].info();
            added = true;
            break;
        }
    }
    if (!added) {
        streamers.push_back(VHPstreamer(user_id, user_name));
        ofxOscMessage m = streamers[streamers.size()-1].setData(_s);
        for (int i=0; i<host.size(); i++) {
            sender[i].sendMessage(m);
        }
        cout << "New streamer created" <<endl;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,255,255);
	ofSetColor(0,0,0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key=='s'){ // sending data test
        ofxHttpForm form;
        form.action = update_URL;
        form.method = OFX_HTTP_POST;
        form.addFormField("auth_key",auth_key);
        form.addFormField("user_name",user_name);
        form.addFormField("data_name","test");
        form.addFormField("data_type","bool");
        form.addFormField("data","0");
        updateData.addForm(form);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
