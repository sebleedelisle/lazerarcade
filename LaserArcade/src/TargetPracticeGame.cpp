//
//  TargetPracticeGame.cpp
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 20/02/2014.
//
//

#include "TargetPracticeGame.h"


void TargetPracticeGame::setup(ofRectangle rect, LaserManager * lm) {
	
	
	BaseGame:: setup(rect, lm);

	shotsPerGame = 6;
	
	name = "Target Practice"; 
	
	targetRadiuses.push_back(20);
	targetScores.push_back(50);
	targetColours.push_back(ofColor::white);
	targetRadiuses.push_back(100);
	targetScores.push_back(10);
	targetColours.push_back(ofColor::red);
	targetRadiuses.push_back(200);
	targetScores.push_back(5);
	targetColours.push_back(ofColor::cyan);
	
	bullseyeSound.loadSound("../../../Sounds/ufo_lowpitch.wav"); 
}

void TargetPracticeGame::update(vector<ofVec2f> hits) {
	BaseGame::update(hits);
	
	
}

bool TargetPracticeGame::draw() {


	if(!BaseGame::draw()) return false;
	
	
	LaserManager& lm = *laserManager;
	
	
	
	
	//if(state ==STATE_PLAYING) {
		
		for(int i =0; i<targetRadiuses.size(); i++) {
			lm.addLaserCircle(centre, targetColours[i], targetRadiuses[i]);
		}
	//}
	
	
	if(state == STATE_PLAYING) {
		
	
		
		if((lastScore !=0) && (timeSinceLastShot<1)) {
			ofVec2f textPos = previousShots[previousShots.size()-1];
			float textSize = (1-timeSinceLastShot) *6;
			ofVec2f textpos = centre;
			textpos.y -= 50;

			textPos.y -= textSize*4;
			lm.addLaserText(ofToString(lastScore), textPos,textSize ,white, true);
		}
		
		
	}
	
	return true; 
}



void TargetPracticeGame::registerHit(ofVec2f pos){
	
	BaseGame:: registerHit(pos);
	lastScore = 0;
	if(previousShots.size()<=shotsPerGame) {
		for(int i = 0; i<targetRadiuses.size(); i++) {
			
			if(pos.distance(centre) < targetRadiuses[i]) {
				score += targetScores[i];
				lastScore = targetScores[i];
				if(i==0) bullseyeSound.play();
				
				break;
			}
			
		}
	}
}