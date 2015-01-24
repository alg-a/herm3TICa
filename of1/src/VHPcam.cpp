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
    
    // Video devices
    for(int i = 0; i < videoDevices.size(); i++){
        cout << videoDevices[i] << endl;
    }
    
    // control variables
    show = false;
    
    // init grabber
    vidGrabber.initGrabber(camWidth,camHeight);
    
    // allocate the frame buffer object
    camFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    playerFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    stelaFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    greyFbo.allocate(camWidth/2, camHeight/2, GL_RGB, 0);
    
    // allocate textures
    videoTexture.allocate(camWidth, camHeight, GL_RGB);
    playerTexture.allocate(camWidth, camHeight, GL_RGB);
    timeBufferTexture.allocate(camWidth, camHeight, GL_RGB);
    
    //shaders
    #ifdef TARGET_OPENGLES
	camShader.load("shaders_gles/greyscale.vert","shaders_gles/cam.frag");
	greyShader.load("shaders_gles/greyscale.vert","shaders_gles/greyscale.frag");
	stelaShader.load("shaders_gles/greyscale.vert","shaders_gles/stela.frag");
    cout << "shadersES2" << endl;
    #else
	if(ofGetGLProgrammableRenderer()){
		camShader.load("shaders_gl3/greyscale.vert", "shaders_gl3/cam.frag");
		greyShader.load("shaders_gl3/greyscale.vert", "shaders_gl3/greyscale.frag");
		stelaShader.load("shaders_gl3/greyscale.vert", "shaders_gl3/stela.frag");
        cout << "shadersGL3" << endl;
	}else{
		camShader.load("shaders/greyscale.vert", "shaders/cam.frag");
		greyShader.load("shaders/greyscale.vert", "shaders/greyscale.frag");
		stelaShader.load("shaders/greyscale.vert", "shaders/stela.frag");
        cout << "shadersGL2" << endl;
	}
    #endif
    
    //recorder
    camRecorder.setFfmpegLocation(_ffmpeg);
    greyRecorder.setFfmpegLocation(_ffmpeg);
    
    // recording variables
    recordingNum = 0;
    playingNum = 0;
    newRecording = "";
    recording = false;
    playing = false;
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
    vidGrabber.update();
    player.update();
    
	if (vidGrabber.isFrameNew()){
        /*
        int w = camWidth/2;
        int h = camHeight/2;
        int t = camWidth*camHeight/4;
        for (int i=0; i<t; i++) {
            int x = i % w;
            int y = (i - x) / w;
            x *= 2;
            y *= 2;
            int pos = (y * camWidth * 3 + x*3) % totalPixels;
            int val = 0.2126 * pixels[pos] + 0.7152 * pixels[pos+1] + 0.0722 * pixels[pos+2];
            val = contrast.ajusteExponencial(val, e[0], f[0]);
            buffer[i] = val;
        }
        for (int i=0; i<totalPixels; i+=3) {
            pixels[i] = contrast.ajusteExponencial(pixels[i], e[1], f[1]);
            pixels[i+1] = contrast.ajusteExponencial(pixels[i+1], e[2], f[2]);
            pixels[i+2] = contrast.ajusteExponencial(pixels[i+2], e[3], f[3]);
            pixels[i] = mixture.value[pixels[i]][timeBuffer[i]][percent];
            pixels[i+1] = mixture.value[pixels[i+1]][timeBuffer[i+1]][percent];
            pixels[i+2] = mixture.value[pixels[i+2]][timeBuffer[i+2]][percent];
            //int x = i % (camWidth * 3);
            //int y = (i - x) / (camWidth * 3);
            // do something with pixels[i]  ...
        }
         */
        videoTexture.loadData(vidGrabber.getPixels(), camWidth, camHeight, GL_RGB);
        if (player.isPlaying()) {
            playerTexture.loadData(player.getPixels(), camWidth, camHeight, GL_RGB);
            playerFbo.begin();
            stelaShader.begin();
            stelaShader.setUniformTexture("tex1", playerTexture, 1);
            stelaShader.setUniform1f("mixture", percent[1]/1000.0);
            videoTexture.draw(0, 0, camWidth, camHeight);
            stelaShader.end();
            playerFbo.end();
            playerFbo.readToPixels(playerPix);
            videoTexture.loadData(playerPix.getPixels(), camWidth, camHeight, GL_RGB);
        }
        // Stela
        stelaFbo.begin();
        stelaShader.begin();
        stelaShader.setUniformTexture("tex1", timeBufferTexture, 1);
        stelaShader.setUniform1f("mixture", percent[0]/1000.0);
        videoTexture.draw(0, 0, camWidth, camHeight);
        stelaShader.end();
        stelaFbo.end();
        // Cam
        camFbo.begin();
        camShader.begin();
        camShader.setUniformTexture("texE1", contrast.texture[e[1]], 1);
        camShader.setUniformTexture("texE2", contrast.texture[e[2]], 2);
        camShader.setUniformTexture("texE3", contrast.texture[e[3]], 3);
        camShader.setUniform1f("f1", f[1]);
        camShader.setUniform1f("f2", f[2]);
        camShader.setUniform1f("f3", f[3]);
        stelaFbo.draw(0, 0, camWidth, camHeight);
        camShader.end();
        camFbo.end();
        // Grey
        greyFbo.begin();
        greyShader.begin();
        greyShader.setUniformTexture("texE", contrast.texture[e[0]], 1);
        greyShader.setUniform1f("f", f[0]);
        videoTexture.draw(0, 0, camWidth/2, camHeight/2);
        greyShader.end();
        greyFbo.end();
        // copy the frame buffer pixels
        stelaFbo.readToPixels(stelaPix);
        timeBufferTexture.loadData(stelaPix.getPixels(), camWidth, camHeight, GL_RGB);
        
        if(recording){
            //camFbo.readToPixels(camPix);
            camRecorder.addFrame(stelaPix);
            greyFbo.readToPixels(greyPix);
            greyRecorder.addFrame(greyPix);
            
        }
        
    }
}

//----------------------------------------------------------------

void VHPcam::draw() {
    camFbo.draw(0,0);
    if (show) greyFbo.draw(camWidth*3/4, camHeight*3/4, camWidth/4, camHeight/4);
    if (player.isPlaying()) {
        player.draw(camWidth*2/4, camHeight*3/4, camWidth/4, camHeight/4);
    }
    
    //if (vidRecorder->isRecording()){
        // do something
    //}
}

//----------------------------------------------------------------

void VHPcam::setContrast(int _n, float _e, float _f) {
    _n = ofClamp(_n, 0, 3);
    e[_n] = (int) ofClamp(_e, 0, 255);
    f[_n] = (int) ofClamp(_f, 0, 255);
    cout << "e["<< _n << "]: "<< e[_n] << ", f[" << _n << "]: "<< f[_n] << endl;
}

//----------------------------------------------------------------

void VHPcam::save(int _s) {
    if (_s == 0) {
        if(recording) {
            camRecorder.close();
            greyRecorder.close();
            recording = false;
        }
    } else if (_s == 1){
        if(!recording) {
            camRecorder.setup("saved/clip_"+ ofToString(recordingNum) +".mov", camWidth, camHeight, 15);
            greyRecorder.setup("saved/clip_grey_"+ ofToString(recordingNum) +".mov", camWidth/2, camHeight/2, 15);
            recording = true;
            recordingNum++;
        }
    }
}

void VHPcam::play(int _p, int _n) {
    if (_p == 0) {
        if(playing) {
            player.stop();
            playing = false;
        }
    } else if (_p == 1){
        if(!playing) {
            playing = load(_n);
        }
    }
}


string VHPcam::getNewRecording() {
    return newRecording;
}

void VHPcam::emptyNewRecording() {
    newRecording = "";
}

bool VHPcam::load(int _n){
	bool exists = player.loadMovie("saved/clip_"+ofToString(_n)+".mov");
    if (exists) player.play();
    return exists;
}

//----------------------------------------------------------------
