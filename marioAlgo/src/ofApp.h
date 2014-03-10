#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);

	
	vector<ofVec2f> mics;
	vector<float> tdoas; 
	ofVec2f mouseClickPoint;
	ofVec2f calculatedPoint;
	
	
};
