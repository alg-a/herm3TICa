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
    
    // init grabber
    vidGrabber.initGrabber(camWidth,camHeight);
    
    // allocate the frame buffer object
    camFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    
    // allocate textures
    videoTexture.allocate(camWidth, camHeight, GL_RGB);
    
    //recorder
    camRecorder.setFfmpegLocation(_ffmpeg);
    
    // recording variables
    recordingNum = 0;
    newRecording = "";
    fileBeingRecorded = "";
    recording = false;
    playing = false;
}

//----------------------------------------------------------------
void VHPcam::update() {
    vidGrabber.update();
    player.update();
    
	if (vidGrabber.isFrameNew()){
        
        if (player.isPlaying()) {
            videoTexture.loadData(player.getPixels(), camWidth, camHeight, GL_RGB);
        } else {
            videoTexture.loadData(vidGrabber.getPixels(), camWidth, camHeight, GL_RGB);
        }
        
        // Cam
        camFbo.begin();
        videoTexture.draw(0, 0, camWidth, camHeight);
        camFbo.end();
        
        if(recording){
            camFbo.readToPixels(camPix);
            camRecorder.addFrame(camPix);
        }
        
    }
}

//----------------------------------------------------------------

void VHPcam::draw() {
    camFbo.draw(0,0);
}

//----------------------------------------------------------------

void VHPcam::save(int _s) {
    if (_s == 0) {
        if(recording) {
            camRecorder.close();
            newRecording = fileBeingRecorded;
            recording = false;
        }
    } else if (_s == 1){
        if(!recording) {
            camRecorder.setup("saved/clip_"+ ofToString(recordingNum) +".mov", camWidth, camHeight, 15);
            fileBeingRecorded = "saved/clip_"+ ofToString(recordingNum) +".mov";
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
