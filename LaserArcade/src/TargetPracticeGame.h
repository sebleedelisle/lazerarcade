//
//  TargetPracticeGame.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 20/02/2014.
//
//


#pragma once

#include "BaseGame.h"

class TargetPracticeGame : public BaseGame {

	public:
	
	void setup(ofRectangle rect, LaserManager * lm);
	void update(vector<ofVec2f> hits);
	bool draw();
	
	void registerHit(ofVec2f pos); 
	
	vector <float> targetRadiuses;
	vector <int> targetScores;
	vector <ofColor> targetColours;
	
	ofSoundPlayer bullseyeSound; 
	
		
};