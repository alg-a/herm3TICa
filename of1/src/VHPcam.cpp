#include "VHPcam.h"

//constructor

//----------------------------------------------------------------	
VHPcam::VHPcam() {
    
}

// methods

//----------------------------------------------------------------
void VHPcam::setup(int _w, int _h, int _d, int _f) {
    
    camWidth 		= _w;	// try to grab at this size.
	camHeight 		= _h;
	totalPixels     = camWidth * camHeight * 3;
    
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
    
    vidGrabber.setDeviceID(_d);
	vidGrabber.setDesiredFrameRate(_f);
	vidGrabber.initGrabber(camWidth,camHeight);
    videoTexture.allocate(camWidth, camHeight, GL_RGB);
    
}

//----------------------------------------------------------------
void VHPcam::update() {
    vidGrabber.update();
	if (vidGrabber.isFrameNew()){
        unsigned char * pixels = vidGrabber.getPixels();
        for (int i=0; i<totalPixels; i++) {
            int x = i % (camWidth * 3);
            int y = (i - x) / (camWidth * 3);
            // do something with pixels[i]  ...
        }
        videoTexture.loadData(pixels, camWidth, camHeight, GL_RGB);
    }
}

//----------------------------------------------------------------
void VHPcam::draw() {
    videoTexture.draw(0, 0, camWidth, camHeight);
}

//----------------------------------------------------------------
