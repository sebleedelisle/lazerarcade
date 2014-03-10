//
//  BaseGame.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 17/02/2014.
//
//

#pragma once 

#include "ofMain.h"
#include "LaserManager.h"
#include "Cubic.h"

class BaseGame {


	public : 
	virtual void setup(ofRectangle rect, LaserManager* lm);
	virtual void update(vector<ofVec2f> hits);
	virtual bool draw();
	
	virtual void startGame();
	virtual void toggleState(); 

	virtual void registerHit(ofVec2f pos);
	
	virtual void changeState(int newstate);
	
	virtual void showHitAnimations();

	LaserManager* laserManager = NULL;
	
	//int width, height;
	ofVec2f centre;
	ofRectangle gameRect;
	
	
	int shotsPerGame;
	int shotsRemaining; 

	
	int STATE_WAITING = 0;
	int STATE_COUNTDOWN = 1;
	int STATE_PLAYING = 2;
	int STATE_GAMEOVER = 3;
	int state = STATE_WAITING;
	float timeSinceStateChange = 0;
	
	int score;
	int lastScore; // used to display the last target score. 
	
	
	deque<ofVec2f> previousShots;
	deque<float> previousShotTimes;
	float timeSinceLastShot;
	
	ofColor red = ofColor::red;
	ofColor white = ofColor::white;
	ofColor yellow = ofColor::yellow;
	ofColor cyan = ofColor::cyan;
	ofColor blue = ofColor::blue;
	ofColor magenta = ofColor::magenta;
	ofColor green = ofColor::green;
	
	
	string name;
	
	ofSoundPlayer pew; 
	
	
};