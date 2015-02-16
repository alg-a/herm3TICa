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
    cam.settings(settings.getValue("STELA", 100), 0, settings.getValue("SHOW", 0), settings.getValue("CONTRAST_GREY_E", 140), settings.getValue("CONTRAST_GREY_F", 172), settings.getValue("CONTRAST_R_E", 165), settings.getValue("CONTRAST_R_F", 187), settings.getValue("CONTRAST_G_E", 165), settings.getValue("CONTRAST_G_F", 187), settings.getValue("CONTRAST_B_E", 165), settings.getValue("CONTRAST_B_F", 187));
    int n = settings.getNumTags("IMAGE");
    for(int i = 0; i < n; i++){
        cam.loadImage(settings.getValue("IMAGE", "", i));
    }
    cam.hierofante.setup(settings);
    
    // OSC
    osc.setup(settings.getValue("HOST", "localhost"), settings.getValue("S_PORT", 8000), settings.getValue("R_PORT", 9000));
    osc.sendSettings(settings.getValue("STELA", 100), settings.getValue("SHOW", 0), settings.getValue("CONTRAST_GREY_E", 140), settings.getValue("CONTRAST_GREY_F", 172), settings.getValue("CONTRAST_R_E", 165), settings.getValue("CONTRAST_R_F", 187), settings.getValue("CONTRAST_G_E", 165), settings.getValue("CONTRAST_G_F", 187), settings.getValue("CONTRAST_B_E", 165), settings.getValue("CONTRAST_B_F", 187));
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
    font.drawString("framerate: "+ofToString(ofGetFrameRate()), 20, cam.camHeight+ 20);
    font.drawString("automata: "+ofToString(cam.automata.x)+", "+ofToString(cam.automata.y), 20, cam.camHeight+ 40);
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
    cam.setAutomata(x,y);
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
