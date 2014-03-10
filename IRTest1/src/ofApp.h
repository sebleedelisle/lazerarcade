#pragma once

#include "ofMain.h"
#include "CameraManager.h"


class ofApp : public ofBaseApp{
	public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);


	CameraManager cameraManager; 

};
