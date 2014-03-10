//
//  Bottle.h
//  LaserArcade
//
//  Created by Seb Lee-Delisle on 21/02/2014.


#pragma once

#include "ofMain.h"
#include "LaserManager.h"
#include "ofxSvg.h"

class Bottle {
	
public:
	Bottle() {
		
		pos.set(0,0);
		enabled = true;
		rotation = 0;
		width = 50;
		height = 100;
		
		bottleSVG.load("bottle.svg"); 
		
	}
	
	void draw(LaserManager & lm ) {
		if(!enabled) return; 
		ofColor white = ofColor :: white;
		ofColor yellow = ofColor :: yellow;
		ofColor green = ofColor :: green;
		
		
		//lm.addLaserRectEased(pos, ofVec2f(width, height), ofColor::red);
		
		
		ofxSVG & svg = bottleSVG; 
		ofVec3f centrePoint = ofVec3f(svg.getWidth()/2, svg.getHeight()/2);
		float scale = 1.2;
		
		
		for(int i=0; i<svg.getNumPath(); i++ ) {
			
			vector<ofPolyline>& lines = svg.getPathAt(i).getOutline();
			for(int j=0; j<lines.size(); j++) {
				ofPolyline line = lines[j];
				vector<ofVec3f>& vertices = line.getVertices();
				for(int i = 0; i<vertices.size(); i++) {
					ofVec3f& v = vertices[i];
					v-=centrePoint;
					v*=scale;
					v.x+=width/2;
					v.y+=height/2;
					
					//v.x+=APP_WIDTH/2;
					//v.y +=APP_HEIGHT*0.3;
					v+=pos;
					//line.
					
				}
				//cout << "brightness : " << brightness << endl;
				lm.addLaserPolyline(line,new ColourSystem(ofColor::green),1);
			}
		}
		
	};
	
	bool checkHit(ofVec2f hitPos) {
		ofRectangle rect(pos.x, pos.y, width, height);
		return rect.inside(hitPos);
		
	};
	
	ofVec2f pos;
	bool enabled;
	float rotation;
	float width, height;
	ofxSVG bottleSVG; 
	
	
	
};