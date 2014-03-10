//
//  Asteroid.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 20/02/2014.
//
//
#pragma once 
#include "ofMain.h"
#include "LaserManager.h" 

class Asteroid {
	
	public :
	
	Asteroid() {
		pos.set(0,0);
		vel.set(1,0);
		vel.rotate(ofRandom(0,360));
	
	};

	void setPos(ofVec2f newpos) {
		pos = newpos;
	}
	void setPos(float x, float y) {
		setPos(ofVec2f(x, y));
	}
	
	void setVel(ofVec2f newvel) {
		vel = newvel;
	}
	
	void setRadius(float newradius) {
		radius = newradius;
		
		points.erase(points.begin(), points.end()); 
		ofVec2f temp(radius, 0);
		float angle = 0;
		int counter = 0;
		while(angle<360) {
			
			counter++;
			
			if(counter%2==0)
				temp.set(radius * ofRandom(0.6, 1),0);
			else
				temp.set(radius,0);
			
			temp.rotate(angle);
			
			points.push_back(temp);
			angle+=ofRandom(15,35);
			
			shape.addVertex(temp);
			
		}
		
	} 
	
	void update(ofRectangle rect) {
		pos+=vel;
		
		if(pos.x+radius<rect.getLeft()) pos.x = rect.getRight()+radius;
		else if(pos.x-radius>rect.getRight()) pos.x = rect.getLeft()-radius;
		if(pos.y+radius<rect.getTop()) pos.y = rect.getBottom()+radius;
		else if(pos.y-radius>rect.getBottom()) pos.y = rect.getTop()-radius;
		
		
	}
	
	void draw(LaserManager& lm) {

		shape.clear();
		
		//lm.addLaserCircle(pos, ofColor(255), radius);
		for(int i = 0; i<points.size(); i++) {
			//lm.addLaserLineEased(pos + points[i], pos+points[(i+1)%points.size()], ofColor(255));
			shape.addVertex(pos+points[i]);

		}
		shape.addVertex(pos+points[0]);
	
		
		lm.addLaserPolyline(shape); 	
	}
	
	void halve() {
		setRadius(radius/2);
		score *=2; 
		
	}
	
	
	ofVec2f pos;
	ofVec2f vel;
	int score = 5;
	
	ofPolyline shape;
	ofPolyline translatedShape; 
	
	vector <ofVec2f> points; 
	
	float radius;
	
	
};