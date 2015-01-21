#pragma once

#include "ofMain.h"

#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxHttpUtils.h"
#include "ofxJSONElement.h"
#include "VHPstreamer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void getResponse();
        void addStreamer(ofxJSONElement& _s);
    
        void newResponse(ofxHttpResponse & response);
    
        // Variables
        ofxXmlSettings XML;
        vector<string> host;
        vector<VHPstreamer> streamers;
        vector<ofxOscSender> sender;
        ofxOscReceiver receiver;
        int timer;
        bool loaded;
    
        ofxJSONElement  response;
        ofxHttpUtils updateData;
        string auth_key;
        string user_name;
        string getdata_URL;
        string update_URL;
		
};
