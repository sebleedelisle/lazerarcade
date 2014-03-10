//
//  BaseGame.cpp
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 17/02/2014.
//
//

#include "BaseGame.h"

void BaseGame :: setup(ofRectangle rect, LaserManager * lm) {
	
	laserManager = lm;

	gameRect = rect; 
	
	centre = rect.getCenter();
	name = "";
	
	shotsPerGame = 6;
	
	pew.loadSound("../../../Sounds/RetroLaunch.1.wav");
	pew.setSpeed(0.7);

}

void BaseGame :: update(vector<ofVec2f> hits) {
	
	timeSinceStateChange+=ofGetLastFrameTime();
	
	timeSinceLastShot = 0;
	
	if(previousShots.size()>0) {
		timeSinceLastShot = ofGetElapsedTimef() - previousShotTimes[previousShotTimes.size()-1];
	}
	
	for(int i = 0; i<hits.size(); i++) {
		registerHit(hits[i]); 
	}
	
	
	
	if((state == STATE_COUNTDOWN) && (timeSinceStateChange>3)) {
		changeState(STATE_PLAYING); 
	}
	
	if(state == STATE_PLAYING) {
		if(shotsRemaining<=0) {
			shotsRemaining = 0;
			if(timeSinceLastShot>1) changeState(STATE_GAMEOVER);
		}

	}
	
		

	
}

bool BaseGame :: draw() {
	if(laserManager==NULL) return false;
	
	LaserManager& lm = *laserManager;
	
	
	showHitAnimations();
	
	if(state == STATE_WAITING) {
		
		lm.addLaserText(ofToUpper(name), centre * ofVec2f(1,0.6), 10,cyan, true);
		
	}

	ofVec2f textpos = centre * ofVec2f(1,0.6);
	//textpos.y -= 50;

	if(state == STATE_COUNTDOWN) {
		
		int time = 1+(3-timeSinceStateChange);
		lm.addLaserText(ofToString(time), textpos, 10,white, true);
		
	}

	if(state == STATE_PLAYING) {
		if(timeSinceStateChange < 0.5) {
			//float progress = timeSinceStateChange/3;
			ofVec3f pos = textpos;
			
			//pos.z = 0;//progress * 5000;
			
			lm.addLaserText("GO", pos, 10,white, true);
			
		}
		lm.addLaserText(ofToString(shotsRemaining), centre * ofVec2f(0.5,0.5), 6,red, true);
		
	}
	
	
	if(state == STATE_GAMEOVER) {
		
		if(timeSinceStateChange > 5) {
			
			changeState(STATE_WAITING);
			
		} else {
			
			lm.addLaserText("GAME OVER", centre * ofVec2f(1,0.6), 10,cyan, true);
			lm.addLaserText("SCORE : " + ofToString(score), centre * ofVec2f(1,1), 10,red, true);
			
		}
		
		
	}
	return true; 
}

void BaseGame::registerHit(ofVec2f pos){
	
	
	previousShots.push_back(pos);
	previousShotTimes.push_back(ofGetElapsedTimef());
	
	if(previousShots.size()>10) {
		previousShots.pop_front();
		previousShotTimes.pop_front();		
	}
	
	pew.play();
	
	if(state == STATE_PLAYING) shotsRemaining --; 
	
	
	
}


void BaseGame::changeState(int newstate) {

	state = newstate;
	timeSinceStateChange = 0; 


}

void BaseGame::startGame() {

	changeState(STATE_COUNTDOWN);
	previousShots.erase(previousShots.begin(), previousShots.end());
	previousShotTimes.erase(previousShotTimes.begin(), previousShotTimes.end());
	
	score = 0; 
	lastScore = 0;
	
	shotsRemaining = shotsPerGame;
}

void BaseGame::showHitAnimations() {
	
	LaserManager &lm = *laserManager;
	for(int i = 0; i<previousShots.size(); i++) {
		
		//lm.addLaserDot(previousShots[i], ofColor::white);
		
		float timeSinceShot = ofGetElapsedTimef() - previousShotTimes[i];
		
		float shotAnimateTime = 0.7;
		ofVec2f shotAnimatePath = ofVec2f(200,200);
		float progress = Cubic::easeOut(ofMap(timeSinceShot, 0,shotAnimateTime, 0, 1),0,1,1);
		
		if(progress < 1) {
			lm.addLaserDot(previousShots[i] + shotAnimatePath * progress, ofFloatColor(1,1,1), 1-progress);
			lm.addLaserDot(previousShots[i] + shotAnimatePath * ofVec2f(1,-1) * progress, ofFloatColor(1,1,1), 1-progress);
			lm.addLaserDot(previousShots[i] + shotAnimatePath * ofVec2f(-1,-1) * progress, ofFloatColor(1,1,1), 1-progress);
			lm.addLaserDot(previousShots[i] + shotAnimatePath * ofVec2f(-1,1) * progress, ofFloatColor(1,1,1), 1-progress);
		}
		
	}


}

void BaseGame::toggleState() {
	
	if(state==STATE_PLAYING) changeState(STATE_GAMEOVER);
	else startGame(); 


}