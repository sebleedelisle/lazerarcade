//
//  DuckGame.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 21/02/2014.
//
//
#pragma once 
#include "BaseGame.h"
#include "Duck.h"

class DuckGame : public BaseGame {




	public : 


	void setup(ofRectangle rect, LaserManager * lm);
	
	void startGame();
	
	
	//void update(vector<ofVec2f> hits);
	bool draw();
	
	void registerHit(ofVec2f pos);


	vector <Duck> ducks; 




};