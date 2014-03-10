#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	mics.push_back(ofVec2f(100,100));
	//mics.push_back(ofVec2f(400,100));
	mics.push_back(ofVec2f(700,100));
	//mics.push_back(ofVec2f(700,500));
	//mics.push_back(ofVec2f(400,500));
	//mics.push_back(ofVec2f(100,500));
	
	mics.push_back(ofVec2f(400,400));
	
	tdoaPoints = mics;
	velocities = mics;
	
	tdoas.assign(mics.size(),0);

	
	calculatedPoint = ofVec2f(400,300);
	mouseClickPoint = ofVec2f(400,300);
	calcPointVel.set(0,0);
	
	ofSetVerticalSync(true); 
	
	
}

void ofApp::update(){
	
	
	if(!settled) {
			
		float averagedistance = 0;
		
		// each tdoa point needs to be attracted to the centre point, but
		// also restricted to the radius of their TDOA
		
		for(int i = 0; i<mics.size(); i++) {
			velocities[i]*=0.5;
			velocities[i]+= (calculatedPoint - tdoaPoints[i]) *0.2;
			
			tdoaPoints[i] += velocities[i];

			if(tdoaPoints[i].distance(mics[i]) != tdoas[i]) {
				
				tdoaPoints[i] -= mics[i];
								 
				tdoaPoints[i].normalize();
				tdoaPoints[i]*=tdoas[i];
				tdoaPoints[i]+=mics[i];
				
				
			}
			
			averagedistance += calculatedPoint.distance(tdoaPoints[i]);
			
			
		}

		averagedistance/=mics.size();
		
		calcPointVel*=0.3;
		
		// then each distance between the constrained TDOA points and the calculated position
		// wants to be the same - so compare to the average distance and expand / contract.

		for(int i = 0; i<mics.size(); i++) {
			
			float distance = tdoaPoints[i].distance(calculatedPoint);
			//if(distance )
			ofVec2f target = calculatedPoint - tdoaPoints[i];
			target *= averagedistance / distance;
			target+=tdoaPoints[i];
			
					   
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
void ofApp::draw(){
	ofBackground(0);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	ofNoFill();
	ofSetColor(255);
	ofRect(100,100,600,400);
	ofCircle(mouseClickPoint, 1);
	
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
		ofCircle(tdoaPoints[i], 2);
		
		ofSetColor(100);
		ofLine(tdoaPoints[i], calculatedPoint);
		ofLine(tdoaPoints[i], mics[i]);
		
	}
	
	if(!settled) framesUntilSettled ++;

	ofDrawBitmapString(ofToString(framesUntilSettled), 10,10);
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int mousex, int mousey, int button){
	
	
	mouseClickPoint.set(mousex,mousey);
	calculatedPoint.set(400,300);
	calcPointVel.set(0,0);
	
	float closest = 20000;
	int closestindex = -1;
	
	for(int i = 0; i<mics.size(); i++) {
		
		float distance = mics[i].distance(mouseClickPoint);
		if(distance<closest) {
			closest = distance;
			closestindex = i;
		}
	}
	
	tdoas.erase(tdoas.begin(), tdoas.end());
	for(int i = 0; i<mics.size(); i++) {
		float distance = mics[i].distance(mouseClickPoint) - closest;
		
		//if((distance > 0) && (ofRandom(1)<0.5 )) distance += ofRandom(-100,100);
		
		tdoas.push_back(distance);
		//velocities[i].set(0,0);
	}
	
	framesUntilSettled = 0;
	settled = false; 
		
}
