//
//  SonicHitFinder
//  
//
//  Created by Seb Lee-Delisle on 14/02/2014.
//
//

#pragma once
#include "AudioSample.h"
#include "MultilatSpring.h"
#include "RtAudio.h"
#include "ofxXmlSettings.h"

class SonicHitFinder {
	public:
	
	void setup(ofBaseApp * app, int w, int h, int numchannels);
	void update();
	void draw();
	
	void mousePressed(int x, int y);
	void mouseDragged(int x, int y);
	void mouseReleased(int x, int y);
	
	void audioIn(float * input, int bufferSize, int nChannels);
	
	void updateTDOAs();
	void updateHitPeakPositions();
	
	void scalarChanged(float& v);
	void allThresholdsChanged(float& v);
	void secondaryThresholdChanged(float& v);

	bool loadSettings();
	void saveSettings(); 
	
	int width, height;
	
	int hitCount; 
	
	
	vector<AudioSample> inputs;
	vector<AudioSample> hitWaves;
	vector<int> hitPeakPositions;
	int samplesBetweenHits; 
	int numChannels;
	int lastHitChannel;
	
	MultilatSpring solver;
	
	
	long sampleCounter;
	
	long peakPosition;
	
	
	ofSoundStream soundStream;
	
	
	ofParameterGroup params;
	vector<ofParameter<float> > thresholds;
	ofParameter<bool> showWaveForms;
	ofParameter<bool> showSolver;
	ofParameter<float> scalar;
	ofParameter<float> allThresholds; 
	ofParameter<float> secondaryThreshold;
	
	vector <ofVec2f>  micPositions;
	
	
	
}; 