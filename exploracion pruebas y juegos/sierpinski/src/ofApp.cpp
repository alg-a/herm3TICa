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

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	//videoTexture.draw(0, 0, camWidth/2, camHeight/2);
    sierpinski.draw();
    font.drawString(ofToString(ofGetFrameRate()), 739, 24);
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
