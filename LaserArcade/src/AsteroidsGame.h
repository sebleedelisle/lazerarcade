//
//  AsteroidsGame.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 20/02/2014.
//
//
#pragma once 

#include "BaseGame.h"
#include "Asteroid.h"

class AsteroidsGame : public BaseGame {


	public:
	
	void setup(ofRectangle rect, LaserManager * lm);
	
	void startGame();
	

	void update(vector<ofVec2f> hits);
	bool draw();
	
	void registerHit(ofVec2f pos);
	
	void resetAsteroids(); 

	
	vector <Asteroid> asteroids;
	
	ofSoundPlayer explosion; 
	
	
};