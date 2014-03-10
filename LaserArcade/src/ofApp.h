#pragma once

#include "ofMain.h"
#include "LaserManager.h"
#include "SonicHitFinder.h"

class ofApp : public ofBaseApp{

	public:
	void setup();
	void update();
	void draw();
	void audioIn(float * input, int bufferSize, int numChannels);
	void keyPressed(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void gotMessage(ofMessage msg);
	void exit();
	
	int screenWidth, screenHeight;
	
	
	ofxPanel gui;
	LaserManager laserManager;
	
	SonicHitFinder hitFinder;
	
	
		
};
