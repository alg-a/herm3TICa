#include "ofMain.h"
#include "ofApp.h"

#define HOST "localhost"
#define PORT 8000

//========================================================================
int main( ){
	ofSetupOpenGL(285,193,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
