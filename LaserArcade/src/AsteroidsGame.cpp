//
//  AsteroidsGame.cpp
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 20/02/2014.
//
//

#include "AsteroidsGame.h"

void AsteroidsGame::setup(ofRectangle rect, LaserManager * lm){
	BaseGame::setup(rect, lm);
	
	name = "Laseroids";
	
	shotsPerGame = 6;
	
	explosion.loadSound("../../../Sounds/RetroExplosion.1.aif"); 
}

void AsteroidsGame::startGame() {
	BaseGame :: startGame();
	resetAsteroids();
}


void AsteroidsGame::update(vector<ofVec2f> hits){
	BaseGame::update(hits);
	for (int i = 0; i<asteroids.size(); i++) {
		asteroids[i].update(gameRect);
		
	}
	
	if(asteroids.size()==0) {
		score+=100; 
		resetAsteroids();
		
	}
	
}

bool AsteroidsGame::draw(){
	if(!BaseGame::draw()) return false;
	
	for (int i = 0; i<asteroids.size(); i++) {
		asteroids[i].draw(*laserManager);
		
	}
	
	return true; 
	
}

void AsteroidsGame::registerHit(ofVec2f pos){
	BaseGame::registerHit(pos);
	
	if((state != STATE_PLAYING) || (shotsRemaining <= 0)) return;
	
	for(int i = 0; i<asteroids.size(); i++) {
		Asteroid & asteroid = asteroids[i];
		if(asteroid.pos.distance(pos) < asteroid.radius) {
			// HIT!
			
			explosion.play(); 
			score += asteroid.score;
			
			if(asteroid.score>=20)  {
				asteroids.erase(asteroids.begin()+i);
				
				
			} else {
				
				asteroid.halve();
				
				
				asteroids.push_back(asteroid);
				Asteroid &newasteroid = asteroids[asteroids.size()-1];
				newasteroid.setRadius(asteroid.radius);
				newasteroid.vel.rotate(ofRandom(0,160));
				asteroid.vel.rotate(ofRandom(0,-160));
			}
			break;
		}
		
		
	}
	
}

void AsteroidsGame::resetAsteroids(){
	asteroids.erase(asteroids.begin(), asteroids.end());

	for(int i = 0; i<3 ; i++) {
		asteroids.push_back(Asteroid()); 
		Asteroid & asteroid = asteroids[asteroids.size()-1] ;
		asteroid.setPos(centre - ofVec2f(100,0));
		asteroid.setVel(ofVec2f(1,0.1));
		if(i==1) {
			asteroid.vel = -asteroid.vel;
			asteroid.pos.x = centre.x + 100;
		}else if(i==2) {
			asteroid.vel.y = -asteroid.vel.x;
			asteroid.pos = centre;
		}
		asteroid.setRadius(100);
		for(int j = 0; j<300; j++) asteroid.pos-=asteroid.vel;
	}
	
	
}
