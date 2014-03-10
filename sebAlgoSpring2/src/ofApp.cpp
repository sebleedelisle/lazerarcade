#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	
	ofSetVerticalSync(true);
	solver.setup();
	mouseClickPoint = ofVec2f(400,300);
	
}

void ofApp::update(){
	solver.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	solver.draw();
	ofCircle(mouseClickPoint, 1);
	
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int mousex, int mousey, int button){
	
	
	mouseClickPoint.set(mousex,mousey);

	
	float closest = 20000;
	int closestindex = -1;
	
	vector<ofVec2f> & mics = solver.mics;
	
	for(int i = 0; i<mics.size(); i++) {
		
		float distance = mics[i].distance(mouseClickPoint);
		if(distance<closest) {
			closest = distance;
			closestindex = i;
		}
	}
	

	for(int i = 0; i<mics.size(); i++) {
		float distance = mics[i].distance(mouseClickPoint) - closest;
		
		//add error margin
		if((distance > 0) && (ofRandom(1)<0.5 )) distance += ofRandom(-50,50);
		
//		tdoas.push_back(distance);
		solver.setTDOA(i, distance);
	}
	
	solver.reset(); 
		
}
