//
//  MultilatSpring.h
//  sebAlgoSpring2
//
//  Created by Seb Lee-Delisle on 10/02/2014.
//
//

#pragma once
#include "ofMain.h"

class MultilatSpring {



	public :
	
	
	void setup();
	void addMic(float x, float y);
	void setMicPosition(int index, ofVec2f& pos);
	void setMicPosition(int index, float x, float y);
	void update();
	void draw();
	void setTDOA(int index, float distance);
	void reset();
	
	void simulateHit(float x, float y);

	
	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);
	void mouseDragged(int x, int y);
	
	ofVec2f offsetClick;
	int currentDragMic; 
	
	
	vector<ofVec2f> mics;
	vector<float> tdoas;
	ofVec2f calculatedPoint;
	ofVec2f calcPointVel;
	ofVec2f centrePoint;
	
	int framesUntilSettled;
	bool settled;






};