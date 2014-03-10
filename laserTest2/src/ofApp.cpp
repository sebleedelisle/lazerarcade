#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	

	
	laserManager.setup(ofGetWidth()-200, ofGetHeight());
	laserManager.connectToEtherdream();
	
	laserManager.renderLaserPreview = true;
	laserManager.showPostTransformPreview = true;
	
	
	gui.setup("panel");
	gui.setVisible(true);
	gui.add(&laserManager.connectButton);
	gui.add(laserManager.parameters);
	gui.load();
	
	vector<ofColor> cols;
	cols.push_back(ofColor::red);
	cols.push_back(ofColor::cyan);
	cols.push_back(ofColor::magenta);
	
	
	for(int i = 0; i< 6; i++) {
		targets.push_back(ofVec2f(ofRandom(100,800), ofRandom(100,600)));
		ofVec2f targetVel;
		targetVel.set(2);
		targetVel.rotate(ofRandom(360));
		targetVels.push_back(targetVel);
		
		colours.push_back(cols[i%3]);

	}

}

//--------------------------------------------------------------
void ofApp::update(){
	laserManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	int width = ofGetWidth()-200;
	int height = ofGetHeight();
	int radius = 30; 
	
	
	for(int i = 0; i<targets.size(); i++)  {
		
		ofVec2f& target = targets[i];
		ofVec2f& targetVel = targetVels[i];
		
		laserManager.addLaserCircle(target, colours[i], radius);
	
		target += targetVel;
		
		if(target.x >width - radius) targetVel.x *= -1;
		if(target.x <  radius) targetVel.x *= -1;
		if(target.y >height - radius) targetVel.y *= -1;
		if(target.y <  radius) targetVel.y *= -1;
	
	}
		
		
	laserManager.draw();
	laserManager.renderLaserPath(ofRectangle(0,0,ofGetWidth(), ofGetHeight()), true);
	laserManager.renderPreview();
	gui.draw(); 

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if(key == ' ') laserManager.toggleRegistration();

}


void ofApp::exit() {
	
	gui.save(); 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
