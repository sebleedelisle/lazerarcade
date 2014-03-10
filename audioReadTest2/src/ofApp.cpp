#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);
	
	hitFinder.setup(this, ofGetWidth(), ofGetHeight(), 6);
	hitFinder.showWaveForms = true;
	/*
	solver.setup();
	
	solver.addMic(40,380);
	solver.addMic(500,380);
	solver.addMic(1024,375);
	solver.addMic(1024,700);
	solver.addMic(500,700);
	solver.addMic(40,700);
	
	
	
	soundStream.listDevices();
	
	//if you want to set a different device id 
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 1024;
	
	peakPosition = -10000000;
	
	numChannels = 6;
	
	
	inputs.assign(numChannels, AudioSample(96000));
	hitWaves.assign(numChannels, AudioSample(700));
	hitPeakPositions.assign(numChannels, 0); 
	*/
	gui.setup("panel");
	gui.setVisible(true);
	
	/*
	for(int i = 0; i<numChannels; i++) {
		string name = "threshold "+ofToString(i);
		
		thresholds.push_back(0.1);
		ofParameter<float> & param = thresholds[i]; 
		
		param.set(name, 0.1, 0, 1);
		gui.add(param);
	}*/
	
	gui.add(scalar.set("Scalar", 2.35, 0, 10));
	//scalar.addListener(this, &ofApp::scalarChanged);
	gui.setPosition(ofPoint(1000,0));
		/*
	soundStream.setDeviceID(6);
	soundStream.setup(this, 0, numChannels, 192000, bufferSize, 4);
	//soundStream.setup(this, 0, 2, 96000, bufferSize, 4);
*/
}

//--------------------------------------------------------------
void ofApp::update(){
	hitFinder.update();
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	
	float screenWidth = 1536;
	float screenHeight = 1024;
	
	
	//cout << peakPosition << endl;
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(128);
	
	hitFinder.draw();
	
		/*
	ofPushStyle();
	

	ofFill();
	float smallest = 1000;
	int smallestpos = 0;
	ofBeginShape();
	ofVertex(0,ofGetHeight());
	
	for(int i = 0; i<offsetVolumes.size(); i++) {
		ofVertex( i , ofGetHeight() - (offsetVolumes[i] * 1000));
		if(offsetVolumes[i]<smallest) {
			smallest = offsetVolumes[i];
			smallestpos = i;
		}
	}
	ofVertex(offsetVolumes.size(),screenHeight);
	ofEndShape(true); 
	ofSetColor(255,0,0);
	ofLine(300,ofGetHeight()-100,300,screenHeight);
	ofLine(smallestpos,screenHeight-100,smallestpos,screenHeight);
	float subtractionoffset = 300-smallestpos; 
	*/
	
	
	/*
	 
	ofNoFill();
	
	
	ofPushMatrix();
	ofScale(screenWidth/8, screenHeight/8);
	
	ofTranslate(0.05,0.05);
	for(int i = 0; i<inputs.size(); i++) {
		
		inputs[i].drawWaveform(0,0,1,1);
		ofLine(0,(1 - thresholds[i])/2, 1, (1 - thresholds[i])/2);
		ofLine(0,(1 + thresholds[i])/2, 1, (1 + thresholds[i])/2);
		ofTranslate(1.05,0);
		
		
	}
	ofPopMatrix();
	
	ofPushMatrix();
	
	//ofTranslate(secondScreen.x, secondScreen.y);

	for(int i = 0; i<inputs.size(); i++) {
		
		ofPushMatrix();
		ofTranslate(10,ofMap(i, 0, numChannels, 10, 200));
		ofScale(100,200/numChannels -10);
		
		inputs[i].drawWaveform(0,0,1,1);
		ofLine(0,(1 - thresholds[i])/2, 1, (1 - thresholds[i])/2);
		ofLine(0,(1 + thresholds[i])/2, 1, (1 + thresholds[i])/2);
		ofPopMatrix();
		
	}
	

	
	for(int i = 0; i<hitWaves.size(); i++) {
		ofPushMatrix();
		ofTranslate(120,ofMap(i, 0, numChannels, 10, 200));
		ofScale(880,200/numChannels -10);
		
		hitWaves[i].drawWaveform(0,0,1,1);
		float peakPosition = ofMap(hitPeakPositions[i], 0, hitWaves[i].numSamples, 0,1);
		ofSetColor(255);
		ofLine(peakPosition, 0,peakPosition, 1);
		
		ofPopMatrix();
				
	}
	
	ofPopMatrix();
		
	ofPopStyle();
	
	ofPushMatrix();
	//ofTranslate(secondScreen.x, secondScreen.y);
	solver.draw();
	ofPopMatrix();
	*/
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int numChannels){
	
	hitFinder.audioIn(input, bufferSize, numChannels);
	/*
	//cout << nChannels<< endl;
	
	//curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//while (inputs.size()<numChannels) {
	//	inputs.push_back(AudioSample(96000)); // default number of samples
	//}
	
	bool hitFound = false; 
	
	for (int i = 0; i < bufferSize; i++){
		for(int j = 0; j<numChannels; j++) {
			
			AudioSample & micAudioSample = inputs[j];
			float sample = input[i*numChannels + j];
			micAudioSample.append(sample);
			
			// can't have 2 hits within half a second - should prob extend that
			if(micAudioSample.absolutePosition > peakPosition + 48000){
				
				if(abs(sample)>thresholds[j]) {
					peakPosition = micAudioSample.absolutePosition;
					// should actually rewind to the previous zero crossing
				}
				
			}
			
			if(micAudioSample.absolutePosition == (long)peakPosition + (long)(hitWaves[j].numSamples)) {
				
				hitFound = true; 
				
				AudioSample & hitWave = hitWaves[j];
				hitWave.copyFrom(micAudioSample, peakPosition - 50);
				hitWave.updateVolume();
				hitWave.normalise();
				hitPeakPositions[j] = hitWave.findFirstPeakOverThreshold(0.15);
				
				
			}
			
			
		}

		sampleCounter ++;
	
		
	}
	
	if(hitFound) {
		updateTDOAs();
	}
	

	//bufferCounter++;
	 */
	
}
/*
void ofApp::scalarChanged(float& v) {
	
	updateTDOAs(); 
}
void ofApp::updateTDOAs() {
	
	int closestPeakPosition = hitWaves[0].numSamples;
	for(int i = 0; i<hitPeakPositions.size(); i++) {
		
		if(hitPeakPositions[i]<closestPeakPosition) {
			closestPeakPosition = hitPeakPositions[i];
		}
	}
	
	for(int i = 0; i<hitPeakPositions.size(); i++) {
		
		solver.setTDOA(i, (hitPeakPositions[i]-closestPeakPosition)*scalar);
	}
	solver.reset();

	
	
}
 
 */
//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	/*
	if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}*/
	
	if(key=='f') ofToggleFullscreen();
		
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	hitFinder.mouseDragged(x, y);
	//solver.mouseDragged(x-secondScreen.x, y-secondScreen.y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	hitFinder.mousePressed(x, y);
	//solver.mousePressed(x-secondScreen.x, y-secondScreen.y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	hitFinder.mouseReleased(x, y);
	//solver.mouseReleased(x-secondScreen.x, y-secondScreen.y);
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

