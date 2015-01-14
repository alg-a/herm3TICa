#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
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
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	ofSetVerticalSync(true);
    
    videoTexture.allocate(camWidth, camHeight, GL_RGB);
    
    sierpinski.setup();
    receiver.setup(9000);
    
    font.loadFont("verdana.ttf", 8, false, true);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0,0,0);
	vidGrabber.update();
	if (vidGrabber.isFrameNew()){
        unsigned char * pixels = vidGrabber.getPixels();
        videoTexture.loadData(pixels, camWidth, camHeight, GL_RGB);
        sierpinski.update(camWidth, totalPixels, pixels);
    }
    while(receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if (m.getAddress() == "/threshold") {
            sierpinski.setThreshold(m.getArgAsInt32(0));
        } else if (m.getAddress() == "/sierpinski_0") {
            if (m.getArgAsInt32(0)==1) {
                sierpinski.sierpinski_0.setActive(true);
            } else {
                sierpinski.sierpinski_0.setActive(false);
            }
        } else if (m.getAddress() == "/sierpinski_1") {
            int x_0 = m.getArgAsInt32(1);
            int y_0 = m.getArgAsInt32(2);
            if (m.getArgAsInt32(0)==1) {
                sierpinski.sierpinski_1[x_0][y_0].setActive(true);
            } else {
                sierpinski.sierpinski_1[x_0][y_0].setActive(false);
            }
        } else if (m.getAddress() == "/sierpinski_2") {
            int x_0 = m.getArgAsInt32(1);
            int y_0 = m.getArgAsInt32(2);
            int x_1 = m.getArgAsInt32(3);
            int y_1 = m.getArgAsInt32(4);
            if (m.getArgAsInt32(0)==1) {
                sierpinski.sierpinski_2[x_0][y_0][x_1][y_1].setActive(true);
            } else {
                sierpinski.sierpinski_2[x_0][y_0][x_1][y_1].setActive(false);
            }
        } else if (m.getAddress() == "/sierpinski_3") {
            int x_0 = m.getArgAsInt32(1);
            int y_0 = m.getArgAsInt32(2);
            int x_1 = m.getArgAsInt32(3);
            int y_1 = m.getArgAsInt32(4);
            int x_2 = m.getArgAsInt32(5);
            int y_2 = m.getArgAsInt32(6);
            if (m.getArgAsInt32(0)==1) {
                sierpinski.sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2].setActive(true);
            } else {
                sierpinski.sierpinski_3[x_0][y_0][x_1][y_1][x_2][y_2].setActive(false);
            }
        } else if (m.getAddress() == "/sierpinski_4") {
            int x_0 = m.getArgAsInt32(1);
            int y_0 = m.getArgAsInt32(2);
            int x_1 = m.getArgAsInt32(3);
            int y_1 = m.getArgAsInt32(4);
            int x_2 = m.getArgAsInt32(5);
            int y_2 = m.getArgAsInt32(6);
            int x_3 = m.getArgAsInt32(7);
            int y_3 = m.getArgAsInt32(8);
            if (m.getArgAsInt32(0)==1) {
                sierpinski.sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3].setActive(true);
            } else {
                sierpinski.sierpinski_4[x_0][y_0][x_1][y_1][x_2][y_2][x_3][y_3].setActive(false);
            }
        }

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	//videoTexture.draw(0, 0, camWidth/2, camHeight/2);
    sierpinski.draw();
    ofSetHexColor(0xffffff);
	font.drawString(ofToString(sierpinski.threshold), 739, 10);
	font.drawString(ofToString(ofGetFrameRate()), 739, 24);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f'){
		ofToggleFullscreen();
	}
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
