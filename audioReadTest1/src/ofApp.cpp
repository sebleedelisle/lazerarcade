#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);	
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	soundStream.listDevices();
	
	//if you want to set a different device id 
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 1024;
	
	waveformSize = 5;
	leftPeak = 0;
	rightPeak = 0;
	peakThreshold = 0.1;
	peakResetSamples = 10000; 
	peakPosition = -10000000;
	
	//left.assign(bufferSize, 0.0);
	//right.assign(bufferSize, 0.0);
	leftPeakPreview = AudioSample(1536);
	rightPeakPreview = AudioSample(1536);
	
	left = AudioSample(11000);
	right = AudioSample(11000);
	
	gui.setup("panel");
	gui.setVisible(true);
	gui.add(leftThreshold.set("left threshold", 0.1, 0, 1));
	gui.add(rightThreshold.set("right threshold", 0.1, 0, 1));
	
	//gui.add(params);
	
	//volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	
	maxSampleCount = 10000;
	
	soundStream.setDeviceID(5);
	soundStream.setup(this, 0, 4, 96000, bufferSize, 4);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	
	//cout << peakPosition << endl;
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(128);
	gui.draw();

	
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
	ofVertex(offsetVolumes.size(),ofGetHeight());
	ofEndShape(true); 
	ofSetColor(255,0,0);
	ofLine(300,ofGetHeight()-100,300,ofGetHeight());
	ofLine(smallestpos,ofGetHeight()-100,smallestpos,ofGetHeight());
	float subtractionoffset = 300-smallestpos; 
	
	
	
	
	 
	ofNoFill();
	
	
	ofPushMatrix();
	ofScale(ofGetWidth(), ofGetHeight()/4);

	
	leftPeakPreview.draw(0,0,1,1);
	ofLine(0,(1 - leftThreshold)/2, 1, (1 - leftThreshold)/2);
	ofLine(0,0.5+(leftThreshold/2), 1, 0.5+(leftThreshold/2));
	
	
	ofLine(ofMap(firstPeakLeft, 0, leftPeakPreview.numSamples, 0, 1), 0, ofMap(firstPeakLeft, 0, leftPeakPreview.numSamples, 0, 1), 1);

	ofTranslate(0,1);
	
	rightPeakPreview.draw(0,0,1,1);
	ofLine(0,(1 - leftThreshold)/2, 1, (1 - leftThreshold)/2);
	ofLine(0,0.5+(leftThreshold/2), 1, 0.5+(leftThreshold/2));
	
	
	ofLine(ofMap(firstPeakRight, 0, rightPeakPreview.numSamples, 0, 1), 0, ofMap(firstPeakRight, 0, rightPeakPreview.numSamples, 0, 1), 1);
	subtractionoffset +=firstPeakLeft;
	ofSetColor(255,255,0);
	ofLine(ofMap(subtractionoffset, 0, rightPeakPreview.numSamples, 0, 1), 0, ofMap(subtractionoffset, 0, rightPeakPreview.numSamples, 0, 1), 1);
	
	
	ofTranslate(0,1);
	
	left.draw(0,0,1,1);
	ofLine(0,(1 - leftThreshold)/2, 1, (1 - leftThreshold)/2);
	ofLine(0,0.5+(leftThreshold/2), 1, 0.5+(leftThreshold/2));
	ofTranslate(0,1);
	
	
	right.draw(0,0,1,1);
	ofLine(0,(1 - rightThreshold)/2, 1, (1 - rightThreshold)/2);
	ofLine(0,0.5+(rightThreshold/2), 1, 0.5+(rightThreshold/2));
	ofTranslate(0,1);
	
	ofPopMatrix(); 
	
	
	/*
	ofBeginShape();
	for (unsigned int i = 0; i < leftPeakPreview.size(); i++){
		ofVertex(i, ofMap(leftPeakPreview[i], -1, 1, 0,100, true));
	}
	ofEndShape(false);
	ofBeginShape();
	for (unsigned int i = 0; i < rightPeakPreview.size(); i++){
		ofVertex(i, ofMap(rightPeakPreview[i], -1, 1, 100,200, true));
	}
	ofEndShape(false);
	
	ofLine(512, 0, 512,100);
	ofLine(512 + ((rightPeak - leftPeak)), 100, 512 + ((rightPeak - leftPeak)), 200 );
	 */

	
	ofPopStyle();
	
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	
	//cout << nChannels<< endl;
	
	curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	
	float leftsample, rightsample;
	for (int i = 0; i < bufferSize; i++){
		leftsample = input[i*2];
		rightsample = input[i*2+1];
		
		left.append(leftsample);
		right.append(rightsample);

		if(left.absolutePosition > peakPosition + 48000) {
			//cout << "potential new peak" << endl;
			if(abs(leftsample)>leftThreshold) {
				peakPosition = left.absolutePosition;
				//cout << " -  new peak" << endl;
			} else if(abs(rightsample)>rightThreshold) {
				peakPosition = right.absolutePosition;
				//cout << " -  new peak" << endl;

			}
			
		}
		numCounted++;
		sampleCounter ++;
	
	
		
//		cout << left.absolutePosition << " "  << ((long)peakPosition + (long)left.numSamples) << " " << (left.absolutePosition == (long)peakPosition + (long)left.numSamples)<< endl;
		if(left.absolutePosition == (long)peakPosition + (long)(left.numSamples)) {
			
			//cout << "copying samples" << endl;

			leftPeakPreview.copyFrom(left, peakPosition - 50);
			rightPeakPreview.copyFrom(right, peakPosition - 50);
			
			calculateOffsets(); 
			
			leftPeakPreview.updateVolume();
			rightPeakPreview.updateVolume();
			
			leftPeakPreview.normalise();
			rightPeakPreview.normalise();
			
			firstPeakLeft = leftPeakPreview.findFirstPeakOverThreshold(leftThreshold);
			firstPeakRight = rightPeakPreview.findFirstPeakOverThreshold(rightThreshold);
			
			cout << (firstPeakLeft - firstPeakRight) << "    " << ofMap((firstPeakLeft - firstPeakRight), -270,270,0,140) << endl;
			
		}
	}
	/*
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	*/
	bufferCounter++;
	
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	/*
	if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}*/
}


void ofApp::calculateOffsets() {
	

	if(offsetVolumes.size()<600) offsetVolumes.assign(600,0);
//	offsetVolumes.erase(offsetVolumes.begin(), offsetVolumes.end());
	
	float averagevolume = 0;
	int numsamples = 0;
	float leftsample, rightsample;
	
	for(int j = 0; j<600; j++)  {
		
		int offset = j-300;
		
		averagevolume = 0;
		numsamples = 0;

		
		for(int i = 0; i<leftPeakPreview.numSamples/2; i++) {
			
			int sampleleftindex = i;
			int samplerightindex = i+offset;
			
			if(samplerightindex<0) continue;
			else if(samplerightindex>rightPeakPreview.numSamples) break;
			
			leftsample = leftPeakPreview.samples[i];
			rightsample = rightPeakPreview.samples[samplerightindex];
			//leftsample=leftsample* leftsample * leftsample;
			//rightsample=rightsample* rightsample * rightsample;
			
			float combinedsample =  leftsample - rightsample ;
			averagevolume += abs(combinedsample);//*combinedsample;
			
			numsamples ++;
		}
	
		averagevolume /= numsamples;
		//cout << averagevolume << endl;
		offsetVolumes[j] = averagevolume;
		
	}
	
	
	
	
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

