//
//  CoconutShy.cpp
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 21/02/2014.
//
//

#include "CoconutShy.h"


void CoconutShy :: setup(ofRectangle rect, LaserManager * lm) {
	
	
	BaseGame:: setup(rect, lm);
	
	shotsPerGame = 6;
	
	name = "Coconut Shy";
	
	for (int i = 0; i<6; i++) {
		coconuts.push_back(Coconut()); 
		Coconut & coconut = coconuts[i];
		
		coconut.pos.set(ofMap(i,0,5,gameRect.getLeft() + gameRect.getWidth() * 0.2, gameRect.getRight() - gameRect.getWidth() * 0.2), gameRect.getTop() +  gameRect.getHeight()*0.4);
		
	}


}

void CoconutShy::startGame() {
	BaseGame::startGame();
	for (int i = 0; i<coconuts.size(); i++) {
		Coconut & coconut = coconuts[i];
		
		coconut.pos.set(ofMap(i,0,5,gameRect.getLeft() + gameRect.getWidth() * 0.2, gameRect.getRight() - gameRect.getWidth() * 0.2), gameRect.getTop() +  gameRect.getHeight()*0.4);
		coconut.enabled = true; 
	}
	
}

bool CoconutShy::draw() {
	
	
	if(!BaseGame::draw()) return false;
	
	
	LaserManager& lm = *laserManager;
	
	
	
	
	//if(state ==STATE_PLAYING) {
		
		for(int i =0; i<coconuts.size(); i++) {
			coconuts[i].draw(lm);
		}
	//}
	
	
	
	return true;
}


void CoconutShy::registerHit(ofVec2f pos){
	
	BaseGame:: registerHit(pos);
	lastScore = 0;
	
	if(state != STATE_PLAYING) return;
	if(previousShots.size()<=shotsPerGame) {
		for(int i = 0; i<coconuts.size(); i++) {
			
			if(pos.distance(coconuts[i].pos) < 30) {
				score ++;
				//lastScore = targetScores[i];
				coconuts[i].enabled = false; 
				break;
			}
			
		}
	}
}