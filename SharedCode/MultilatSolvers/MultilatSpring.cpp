//
//  MultilatSpring.cpp
//  sebAlgoSpring2
//
//  Created by Seb Lee-Delisle on 10/02/2014.
//
//

#include "MultilatSpring.h"
//--------------------------------------------------------------
void MultilatSpring::setup(){
	
	
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
	
	//mics.push_back(ofVec2f(100,100));
	//mics.push_back(ofVec2f(400,100));
	//mics.push_back(ofVec2f(700,100));
	//mics.push_back(ofVec2f(700,500));
	//mics.push_back(ofVec2f(400,500));
	//mics.push_back(ofVec2f(100,500));

			
	calculatedPoint = ofVec2f(0,0);
	centrePoint = calculatedPoint; 
	
	calcPointVel.set(0,0);
	currentDragMic = -1; 
	
	
}

void MultilatSpring::addMic(float x, float y) {
	mics.push_back(ofVec2f(x,y));
	tdoas.push_back(0);
	micsEnabled.push_back(true); 
}


void MultilatSpring::setMicPosition(int index, float x, float y){
	ofVec2f pos(x,y);
	setMicPosition(index, pos);
}

void MultilatSpring::setMicPosition(int index, ofVec2f& pos){
	
	while(index>=mics.size()) {
		mics.push_back(pos);
		tdoas.push_back(0);
		micsEnabled.push_back(true);

	}
	
	mics[index] = pos;
	
	
	
}

void MultilatSpring::update(){
	
	int count = 0;
	while((!settled) && (count++ < 100)) {
		
		float averagedistance = 0;
		
		// each tdoa point needs to be attracted to the centre point, but
		// also restricted to the radius of their TDOA
		
		int numActiveMics = 0; 
		for(int i = 0; i<mics.size(); i++) {
			if(!micsEnabled[i]) continue; 
			averagedistance += (calculatedPoint.distance(mics[i])-tdoas[i]);
			numActiveMics++; 
		}
		
		averagedistance/=numActiveMics;
		
		calcPointVel*=0.3;
		
		// then each distance between the constrained TDOA points and the calculated position
		// wants to be the same - so compare to the average distance and expand / contract.
		
		for(int i = 0; i<mics.size(); i++) {
			
			if(!micsEnabled[i]) continue; 
			float distance = mics[i].distance(calculatedPoint);
			if(isinf(distance)) {
				cout << "BORKED" << endl;
			}
			if(distance==0 ) distance =0.0001;
			ofVec2f target = calculatedPoint - mics[i];
			if(isnan(target.x )) {
				cout << "BORKED" << endl;
			}

			target *= (averagedistance+tdoas[i]) / (distance);
			if(isnan(target.x )) {
				cout << "BORKED" << endl;
			}
			target+=mics[i];
			
			
			ofVec2f diff = target - calculatedPoint;
			calcPointVel += diff*0.3;
			
			if(isnan(calcPointVel.x )) {
				cout << "BORKED" << endl; 
			}
			
		}
		
		if(calcPointVel.length() < 0.01) {
			settled = true;
		} else if(calcPointVel.length()>100) {
			calcPointVel.normalize() *=100; 
		}
		
		calculatedPoint += calcPointVel;
		
	
	}
}

//--------------------------------------------------------------
void MultilatSpring::draw(ofColor col){
	
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	ofNoFill();
	ofSetColor(col);
	//ofRect(100,100,600,400);
	
	if(!settled) {
		ofSetColor(255,0,0);
	}
	ofCircle(calculatedPoint, 10);
	
	ofVec2f circleIntersect;
	
	for(int i = 0; i<mics.size(); i++) {
		
		if(!micsEnabled[i]) continue;
		
		ofSetCircleResolution(100);
		ofSetColor(col);
		ofSetLineWidth(3);
		ofCircle(mics[i], 30);
		
		ofSetLineWidth(1);
		ofSetColor(col/2);
		ofCircle(mics[i], tdoas[i]);
		
		ofSetLineWidth(1);
		ofSetColor(col);
		ofLine(mics[i], calculatedPoint);
		
		circleIntersect = calculatedPoint - mics[i];
		circleIntersect.normalize();
		circleIntersect *= tdoas[i];
		circleIntersect += mics[i];
		ofSetLineWidth(2);
		ofCircle(circleIntersect, 2);
		
		
	}
	
	if(!settled) framesUntilSettled ++;
	
	ofPopStyle();
	//ofDrawBitmapString(ofToString(framesUntilSettled), 10,10);
	
}

void MultilatSpring::reset() {
	
	calculatedPoint.set(0,0);
	for(int i = 0;i<mics.size(); i++) {
		calculatedPoint+=mics[i];
	}
	calculatedPoint/=mics.size();
	calcPointVel.set(0,0);
	framesUntilSettled = 0;
	settled = false;
	centrePoint = calculatedPoint;
	
}

// TODO - check index
void MultilatSpring::setTDOA(int index, float distance) {
	cout << "setTDOA " << index << " " << distance << endl; 
	tdoas[index] = distance;
}



void MultilatSpring::mousePressed(int x, int y){
	
	ofVec2f mousePos(x,y);
	for(int i = 0; i<mics.size(); i++) {
		if(mics[i].distance(mousePos)<40) {
			offsetClick =  mics[i] - mousePos;
			currentDragMic = i; 
		}
	}
	

}

void MultilatSpring :: simulateHit(float x, float y) {
	
			
		ofVec2f mouseClickPoint(x,y);
		
		
		float closest = 20000;
		int closestindex = -1;
		
		//vector<ofVec2f> & mics = solver.mics;
		
		for(int i = 0; i<mics.size(); i++) {
			
			if(!micsEnabled[i]) continue;
			
			float distance = mics[i].distance(mouseClickPoint);
			if(distance<closest) {
				closest = distance;
				closestindex = i;
			}
		}
		
		
		for(int i = 0; i<mics.size(); i++) {
			float distance = mics[i].distance(mouseClickPoint) - closest;
			
			//add error margin
			//if((distance > 0) && (ofRandom(1)<0.5 )) distance += ofRandom(-50,50);
			
			//		tdoas.push_back(distance);
			setTDOA(i, distance);
		}
		
		reset();
		
	
	
	
	
}

void MultilatSpring::mouseReleased(int x, int y){
	currentDragMic = -1;
}
void MultilatSpring::mouseDragged(int x, int y){
	ofVec2f mousePos(x,y);

	if(currentDragMic!=-1) {
		mics[currentDragMic] = mousePos + offsetClick;
		
	}
}

