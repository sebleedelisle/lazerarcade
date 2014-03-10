#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	cameraManager.init();
	cout <<	cameraManager.cameraFirewire->getShutter() << endl;
	cameraManager.cameraFirewire->setShutter(20);
	//cout <<	cameraManager.cameraFirewire->getShutter() << endl;
	//cameraManager.cameraFirewire->setGain(300);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	cameraManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	cameraManager.draw(0,0);
	if(cameraManager.capturing) {
		ofSetColor(255,0,0);
		ofCircle(10,10,10);
	}
	ofSetColor(255); 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if(key=='r') {
		if(cameraManager.capturing) {
			cameraManager.endCapture();
		} else {
			cameraManager.beginCapture();
		}
	}
	//cameraManager.cameraFirewire->setShutter(ofGetMouseY());
	//cout <<	cameraManager.cameraFirewire->getBrightness() << endl;
	//cameraManager.cameraFirewire->camera.setExposureAbs(ofGetMouseY());
	//cout <<	cameraManager.cameraFirewire->camera.getExposureAbs()<< endl;

	//SRcameraManager.cameraFirewire->set(mouseY);
}
