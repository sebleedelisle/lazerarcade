//
//  SonicHitFinder
//  
//
//  Created by Seb Lee-Delisle on 14/02/2014.
//
//

#include "SonicHitFinder.h"

//TODO
// how about a maximum normalise value so that we don't boost so much and see
// fake hits?


void SonicHitFinder :: setup(ofBaseApp * app, int w, int h, int numchannels){
	
	// num channels should probably be a setting
	
	width = w;
	height = h;
	numChannels = numchannels;
	samplesBetweenHits = 25000;
	scalar = 1;
	hitCount = 0;
	showWaveForms = false;
	showSolver = false;
	
	// todo replace with actual number. 
	solver.setup();
	params.setName("Hit Finder");

	micPositions.push_back(ofVec2f(40,380));
	micPositions.push_back(ofVec2f(500,380));
	micPositions.push_back(ofVec2f(1024,375));
	micPositions.push_back(ofVec2f(1024,700));
	micPositions.push_back(ofVec2f(500,700));
	micPositions.push_back(ofVec2f(40,700));
	
	loadSettings();
	
	for(int i = 0; i<numChannels; i++) {
		
		solver.setMicPosition(i, micPositions[i]);
		solverTest.setMicPosition(i, micPositions[i]);
		
		
	}
	
	//solver.micsEnabled[4] = false;
	//solverTest.micsEnabled[4] = false;
	
	// TODO : make this work :)
	// ie get the list of devices and add them to some sort of GUI thing.
	//---------------------------------------------------------------------------
	
	ofPtr<RtAudio> audioTemp;
	try {
		audioTemp = ofPtr<RtAudio>(new RtAudio());
	} catch (RtError &error) {
		error.printMessage();
		return;
	}
 	int devices = audioTemp->getDeviceCount();
	RtAudio::DeviceInfo info;
	for (int i=0; i< devices; i++) {
		try {
			info = audioTemp->getDeviceInfo(i);
		} catch (RtError &error) {
			error.printMessage();
			break;
		}
		ofLogNotice("ofRtAudioSoundStream") << "device " << i << " " << info.name << "";
		if (info.isDefaultInput) ofLogNotice("ofRtAudioSoundStream") << "----* default ----*";
		ofLogNotice("ofRtAudioSoundStream") << "maximum output channels " << info.outputChannels;
		ofLogNotice("ofRtAudioSoundStream") << "maximum input channels " << info.inputChannels;
		ofLogNotice("ofRtAudioSoundStream") << "-----------------------------------------";
	}
	//------------------------------------------------------------------------------
	
	
	
	inputs.assign(numChannels, AudioSample(48000));
	hitWaves.assign(numChannels, AudioSample(1400));
	hitPeakPositions.assign(numChannels, 0);
	//thresholds.assign(numChannels, 0.1);
	
	for(int i = 0; i<numChannels; i++) {
		string name = "threshold "+ofToString(i);
		
		thresholds.push_back(0.1);
		ofParameter<float> & param = thresholds[i];
		
		param.set(name, 0.1, 0, 1);
		//params.add(param);
	}
	
	params.add(showSolver.set("Show solver", false));
	params.add(showSolverTest.set("Show guide solver", true));
	
	params.add(allThresholds.set("All thresholds", 0.1, 0, 1));
	allThresholds.addListener(this, &SonicHitFinder::allThresholdsChanged);
	params.add(secondaryThreshold.set("Second threshold", 0.15, 0, 1));
	secondaryThreshold.addListener(this, &SonicHitFinder::secondaryThresholdChanged);
	
	
	params.add(scalar.set("Scalar", 2.35, 0, 10));
	scalar.addListener(this, &SonicHitFinder::scalarChanged);
	
	
	// should somehow make this all editable
	// output channels,
	// input channels
	// sample rate
	// samples per buffer
	// num buffers (latency)
	
	sampleRate = 96000;
	soundStream.setDeviceID(5);
//	soundStream.setup(app, 0, numChannels, 192000, 1024, 1);
	soundStream.setup(app, 0, numChannels, sampleRate, 1024, 1);
	
	//soundStream.setDeviceID(0);
	//soundStream.setup(app, 0, 2, 44100, 1024, 1);

		
}


void SonicHitFinder::update(){
	
	solver.update();
	solverTest.update(); 
	
}

void SonicHitFinder::draw() {

	
	ofSetColor(128);

	
	if(showWaveForms) {
		
		ofPushStyle();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofNoFill();
		
		ofPushMatrix();
		
		ofDrawBitmapString(ofToString(hitCount), 30,10);
		
		for(int i = 0; i<inputs.size(); i++) {
			
			ofPushMatrix();
			ofTranslate(10,ofMap(i, 0, numChannels, height - 200, height - 10));
			ofScale(1,200/numChannels -10);
			
			inputs[i].drawWaveform(0,0,90,1);
			//ofLine(0,(1 - thresholds[i])/2, 1, (1 - thresholds[i])/2);
			ofLine(0,(1 + thresholds[i])/2, 1, (1 + thresholds[i])/2);
			ofPopMatrix();
			
		}
		
		for(int i = 0; i<inputs.size(); i++) {
			
			ofPushMatrix();
			ofTranslate(105,ofMap(i, 0, numChannels, height - 200, height - 10));
			ofScale(10,200/numChannels -10);
			
			inputs[i].drawLevel(0,0,1,1);
			//ofLine(0,(1 - thresholds[i])/2, 1, (1 - thresholds[i])/2);
			//ofLine(0,(1 + thresholds[i])/2, 1, (1 + thresholds[i])/2);
			ofPopMatrix();
			
		}

		
		
		for(int i = 0; i<hitWaves.size(); i++) {
			ofPushMatrix();
			ofTranslate(120,ofMap(i, 0, numChannels, height - 200, height - 10));
			ofScale(1,200/numChannels -10);
			
			hitWaves[i].drawWaveform(0,0,880,1);
			float peakPosition = ofMap(hitPeakPositions[i], 0, hitWaves[i].numSamples, 0,880);
			ofSetColor(255);
			ofLine(peakPosition, 0,peakPosition, 1);
			
			if(i==lastHitChannel) {
				ofSetColor(255,0,0);
				ofRect(0,0,880,1);
			}
			ofPopMatrix();
			
		}
		
		ofPopMatrix();
		
		ofPopStyle();
	
	}
	
	if(showSolver) {
		solver.draw();
		if(showSolverTest){
			solverTest.draw(ofColor::red);
		}
	}
	
	//gui.draw();
}


//--------------------------------------------------------------
void SonicHitFinder::audioIn(float * input, int bufferSize, int numChannels){
	
	
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
			if(micAudioSample.absolutePosition > peakPosition + samplesBetweenHits){
				
				if(abs(sample)>thresholds[j]) {
					peakPosition = micAudioSample.absolutePosition;
					// should actually rewind to the previous zero crossing
					lastHitChannel = j;
				}
				
			}
			
			if(micAudioSample.absolutePosition == (long)peakPosition + (long)(hitWaves[j].numSamples)) {
				
				hitFound = true;
								
				AudioSample & hitWave = hitWaves[j];
				hitWave.copyFrom(micAudioSample, peakPosition - 200);
				
			}
			
			
		}
		
		sampleCounter ++;
		
		
	}
	
	if(hitFound) {
		
		
		
		updateHitPeakPositions();
		updateTDOAs();
		
		registerHit(solver.calculatedPoint);

	}
	
	
	//bufferCounter++;
	
}

void SonicHitFinder:: registerHit(ofVec2f& pos) {
	
	hits.push_back(pos);
	
	hitCount++;

	
}

vector<ofVec2f> SonicHitFinder:: getHits() {
	vector<ofVec2f>returnhits = hits;
	hits.erase(hits.begin(), hits.end());
	return returnhits; 
	
}
void SonicHitFinder::scalarChanged(float& v) {
	
	updateTDOAs();
}

void SonicHitFinder::allThresholdsChanged(float &v) {
	
	for(int i = 0; i<numChannels; i++) {
		thresholds[i] = v;
	}
	
}
void SonicHitFinder::secondaryThresholdChanged(float& v){
	
	updateHitPeakPositions();
	updateTDOAs();
	
	
}


void SonicHitFinder::updateHitPeakPositions() {
	
	for(int i = 0; i<numChannels; i++) {
		
		AudioSample & hitWave = hitWaves[i];
		
		//hitWave.updateVolume();
		hitWave.normalise();
		hitPeakPositions[i] = hitWave.findFirstPeakOverThreshold(secondaryThreshold, true);
		//cout << "peak position " << j << " = " << hitPeakPositions[j] << endl;
	
	}
	
}

void SonicHitFinder::updateTDOAs() {
	
	int closestPeakPosition = hitWaves[0].numSamples;
	for(int i = 0; i<hitPeakPositions.size(); i++) {
		
		if(hitPeakPositions[i]<closestPeakPosition) {
			closestPeakPosition = hitPeakPositions[i];
		}
	}
	
	for(int i = 0; i<hitPeakPositions.size(); i++) {
		
		solver.setTDOA(i, (hitPeakPositions[i]-closestPeakPosition)*scalar * ( 192000 / sampleRate));
	}
	solver.reset();
	solver.update();
	
	
}


//--------------------------------------------------------------
void SonicHitFinder::mouseDragged(int x, int y){
	solver.mouseDragged(x, y);
	//solver.mouseDragged(x-secondScreen.x, y-secondScreen.y);
}

//--------------------------------------------------------------
void SonicHitFinder::mousePressed(int x, int y){
	solver.mousePressed(x, y);
	
	if(solver.currentDragMic==-1)  { //&& (showSolver)) {
		solverTest.simulateHit(x, y);
		ofVec2f pos(x,y);
		registerHit(pos);
	}
	//solver.mousePressed(x-secondScreen.x, y-secondScreen.y);
}

//--------------------------------------------------------------
void SonicHitFinder::mouseReleased(int x, int y){
	solver.mouseReleased(x, y);
	micPositions = solver.mics;
}

bool SonicHitFinder::loadSettings() {
	
	string filename = "hitfinder.xml";
	ofxXmlSettings xml;
	if(!xml.loadFile(filename)) {
		ofLog(OF_LOG_ERROR, "SonicHitFinder::loadSettings - file not found : "+filename);
		return false;
		
	}
	
	for(int i = 0; i<numChannels; i++) {
		if(micPositions.size()<i) micPositions.push_back(ofVec2f(0,0));
		micPositions[i].x =  xml.getValue("hitFinder:micpos"+ofToString(i)+":x", micPositions[i].x);
		micPositions[i].y =  xml.getValue("hitFinder:micpos"+ofToString(i)+":y", micPositions[i].y);
	}
	   
	return true;
}

void SonicHitFinder::saveSettings() {
	
	ofxXmlSettings xml;
	
	string filename = "hitfinder.xml";
    
	xml.addTag("hitFinder");
	xml.pushTag("hitFinder");
	
	for(int i = 0; i<numChannels; i++ ) {
		
		xml.addTag("micpos"+ofToString(i));
		xml.pushTag("micpos"+ofToString(i));
		xml.addValue("x", micPositions[i].x);
		xml.addValue("y", micPositions[i].y);
		
		xml.popTag();
	}

	
	xml.saveFile(filename);
    
    
}


