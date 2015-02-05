#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    camWidth 		= 1280;	// try to grab at this size.
	camHeight 		= 720;
	totalPixels     = camWidth*camHeight*3;
    
    w[0] = 1460; // 1458 + 2 (*1)
    h[0] = 729;
	w[1] = 488; // 486 + 2 (*3)
    h[1] = 243;
	w[2] = 164; // 162 + 2 (*9)
    h[2] = 81;
    w[3] = 56; // 54 + 2 (*27)
    h[3] = 27;
	w[4] = 20; // 18 + 2 (*81)
    h[4] = 9;
	w[5] = 8; // 6 + 2 (*243)
    h[5] = 3;

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
    videoTexture.allocate(camWidth, camHeight, GL_RGB);
    
	ofSetVerticalSync(true);
    
    font.loadFont("verdana.ttf", 8, false, true);
    
    #ifdef TARGET_OPENGLES
	shader.load("shaders_gles/noise.vert","shaders_gles/noise.frag");
    cout << "shadersES2" << endl;
    #else
	if(ofGetGLProgrammableRenderer()){
		shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
        cout << "shadersGL3" << endl;
	}else{
		shader.load("shaders/noise.vert", "shaders/noise.frag");
        cout << "shadersGL2" << endl;
	}
    #endif

    // allocate the frame buffer object
    for (int i=0; i<6; i++) {
        Fbo[i].allocate(w[i], h[i], GL_RGB, 0);
        Texture[i].allocate(w[i], h[i], GL_RGB);
        Texture[i].setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
	if (vidGrabber.isFrameNew()){
        videoTexture.loadData(vidGrabber.getPixels(), camWidth, camHeight, GL_RGB);
        
        for (int i=0; i<6; i++) {
            Fbo[i].begin();
            ofClear(0, 0, 0, 255);
            videoTexture.draw(0, 0, w[i]-2, h[i]);
            Fbo[i].end();
            Fbo[i].readToPixels(Pix[i]);
            Texture[i].loadData(Pix[i].getPixels(), w[i], h[i], GL_RGB);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0,0,0);
    /*
    int n = 1;
    for (int i=0; i<6; i++) {
        shader.begin();
        Texture[i].draw(0, 0, w[i]*n, h[i]*n);
        shader.end();
        n *= 3;
    }
    */
    int n = 243;
    for (int i=0; i<6; i++) {
        shader.begin();
        Texture[5-i].draw(0, 0, w[5-i]*n, h[5-i]*n);
        shader.end();
        n /= 3;
    }
	font.drawString(ofToString(ofGetFrameRate()), 10, camHeight +20);
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
