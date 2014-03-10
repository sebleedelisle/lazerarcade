//
//  Coconut.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 21/02/2014.
//
//
#pragma once 

#include "ofMain.h"

class Coconut {

	public:
	Coconut() {
		
		pos.set(0,0);
		enabled = true;
		rotation = 0;
		
	}
	
	void draw(LaserManager & lm ) {
		ofColor white = ofColor :: white;
		ofColor yellow = ofColor :: yellow;
		
		if(enabled) lm.addLaserCircle(pos, yellow, 30);
		ofVec2f top = pos + ofVec2f(0,40);
		ofVec2f bottom = top + ofVec2f(0,150);
		ofVec2f left = top - ofVec2f(30,0);
		ofVec2f right = top + ofVec2f(30,0);

		lm.addLaserLineEased(top, bottom, white);
		lm.addLaserLineEased(left, right, white);
		
	}
	
	ofVec2f pos;
	bool enabled;
	float rotation; 
	

};