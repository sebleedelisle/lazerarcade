//
//  DuckGame.cpp
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 21/02/2014.
//
//

#include "DuckGame.h"

void DuckGame :: setup(ofRectangle rect, LaserManager * lm) {
	
	
	BaseGame:: setup(rect, lm);
	
	shotsPerGame = 6;
	
	name = "Shooting Ducks";
	
	// set up duck objects
	
	for (int i = 0; i<6; i++) {
		ducks.push_back(Duck());
		Duck & duck = ducks[i];
		
		duck.pos.set(ofMap(i,0,5,gameRect.getLeft() + gameRect.getWidth() * 0.2, gameRect.getRight() - gameRect.getWidth() * 0.2), gameRect.getTop() +  gameRect.getHeight()*0.35);
		
	}
	
	
	
	
}

void DuckGame::startGame() {
	BaseGame::startGame();
	//reset ducks
}

bool DuckGame::draw() {
	
	
	if(!BaseGame::draw()) return false;
	
	
	LaserManager& lm = *laserManager;
	
	
	// draw ducks
	
	
	for(int i =0; i<ducks.size(); i++) {
		Duck & duck = ducks[i];
		duck.pos.x -=4;
		if(duck.pos.x < gameRect.getLeft() + gameRect.getWidth()*0.2) {
			duck.scaleX -=0.1;
			if(duck.scaleX<0) duck.scaleX = 0;
		} else if(duck.scaleX<1) duck.scaleX+=0.1;
		
		if(duck.pos.x + duck.width  *1.5 < gameRect.getLeft() + gameRect.getWidth()*0.2) {
			duck.pos.x = gameRect.getRight() - gameRect.getWidth()*0.2;
			duck.enabled = true; 
		} 
		ducks[i].draw(lm);
	}
	
	
	return true;
}


void DuckGame::registerHit(ofVec2f pos){
	
	BaseGame:: registerHit(pos);
	lastScore = 0;
	
	
	if(state != STATE_PLAYING) return;
		// check collisions
	if(previousShots.size()<=shotsPerGame) {
		for(int i = 0; i<ducks.size(); i++) {
			
			if(ducks[i].checkHit(pos)) {
				score +=10;
				if(score > 30) score+=10;
				//lastScore = targetScores[i];
				ducks[i].enabled = false;
				
				// MAKE PARTICLES!
				break;
			}
			
		}
	}
}