#ifndef VHP_CAM
#define VHP_CAM

#include "ofMain.h"
#include "ofxOsc.h"
#include "VHPcontrast.h"
#include "ofxVideoRecorder.h"
#include "ofxOpenCv.h"
#include "VHPgrid.h"
#include "VHPsierpinski.h"


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
        ofVideoPlayer           bkgPlayer;
    
        // Devices
        vector<string>          videoDevices;
        vector<string>          audioDevices;
    
        // Recording
        ofxVideoRecorder        recorder;
        int                     recordingNum;
        int                     playingNum;
        int                     BkgNum;
        int                     playingBkgNum;
        string                  newRecording;
        string                  fileBeingRecorded;
        bool                    recording;
        bool                    playing;
        bool                    playingBkg;
        bool                    invert;
        bool                    streaming;
    
        // video
        ofTexture               videoTexture;
        ofTexture               playerTexture;
        ofTexture               recorderTexture;
        ofTexture               contrastTexture;
        ofTexture               greyTexture;
        ofTexture               stelaTexture;
        ofTexture               background; // sustraccion de fondo
        ofTexture               adjTexture;
    
        ofFbo                   invertFbo;
        ofPixels                invertPix;
        ofFbo                   recorderFbo;
        ofPixels                recorderPix;
        ofFbo                   stelaFbo;
        ofPixels                stelaPix;
        ofFbo                   adjFbo;
        ofPixels                adjPix;
        ofFbo                   extraFbo;
        ofPixels                extraPix;
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
        float                     th[6];
    
        // sierpinskiDataFbo
        ofFbo                   sierpinskiFbo[6];
        ofPixels                sierpinskiPix[6];
        ofTexture               sierpinskiTexture[6];
        int                     doAlpha;
        float                   sierpinskiMixture;
    
        int                     camWidth;
        int                     camHeight;
        int                     totalPixels;
    
        // contraste
        VHPcontrast             contrast;
        int                     e[6];
        int                     f[6];
    
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
        ofShader                alphaShader;
        ofShader                holeShader;

    
        ofFbo fboBlurOnePass;
        ofFbo fboBlurTwoPass;
    
        int x;
        float blur;
        float min;
        float max;
        VHPgrid grid;
        VHPsierpinski sierpinski;
    
        // display
        int mode; // 0 interface, 1 sierpinski mago, 2 mascara + grid, 3 sierpinski advanced
        int vidBackground; // 0 color, 1 stela, 2 player
        ofColor maskColor;
    
        // methods
        void setup(int _w, int _h, int _d, int _f, string _ffmpeg, int _n, int _nb);
        void settings(int _stela, int _mixture, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3, float _b, float _rb, float _rw);
    
        void update(ofxOscSender & _sender);
        void invertVideo();
        void adjustVideo();
        void findBlobs();
        void mask();
    
        void sierpinskiData(ofxOscSender & _sender);
        void gridStyle(ofxOscSender & _sender);
        void sierpinskiStyle();
        void holes();
    
        void draw();
        void drawInterface();
        void drawSierpinskiData();
        void drawGrid();
        void drawSierpinskiStyle();
        void drawHoles();
    
        void setContrast(int _n, float _e, float _f);
        void setMode(int _m);
    
        bool load(int _n);
        bool loadBkg(int _n);
        void play(int _p, int _n);
        void playBkg(int _p, int _n);
    
        void save(int _s);
        string getNewRecording();
        void emptyNewRecording();
        void updateBkg();
    
        
    
    
    private:
	
};
//--------------------------------------------------------

#endif 