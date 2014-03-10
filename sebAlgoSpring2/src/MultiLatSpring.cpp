//
//  MultiLatSpring.cpp
//  sebAlgoSpring2
//
//  Created by Seb Lee-Delisle on 10/02/2014.
//
//

#include "MultiLatSpring.h"
//--------------------------------------------------------------
void MultiLatSpring::setup(){
	
	
	// four mics
	//	mics.push_back(ofVec2f(100,100));
	//	mics.push_back(ofVec2f(700,100));
	//	mics.push_back(ofVec2f(700,500));
	//	mics.push_back(ofVec2f(100,500));
	
	
	
	// three mics
	//	mics.push_back(ofVec2f(100,100));
	//	mics.push_back(ofVec2f(700,100));
	//	mics.push_back(ofVec2f(400,500));
	
	
	// six mics
	
	mics.push_back(ofVec2f(100,100));
	mics.push_back(ofVec2f(400,100));
	mics.push_back(ofVec2f(700,100));
	mics.push_back(ofVec2f(700,500));
	mics.push_back(ofVec2f(400,500));
	mics.push_back(ofVec2f(100,500));
	
	//tdoaPoints = mics;
	//velocities = mics;
	
	tdoas.assign(mics.size(),0);
		
	calculatedPoint = ofVec2f(400,300);
	
	calcPointVel.set(0,0);
	
	
	
}

void MultiLatSpring::update(){
	
	
	if(!settled) {
		
		float averagedistance = 0;
		
		// each tdoa point needs to be attracted to the centre point, but
		// also restricted to the radius of their TDOA
		
		for(int i = 0; i<mics.size(); i++) {
			
			averagedistance += (calculatedPoint.distance(mics[i])-tdoas[i]);

		}
		
		averagedistance/=mics.size();
		
		calcPointVel*=0.3;
		
		// then each distance between the constrained TDOA points and the calculated position
		// wants to be the same - so compare to the average distance and expand / contract.
		
		for(int i = 0; i<mics.size(); i++) {
			
			float distance = mics[i].distance(calculatedPoint);
			//if(distance )
			ofVec2f target = calculatedPoint - mics[i];
			target *= (averagedistance+tdoas[i]) / (distance);
			target+=mics[i];
			
			
			ofVec2f diff = target - calculatedPoint;
			calcPointVel += diff*0.3;
			
			
			
		}
		
		if(calcPointVel.length() < 0.01) {
			settled = true;
		}
		
		calculatedPoint += calcPointVel;
		
	}
}

//--------------------------------------------------------------
void MultiLatSpring::draw(){
		
	ofNoFill();
	ofSetColor(255);
	ofRect(100,100,600,400);
	
	if(calcPointVel.length() > 0.01) {
		ofSetColor(255,0,0);
	}
	ofCircle(calculatedPoint, 10);
	
	for(int i = 0; i<mics.size(); i++) {
		
		ofSetCircleResolution(100);
		ofSetColor(70);
		
		ofCircle(mics[i], tdoas[i]);
		
		ofSetCircleResolution(10);
		ofSetColor(200);
		//ofCircle(tdoaPoints[i], 2);
		
		ofSetColor(100);
		ofLine(mics[i], calculatedPoint);
		//ofLine(tdoaPoints[i], mics[i]);
		
	}
	
	if(!settled) framesUntilSettled ++;
	
	ofDrawBitmapString(ofToString(framesUntilSettled), 10,10);
	
}

void MultiLatSpring::reset() {
	
	calculatedPoint.set(400,300);
	calcPointVel.set(0,0);
	framesUntilSettled = 0;
	settled = false;
	
}

// TODO - check index
void MultiLatSpring::setTDOA(int index, float distance) {
	tdoas[index] = distance;
}
