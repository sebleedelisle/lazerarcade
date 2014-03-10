//
//  MultiLatSpring.h
//  sebAlgoSpring2
//
//  Created by Seb Lee-Delisle on 10/02/2014.
//
//

#pragma once
#include "ofMain.h"

class MultiLatSpring {



	public :
	
	
	void setup();
	void update();
	void draw();
	void setTDOA(int index, float distance);
	void reset(); 
	
	
	vector<ofVec2f> mics;
	vector<float> tdoas;
		ofVec2f calculatedPoint;
	ofVec2f calcPointVel;
	
	int framesUntilSettled;
	bool settled;






};