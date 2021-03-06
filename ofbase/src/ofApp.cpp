#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // settings
    if( settings.loadFile("mySettings.xml") ){
        cout << "mySettings.xml loaded from documents folder!" << endl;
    } else if( settings.loadFile("mySettings.xml") ){
        cout << "mySettings.xml loaded from data folder!" << endl;
    } else{
        cout << "unable to load mySettings.xml check data/ folder" << endl;
    }
    
    // Cam
    cam.setup(settings.getValue("CAM_WIDTH", 1280), settings.getValue("CAM_HEIGHT", 720), settings.getValue("DEVICE_ID", 0), settings.getValue("CAM_FRAMERATE", 60), settings.getValue("FFMPEG", "/Applications/ffmpeg/ffmpeg"));
    
    // OSC
    osc.setup(settings.getValue("HOST", "localhost"), settings.getValue("S_PORT", 8000), settings.getValue("R_PORT", 9000));
     
    // openframeworks
	ofSetVerticalSync(true);
    
    // info
    font.loadFont("verdana.ttf", 8, false, true);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0,0,0);
    osc.update(cam);
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw();
    ofPushStyle();
    ofSetHexColor(0xffffff);
    font.drawString("framerate: "+ofToString(ofGetFrameRate()), 20, cam.height+ 20);
    ofPopStyle();
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
