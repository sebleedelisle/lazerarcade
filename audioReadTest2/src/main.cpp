#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"
//========================================================================
int main( ){

	//ofSetupOpenGL(1536,1024, OF_FULLSCREEN);			// <-------- setup the GL context
	
	ofAppGLFWWindow* window = new ofAppGLFWWindow();
    window->setMultiDisplayFullscreen(true);
	
	ofSetupOpenGL(window,1280,1024, OF_WINDOW);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
