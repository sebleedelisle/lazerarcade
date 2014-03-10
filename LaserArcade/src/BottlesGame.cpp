//
//  BottlesGame.cpp
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 21/02/2014.
//
//

#include "BottlesGame.h"



void BottlesGame :: setup(ofRectangle rect, LaserManager * lm) {
	
	
	BaseGame:: setup(rect, lm);
	
	shotsPerGame = 6;
	
	name = "Green Bottles";
	
	for (int i = 0; i<6; i++) {
		bottles.push_back(Bottle());
		Bottle & bottle = bottles[i];
		
		bottle.pos.set(ofMap(i,0,5,gameRect.getLeft() + gameRect.getWidth() * 0.2, gameRect.getRight() - gameRect.getWidth() * 0.2), gameRect.getTop() +  gameRect.getHeight()*0.4);
		
	}
	
	
}

void BottlesGame::startGame() {
	BaseGame::startGame();
	for (int i = 0; i<bottles.size(); i++) {
		Bottle & bottle = bottles[i];
		
		bottle.pos.set(ofMap(i,0,5,gameRect.getLeft() + gameRect.getWidth() * 0.2, gameRect.getRight() - gameRect.getWidth() * 0.2), gameRect.getTop() +  gameRect.getHeight()*0.4);
		bottle.enabled = true;
	}
	
}

bool BottlesGame::draw() {
	
	
	if(!BaseGame::draw()) return false;
	
	
	LaserManager& lm = *laserManager;
	
	
	
	
	//if(state ==STATE_PLAYING) {
	
	for(int i =0; i<bottles.size(); i++) {
		bottles[i].draw(lm);
	}
	//}
	
	
	
	return true;
}


void BottlesGame::registerHit(ofVec2f pos){
	
	BaseGame:: registerHit(pos);
	lastScore = 0;
	
	if(state != STATE_PLAYING) return;
	if(previousShots.size()<=shotsPerGame) {
		for(int i = 0; i<bottles.size(); i++) {
			
			if(bottles[i].checkHit(pos)) {
				score +=10;
				if(score > 30) score+=10; 
				//lastScore = targetScores[i];
				bottles[i].enabled = false;
				
				// MAKE PARTICLES!
				break;
			}
			
		}
	}
}