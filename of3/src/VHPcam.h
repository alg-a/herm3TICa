#ifndef VHP_CAM
#define VHP_CAM

#include "ofMain.h"
#include "VHPcontrast.h"
#include "ofxVideoRecorder.h"
#include "VHPhierofante.h"

//--------------------------------------------------------
class VHPcam {
    public:
    
        //constructor
        VHPcam();
    
        // variables
    
        // Cam
        ofVideoGrabber          vidGrabber;
        bool                    camRecording;
    
        // Player
        ofVideoPlayer           player;
        bool                    playing;
        int                     playingNum;
    
        // Devices
        vector<string>          videoDevices;
        vector<string>          audioDevices;
    
        // Recording
        ofxVideoRecorder        vidRecorder;
        bool                    recording;
        bool                    invert;
        int                     recordingNum;
        string                  newRecording;
        string                  fileBeingRecorded;
    
        // fbo & textures
        ofTexture               vidTexture;
        ofFbo                   camFbo;
        ofPixels                camPix;
        ofFbo                   invertFbo;
        ofPixels                invertPix;
        ofFbo                   scaleFbo;
        ofPixels                scalePix;
        ofFbo                   stelaFbo;
        ofPixels                stelaPix;
        ofTexture               stelaTexture;
        ofFbo                   of2Fbo;
        ofPixels                of2Pix;
        ofTexture               of2Texture;
        ofFbo                   drawFbo;
        ofPixels                drawPix;
        ofTexture               drawTexture;
    
        ofVec3f                 automata;
    
        bool                    show;
        bool                    showPlayer;
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
    
        // images
        vector<ofImage>         tarot;
        int                     ntarot;
    
        // hierofante
        VHPhierofante           hierofante;
    
        // display
        int mode; // 0 narrative, 1 oscFace
    
        // methods
        void setup(int _w, int _h, int _d, int _f, string _ffmpeg);
        void settings(int _stela, int _mixture, int _show, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3);
        void update();
        void stela();
        void draw(int _x, int _y, int _width, int _height);
        void drawInFbo();
        void setContrast(int _n, float _e, float _f);
        void setMode(int _m);
        bool load(int _n);
        void play(int _p, int _n);
    
        void save(int _s);
        string getNewRecording();
        void emptyNewRecording();
        void loadImage(string _image);
        void setAutomata(int _x, int _y);
        void checkAutomata();
    
    private:
	
};
//--------------------------------------------------------

#endif 