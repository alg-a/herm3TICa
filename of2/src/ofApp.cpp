#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    // settings
    if( settings.loadFile("mySettings.xml") ){
        cout << "mySettings.xml loaded from documents folder!" << endl;
    } else if( settings.loadFile("mySettings.xml") ){
        cout << "mySettings.xml loaded from data folder!" << endl;
    } else{
        cout << "unable to load mySettings.xml check data/ folder" << endl;
    }
    
    // Cam
    cam.setup(settings.getValue("CAM_WIDTH", 1280), settings.getValue("CAM_HEIGHT", 720), settings.getValue("DEVICE_ID", 0), settings.getValue("CAM_FRAMERATE", 60), settings.getValue("FFMPEG", "/Applications/ffmpeg/ffmpeg"), settings.getValue("RECORDING", 0), settings.getValue("BKGRECORDING", 0));
    cam.settings(
                 settings.getValue("STELA", 100),
                 0,
                 settings.getValue("CONTRAST_GREY_E", 140),
                 settings.getValue("CONTRAST_GREY_F", 172),
                 settings.getValue("CONTRAST_R_E", 165),
                 settings.getValue("CONTRAST_R_F", 187),
                 settings.getValue("CONTRAST_G_E", 165),
                 settings.getValue("CONTRAST_G_F", 187),
                 settings.getValue("CONTRAST_B_E", 165),
                 settings.getValue("CONTRAST_B_F", 187),
                 settings.getValue("BLUR_GREY", 1.7),
                 settings.getValue("RECORTE_BLACK", 0.25),
                 settings.getValue("RECORTE_WHITE", 0.25));
    // OSC
    osc.setup(settings.getValue("HOST", "localhost"), settings.getValue("REMOTE_HOST", "172.24.200.243"), settings.getValue("S_PORT", 8000), settings.getValue("REMOTE_S_PORT", 8002), settings.getValue("R_PORT", 9000));
    osc.sendSettings(
                     settings.getValue("STELA", 100),
                     settings.getValue("SHOW", 0),
                     settings.getValue("CONTRAST_GREY_E", 140),
                     settings.getValue("CONTRAST_GREY_F", 172),
                     settings.getValue("CONTRAST_R_E", 165),
                     settings.getValue("CONTRAST_R_F", 187),
                     settings.getValue("CONTRAST_G_E", 165),
                     settings.getValue("CONTRAST_G_F", 187),
                     settings.getValue("CONTRAST_B_E", 165),
                     settings.getValue("CONTRAST_B_F", 187),
                     settings.getValue("BLUR_GREY", 1.7),
                     settings.getValue("RECORTE_BLACK", 0.25),
                     settings.getValue("RECORTE_WHITE", 0.25));
    // openframeworks
	ofSetVerticalSync(true);
    
    // info
    font.loadFont("verdana.ttf", 8, false, true);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0,0,0);
    osc.update(cam); // receive msg and set cam
    cam.update(osc.sender, osc.remoteSender); // update cam and send msg via osc
    cam.drawInFbo();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0,0,1920,1080);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f'){
		ofToggleFullscreen();
	} else if (key == 's') {
        cam.sierpinski.sendJson();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    cam.x = x;
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
