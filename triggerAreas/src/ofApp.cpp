#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // settings
    if( XML.loadFile("mySettings.xml") ){
        cout << "mySettings.xml loaded from documents folder!" << endl;
    } else if( XML.loadFile("mySettings.xml") ){
        cout << "mySettings.xml loaded from data folder!" << endl;
    } else{
        cout << "unable to load mySettings.xml check data/ folder" << endl;
    }
    int id = XML.getValue("DEVICE_ID", 0);
    string host = XML.getValue("HOST", "localhost");
    string data_name = XML.getValue("DATA_NAME", "trigger");
    int r_port = XML.getValue("R_PORT", 9000);
    int s_port = XML.getValue("S_PORT", 8000);
    int x = XML.getValue("X", 0);
    int y = XML.getValue("Y", 0);
    int w = XML.getValue("WIDTH", 100);
    int h = XML.getValue("HEIGHT", 100);
    
    // Cam
    camWidth 		= 1280;	// try to grab at this size.
	camHeight 		= 720;
	totalPixels     = camWidth*camHeight*3;
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    vidGrabber.setDeviceID(id);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
    videoTexture.allocate(camWidth, camHeight, GL_RGB);
    
    // openframeworks
	ofSetVerticalSync(true);
    
    // triggerArea
    area.setup(x, y, w, h, host, s_port, data_name);
    
    // OSC
    receiver.setup(r_port);
    cout << "receiver port: " << r_port << endl;
    
    // info
    font.loadFont("verdana.ttf", 8, false, true);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0,0,0);
	vidGrabber.update();
	if (vidGrabber.isFrameNew()){
        unsigned char * pixels = vidGrabber.getPixels();
        area.update(camWidth, camHeight, totalPixels, pixels);
        videoTexture.loadData(pixels, camWidth, camHeight, GL_RGB);
    }
    while(receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if (m.getAddress() == "/threshold") {
            area.setThreshold(m.getArgAsInt32(0));
        } else if (m.getAddress() == "/position") {
            float x = m.getArgAsFloat(0)*(camWidth-area.width)/100.0;
            float y = m.getArgAsFloat(1)*(camHeight-area.height)/100.0;
            area.setPosition((int)x, (int)y);
        } else if (m.getAddress() == "/width") {
            float w = m.getArgAsFloat(0)*(camWidth-area.getX())/100.0;
            area.setWidth((int)w);
        } else if (m.getAddress() == "/height") {
            float h = m.getArgAsFloat(0)*(camHeight-area.getY())/100.0;
            area.setHeight((int)h);
        } else if (m.getAddress() == area.data.getAddress()) {
            if (m.getArgAsInt32(0)==1) {
                area.data.setActive(true);
            } else {
                area.data.setActive(false);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	videoTexture.draw(0, 0, camWidth, camHeight);
    area.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
