#include "VHPcam.h"

//constructor

//----------------------------------------------------------------	
VHPcam::VHPcam() {
    
}

// methods

//----------------------------------------------------------------
void VHPcam::setup(int _w, int _h, int _d, int _f, string _ffmpeg) {
    
    // video setup
    camWidth 		= _w;	// try to grab at this size.
	camHeight 		= _h;
	totalPixels     = camWidth * camHeight * 3;
    
    automata.set(ofRandom(camWidth), ofRandom(camHeight), 2.0);
    
    // contrast
	contrast.setup();
    
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
    
    cout << "DeviceID: " << _d << " FrameRate: " << _f << " camWidth: " << camWidth << " camHeight: " << camHeight  << endl;
    vidGrabber.setVerbose(true);
    vidGrabber.setDeviceID(_d);
	//vidGrabber.setDesiredFrameRate(_f);
    camRecording = false;
    
    // Video devices
    for(int i = 0; i < videoDevices.size(); i++){
        cout << videoDevices[i] << endl;
    }
    
    // control variables
    show = false;
    showPlayer = false;
    
    // init grabber
    vidGrabber.initGrabber(camWidth,camHeight);
    
    // allocate the frame buffer object
    camFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    invertFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    scaleFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    stelaFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    of2Fbo.allocate(camWidth, camHeight, GL_RGB, 0);
    drawFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    recorderFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    
    // allocate textures
    vidTexture.allocate(camWidth, camHeight, GL_RGB);
    of2Texture.allocate(camWidth, camHeight, GL_RGB);
    stelaTexture.allocate(camWidth, camHeight, GL_RGB);
    drawTexture.allocate(camWidth, camHeight, GL_RGB);
    
    //shaders
    #ifdef TARGET_OPENGLES
	camShader.load("shaders_gles/greyscale.vert","shaders_gles/cam.frag");
	stelaShader.load("shaders_gles/greyscale.vert","shaders_gles/stela.frag");
    cout << "shadersES2" << endl;
    #else
	if(ofGetGLProgrammableRenderer()){
		camShader.load("shaders_gl3/greyscale.vert", "shaders_gl3/cam.frag");
		stelaShader.load("shaders_gl3/greyscale.vert", "shaders_gl3/stela.frag");
        cout << "shadersGL3" << endl;
	}else{
		camShader.load("shaders/greyscale.vert", "shaders/cam.frag");
		stelaShader.load("shaders/greyscale.vert", "shaders/stela.frag");
        cout << "shadersGL2" << endl;
	}
    #endif
    
    //recorder
    vidRecorder.setFfmpegLocation(_ffmpeg);
    
    // recording variables
    recordingNum = 0;
    playingNum = 0;
    newRecording = "";
    fileBeingRecorded = "";
    recording = false;
    playing = false;
    invert = false;
    
    ntarot = 0;
    
    mode = 0;
}

void VHPcam::settings(int _stela, int _mixture, int _show, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3){
    percent[0] = ofClamp(_stela, 0, 1000);
    percent[1] = ofClamp(_mixture, 0, 1000);
    _show==0 ? show = false : show = true;
    setContrast(0, _e0, _f0);
    setContrast(1, _e1, _f1);
    setContrast(2, _e2, _f2);
    setContrast(3, _e3, _f3);
}

//----------------------------------------------------------------
void VHPcam::update() {
    
    switch (mode) {
        case 0: // narrative
            if (camRecording) {
                vidGrabber.update();
                if (vidGrabber.isFrameNew()){
                    vidTexture.loadData(vidGrabber.getPixels(), camWidth, camHeight, GL_RGB);
                    if (invert) {
                        invertFbo.begin();
                        vidTexture.draw(camWidth, 0, -camWidth, camHeight);
                        invertFbo.end();
                        invertFbo.readToPixels(invertPix);
                        vidTexture.loadData(invertPix.getPixels(), camWidth, camHeight, GL_RGB);
                    }
                    stela();
                }
            } else if (playing) {
                player.update();
                if (player.isPlaying()) {
                    vidTexture.loadData(player.getPixels(), camWidth, camHeight, GL_RGB);
                    stela();
                }
            } else {
                int width = tarot[ntarot].getWidth() * automata.z;
                int height = tarot[ntarot].getHeight() * automata.z;
                //automata += ofVec3f(ofRandom(-4,4),ofRandom(-4,4),0);
                checkAutomata();
                //escalado
                scaleFbo.begin();
                tarot[ntarot].draw(automata.x, automata.y, width, height);
                scaleFbo.end();
                scaleFbo.readToPixels(scalePix);
                vidTexture.loadData(scalePix.getPixels(), camWidth, camHeight, GL_RGB);
                stela();
            }
            break;
        case 1: // oscFace
            hierofante.update();
            invertFbo.begin();
            hierofante.draw();
            invertFbo.end();
            invertFbo.readToPixels(invertPix);
            vidTexture.loadData(invertPix.getPixels(), camWidth, camHeight, GL_RGB);
            stela();
            break;
        default:
            break;
    }
    
    // Video
    of2Fbo.begin();
    camShader.begin();
    camShader.setUniformTexture("texE1", contrast.texture[e[1]], 1);
    camShader.setUniformTexture("texE2", contrast.texture[e[2]], 2);
    camShader.setUniformTexture("texE3", contrast.texture[e[3]], 3);
    camShader.setUniform1f("f1", f[1]);
    camShader.setUniform1f("f2", f[2]);
    camShader.setUniform1f("f3", f[3]);
    stelaFbo.draw(0, 0, camWidth, camHeight);
    camShader.end();
    of2Fbo.end();
    
    // copy the frame buffer pixels
    of2Fbo.readToPixels(of2Pix);
    of2Texture.loadData(of2Pix.getPixels(), camWidth, camHeight, GL_RGB);
    stelaFbo.readToPixels(stelaPix);
    stelaTexture.loadData(stelaPix.getPixels(), camWidth, camHeight, GL_RGB);
    
    drawInFbo();
    if(recording){
        //recorderTexture.loadScreenData(0, 0, camWidth*2, camHeight*2);
        recorderFbo.begin();
        drawTexture.draw(0, 0, camWidth, camHeight);
        recorderFbo.end();
        recorderFbo.readToPixels(recorderPix);
        vidRecorder.addFrame(recorderPix);
    }
    
}
    
//----------------------------------------------------------------
void VHPcam::stela() {
    // Stela
    stelaFbo.begin();
    stelaShader.begin();
    stelaShader.setUniformTexture("tex1", stelaTexture, 1);
    stelaShader.setUniform1f("mixture", percent[0]/1000.0);
    vidTexture.draw(0, 0, camWidth, camHeight);
    stelaShader.end();
    stelaFbo.end();
}

//----------------------------------------------------------------

void VHPcam::drawInFbo() {
    drawFbo.begin();
    of2Fbo.draw(0,0);
    if ((player.isPlaying())&&(showPlayer)) {
        player.draw(camWidth*2/4, camHeight*3/4, camWidth/4, camHeight/4);
    }
    drawFbo.end();
    drawFbo.readToPixels(drawPix);
    drawTexture.loadData(drawPix.getPixels(), camWidth, camHeight, GL_RGB);
}

void VHPcam::draw(int _x, int _y, int _width, int _height) {
    drawTexture.draw( _x, _y, _width, _height);
}

//----------------------------------------------------------------

void VHPcam::setContrast(int _n, float _e, float _f) {
    _n = ofClamp(_n, 0, 3);
    e[_n] = (int) ofClamp(_e, 0, 255);
    f[_n] = (int) ofClamp(_f, 0, 255);
    cout << "e["<< _n << "]: "<< e[_n] << ", f[" << _n << "]: "<< f[_n] << endl;
}

void VHPcam::setMode(int _m) {
    // 0 interface, 1 sierpinski mago, 2 mascara + grid, 3 sierpinski styled, 4 Black holes white wall
    mode = _m;
}

//----------------------------------------------------------------

void VHPcam::save(int _s) {
    if (_s == 0) {
        if(recording) {
            vidRecorder.close();
            newRecording = fileBeingRecorded;
            recording = false;
        }
    } else if (_s == 1){
        if(!recording) {
            vidRecorder.setup("saved/clip_"+ ofToString(recordingNum) +".mov", camWidth, camHeight, 15);
            fileBeingRecorded = "saved/clip_"+ ofToString(recordingNum) +".mov";
            recording = true;
            recordingNum++;
        }
    }
}

//----------------------------------------------------------------

void VHPcam::play(int _p, int _n) {
    if (_p == 0) {
        if(playing) {
            player.stop();
            playing = false;
        }
    } else if (_p == 1){
        if(!playing) {
            playing = load(_n);
        } else {
            player.stop();
            playing = load(_n);
        }
    }
}

//----------------------------------------------------------------

string VHPcam::getNewRecording() {
    return newRecording;
}

//----------------------------------------------------------------

void VHPcam::emptyNewRecording() {
    newRecording = "";
}

//----------------------------------------------------------------

bool VHPcam::load(int _n){
	bool exists = player.loadMovie("recorded/clip_"+ofToString(_n)+".mov");
    if (exists) player.play();
    return exists;
}

//----------------------------------------------------------------

void VHPcam::loadImage(string _image) {
	tarot.push_back(ofImage());
    tarot[tarot.size()-1].loadImage(_image);
    cout << _image << " width: " << tarot[tarot.size()-1].getWidth() << " height: " << tarot[tarot.size()-1].getHeight() << endl;
}

//----------------------------------------------------------------

void VHPcam::setAutomata(int _x, int _y) {
	automata.x = _x*1.0*(camWidth-tarot[0].getWidth()* automata.z)/camWidth;
	automata.y = _y*1.0*(camHeight-tarot[0].getHeight()* automata.z)/camHeight;
}

//----------------------------------------------------------------

void VHPcam::checkAutomata() {
    if (automata.x>=0) {
        automata.x = 0;
    } else if (automata.x<=(camWidth - tarot[0].getWidth()* automata.z)){
        automata.x = camWidth - tarot[0].getWidth()* automata.z;
    }
    if (automata.y>=0) {
        automata.y = 0;
    } else if (automata.y<=(camHeight - tarot[0].getHeight()* automata.z)){
        automata.y = camHeight - tarot[0].getHeight()* automata.z;
    }
}