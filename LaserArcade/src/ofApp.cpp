#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofSetFrameRate(60);

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
	
	gui.setup("Settings");
	gui.setPosition(ofPoint(screenWidth - panelwidth - 10,10));
	gui.setVisible(true);
	gui.add(&laserManager.connectButton);
	gui.add(laserManager.parameters);
	

	gui.add(hitFinder.params);
	
	gui.load();
	
	
	asteroidsGame.setup(ofRectangle(0,screenHeight*0.3,screenWidth, screenHeight*0.7), &laserManager);
	targetGame.setup(ofRectangle(0,screenHeight*0.3,screenWidth, screenHeight*0.7), &laserManager);
	coconutGame.setup(ofRectangle(0,screenHeight*0.3,screenWidth, screenHeight*0.7), &laserManager);
	bottlesGame.setup(ofRectangle(0,screenHeight*0.3,screenWidth, screenHeight*0.7), &laserManager);
	duckGame.setup(ofRectangle(0,screenHeight*0.3,screenWidth, screenHeight*0.7), &laserManager);
	
	games.push_back(&coconutGame);
	games.push_back(&targetGame);
	games.push_back(&asteroidsGame);
	games.push_back(&bottlesGame);
	games.push_back(&duckGame);
	setGame(0); 
	
	
}


void ofApp::setGame(int index) {
	
	if(index >= games.size()) index = 0;
	else if(index<0) index = games.size()-1; 
	currentGameIndex = index;
	currentGame = games[index];
	currentGame->changeState(0);
	
	
}



//--------------------------------------------------------------
void ofApp::update(){
	laserManager.update();
	hitFinder.update();
	currentGame->update(hitFinder.getHits());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofDrawBitmapString(ofToString(round(ofGetFrameRate())), 0,10);
	
	
	if(hitFinder.showSolver) {
		vector<ofVec2f>& mics = hitFinder.micPositions;
		for(int i = 0; i<mics.size(); i++) {
			laserManager.addLaserDot(mics[i], ofColor(255)); 
			
			
		}
		
		if(hitFinder.showSolverTest) {
			laserManager.addLaserDot(hitFinder.solverTest.calculatedPoint, ofColor(255,0,0));

		}
		
	}
	
	currentGame->draw();
		
	laserManager.draw();
	laserManager.renderLaserPath(ofRectangle(0,0,screenWidth, screenHeight), false);
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
	
	if(key == ' ') {
		currentGame->toggleState();
	}
	if(key == OF_KEY_LEFT) {
		setGame(currentGameIndex-1);
	} else if(key == OF_KEY_RIGHT) {
		setGame(currentGameIndex+1);
	}
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