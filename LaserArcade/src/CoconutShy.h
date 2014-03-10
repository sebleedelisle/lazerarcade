//
//  CoconutShy.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 21/02/2014.
//
//
#pragma once

#include "BaseGame.h"
#include "Coconut.h"

class CoconutShy : public BaseGame {

	public :
	
	
	void setup(ofRectangle rect, LaserManager * lm);
	//void update(vector<ofVec2f> hits);
	bool draw();
	void startGame();
	
	
	void registerHit(ofVec2f pos);
	
	vector <Coconut> coconuts;
	
	
};