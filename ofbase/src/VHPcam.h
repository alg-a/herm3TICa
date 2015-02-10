#ifndef VHP_CAM
#define VHP_CAM

#include "ofMain.h"
#include "ofxVideoRecorder.h"

//--------------------------------------------------------
class VHPcam {
    public:
    
        //constructor
        VHPcam();
    
        // variables
    
        // Cam
        ofVideoGrabber          grabber;
    
        // Player
        ofVideoPlayer           player;
        bool                    playing;
    
        // Devices
        vector<string>          videoDevices;
        vector<string>          audioDevices;
    
        // Recording
        ofxVideoRecorder        recorder;
        int                     recordingNum;
        string                  newRecording;
        string                  fileBeingRecorded;
        bool                    recording;
    
        // video
        ofTexture               texture;
    
        ofFbo                   fbo;
        ofPixels                pix;
        
        int                     width;
        int                     height;
    
        // methods
        void setup(int _w, int _h, int _d, int _f, string _ffmpeg);
    
        void update();
        void draw();
        bool load(int _n);
        void play(int _p, int _n);
    
        void save(int _s);
        string getNewRecording();
        void emptyNewRecording();
        
    private:
	
};
//--------------------------------------------------------

#endif 