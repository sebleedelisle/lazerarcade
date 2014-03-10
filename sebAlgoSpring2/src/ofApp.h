#pragma once

#include "ofMain.h"
#include "MultiLatSpring.h"

class ofApp : public ofBaseApp{
	public:
	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);

	MultiLatSpring solver; 
	ofVec2f mouseClickPoint;

	
};
