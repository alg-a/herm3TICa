#include "VHPcam.h"

//constructor

//----------------------------------------------------------------	
VHPcam::VHPcam() {
    
}

// methods

//----------------------------------------------------------------
void VHPcam::setup(int _w, int _h, int _d, int _f, string _ffmpeg) {
    
    // video setup
    width 		= _w;	// try to grab at this size.
	height 		= _h;
    
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = grabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
    cout << "DeviceID: " << _d << " FrameRate: " << _f << " width: " << width << " height: " << height  << endl;
    grabber.setVerbose(true);
    grabber.setDeviceID(_d);
	//vidGrabber.setDesiredFrameRate(_f);
    
    // Video devices
    for(int i = 0; i < videoDevices.size(); i++){
        cout << videoDevices[i] << endl;
    }
    
    // init grabber
    grabber.initGrabber(width,height);
    
    // allocate the frame buffer object
    fbo.allocate(width, height, GL_RGB, 0);
    
    // allocate textures
    texture.allocate(width, height, GL_RGB);
    
    //recorder
    recorder.setFfmpegLocation(_ffmpeg);
    
    // recording variables
    recordingNum = 0;
    newRecording = "";
    fileBeingRecorded = "";
    recording = false;
    playing = false;
}

//----------------------------------------------------------------
void VHPcam::update() {
    grabber.update();
    player.update();
    
	if (grabber.isFrameNew()){
        
        if (player.isPlaying()) {
            texture.loadData(player.getPixels(), width, height, GL_RGB);
        } else {
            texture.loadData(grabber.getPixels(), width, height, GL_RGB);
        }
        
        // Cam
        fbo.begin();
        texture.draw(0, 0, width, height);
        fbo.end();
        
        if(recording){
            fbo.readToPixels(pix);
            recorder.addFrame(pix);
        }
        
    }
}

//----------------------------------------------------------------

void VHPcam::draw() {
    fbo.draw(0,0);
}

//----------------------------------------------------------------

void VHPcam::save(int _s) {
    if (_s == 0) {
        if(recording) {
            recorder.close();
            newRecording = fileBeingRecorded;
            recording = false;
        }
    } else if (_s == 1){
        if(!recording) {
            recorder.setup("saved/clip_"+ ofToString(recordingNum) +".mov", width, height, 15);
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
