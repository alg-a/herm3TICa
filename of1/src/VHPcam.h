#ifndef VHP_CAM
#define VHP_CAM

#include "ofMain.h"
#include "VHPcontrast.h"
#include "ofxVideoRecorder.h"

//--------------------------------------------------------
class VHPcam {
    public:
    
        //constructor
        VHPcam();
    
        // variables
    
        // Cam
        ofVideoGrabber          vidGrabber;
    
        // Player
        ofVideoPlayer           player;
    
        // Devices
        vector<string>          videoDevices;
        vector<string>          audioDevices;
    
        // Recording
        ofxVideoRecorder        camRecorder;
        ofxVideoRecorder        greyRecorder;
        int                     recordingNum;
        string                  newRecording;
        bool                    recording;
    
        // video
        ofTexture               videoTexture;
        ofTexture               playerTexture;
        ofTexture               timeBufferTexture;
    
        ofFbo                   camFbo;
        ofPixels                camPix;
        ofFbo                   playerFbo;
        ofPixels                playerPix;
        ofFbo                   stelaFbo;
        ofPixels                stelaPix;
        ofFbo                   greyFbo;
        ofPixels                greyPix;
    
        bool                    show;
        int                     camWidth;
        int                     camHeight;
        int                     totalPixels;
    
        // contraste
        VHPcontrast             contrast;
        int                     e[4];
        int                     f[4];
    
        // mezcla
        float                   percent[2];
        
        // shaders
        ofShader                stelaShader;
        ofShader                camShader;
        ofShader                greyShader;
    
        // methods
        void setup(int _w, int _h, int _d, int _f, string _ffmpeg);
        void settings(int _stela, int _mixture, int _show, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3);
        void update();
        void draw();
        void setContrast(int _n, float _e, float _f);
        void load(int _n);
    
        void save(int _s);
        string getNewRecording();
        void emptyNewRecording();
        
    private:
	
};
//--------------------------------------------------------

#endif 