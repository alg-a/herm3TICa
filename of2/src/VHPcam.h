#ifndef VHP_CAM
#define VHP_CAM

#include "ofMain.h"
#include "VHPcontrast.h"
#include "ofxVideoRecorder.h"
#include "ofxOpenCv.h"
#include "VHPgrid.h"

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
        ofxVideoRecorder        recorder;
        int                     recordingNum;
        int                     playingNum;
        string                  newRecording;
        string                  fileBeingRecorded;
        bool                    recording;
        bool                    playing;
    
        // video
        ofTexture               videoTexture;
        ofTexture               playerTexture;
        ofTexture               recorderTexture;
        ofTexture               greyTexture;
        ofTexture               stelaTexture;
        ofTexture               background; // sustraccion de fondo
        ofTexture               adjTexture;
    
        ofFbo                   recorderFbo;
        ofPixels                recorderPix;
        ofFbo                   stelaFbo;
        ofPixels                stelaPix;
        ofFbo                   adjFbo;
        ofPixels                adjPix;
        ofFbo                   greyFbo;
        ofPixels                greyPix;
        ofFbo                   sustractFbo;
        ofPixels                sustractPix;
        ofFbo                   maskFbo;
        ofPixels                maskPix;
        ofFbo                   contrastFbo;
        ofPixels                contrastPix;
        ofFbo                   gridFbo;
        ofPixels                gridPix;
    
        // sierpinskiFbo
        ofFbo                   Fbo[6];
        ofPixels                Pix[6];
        ofTexture               Texture[6];
        int                     w[6];
        int                     h[6];
        
        int                     camWidth;
        int                     camHeight;
        int                     totalPixels;
    
        // contraste
        VHPcontrast             contrast;
        int                     e[4];
        int                     f[4];
    
        // ofxCv
        ofxCvGrayscaleImage 	greyImage;
        ofxCvColorImage			colorImage;
        ofxCvContourFinder      contourFinder;
    
        // mezcla
        float                   percent[2];
        
        // shaders
        ofShader                greyShader;
        ofShader                sustractShader;
        ofShader                maskShader;
        ofShader                adjShader;
        ofShader                shaderBlurX;
        ofShader                shaderBlurY;
        ofShader                stelaShader;
        ofShader                contrastShader;
        ofShader                sierpinskiShader;
    
        ofFbo fboBlurOnePass;
        ofFbo fboBlurTwoPass;
    
        int x;
        float blur;
        float min;
        float max;
        VHPgrid grid;
        bool sendGrid;
    
        // display
        int mode;
        int vidBackground; // 0 color, 1 stela, 2 player
        ofColor maskColor;
    
        // methods
        void setup(int _w, int _h, int _d, int _f, string _ffmpeg, int _n);
        void settings(int _stela, int _mixture, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3);
        void update();
        void draw();
        void setContrast(int _n, float _e, float _f);
        bool load(int _n);
        void play(int _p, int _n);
    
        void save(int _s);
        string getNewRecording();
        void emptyNewRecording();
        void updateBkg();
    
    private:
	
};
//--------------------------------------------------------

#endif 