#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableAntiAliasing();
	ofEnableSmoothing();

	screenWidth = 1280;
	screenHeight = 1024;
	
	laserManager.setup(screenWidth, screenHeight);
	//laserManager.connectToEtherdream();
	
	laserManager.renderLaserPreview = true;
	laserManager.showPostTransformPreview = true;
	
	hitFinder.setup(this, screenWidth, screenHeight, 6);

	
	
	int panelwidth = 200;
	
	ofxBaseGui::setDefaultWidth(panelwidth);
    ofxBaseGui::setDefaultHeight(16);
	ofxBaseGui::setDefaultSpacing(3);
    ofxBaseGui::setDefaultElementSpacing(3);
	ofxBaseGui::setDefaultElementIndentation(1);
	ofxBaseGui::setDefaultTextPadding(5);
	ofxBaseGui::setUseTTF(true);
	
	ofxBaseGui::loadFont("VeraMoIt.ttf",8, true);
	
	gui.setup("panel");
	gui.setPosition(ofPoint(screenWidth - panelwidth - 10,10));
	gui.setVisible(true);
	gui.add(&laserManager.connectButton);
	gui.add(laserManager.parameters);
	
	gui.add(hitFinder.params);
	
	
	
//	 for(int i = 0; i<numChannels; i++) {
//	 string name = "threshold "+ofToString(i);
//	 
//	 thresholds.push_back(0.1);
//	 ofParameter<float> & param = thresholds[i];
//	 
//	 param.set(name, 0.1, 0, 1);
//	 gui.add(param);
//	 }
//	
//	gui.add(scalar.set("Scalar", 2.35, 0, 10));
//	scalar.addListener(this, &ofApp::scalarChanged);
	
	
	
	gui.load();
	
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	laserManager.update();
	hitFinder.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	ofDrawBitmapString(ofToString(round(ofGetFrameRate())), 0,10);
	
	laserManager.addLaserCircle(ofPoint(screenWidth/2, screenHeight/2), ofColor::white, 100);
	
	laserManager.draw();
	laserManager.renderLaserPath(ofRectangle(0,0,ofGetWidth(), ofGetHeight()), false);
	laserManager.renderPreview();
	
	hitFinder.draw();
	
	
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'f') ofToggleFullscreen();
	if(key == '\t') gui.toggleVisible();
	if(key == 'w') laserManager.showWarpPoints = !laserManager.showWarpPoints;
	if(key == 'e') hitFinder.showWaveForms = !hitFinder.showWaveForms;
	if(key == 'r') hitFinder.showSolver = !hitFinder.showSolver;
}



//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int numChannels){
	
	hitFinder.audioIn(input, bufferSize, numChannels);
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	hitFinder.mouseDragged(x,y); 
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	hitFinder.mousePressed(x,y); 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	hitFinder.mouseReleased(x,y);
}


//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::exit() {
	gui.save();
	laserManager.warp.saveSettings();
	hitFinder.saveSettings();

}