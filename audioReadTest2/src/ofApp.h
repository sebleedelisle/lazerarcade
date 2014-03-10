#pragma once

#include "ofMain.h"
#include "AudioSample.h"
#include "ofxGui.h"
#include "MultiLatSpring.h"
#include "SonicHitFinder.h"

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
				
		void audioIn(float * input, int bufferSize, int nChannels);
	
	SonicHitFinder hitFinder; 
	/*
	void calculateOffsets();
	void scalarChanged(float& v);
	
	
	void updateTDOAs();
	
	vector<AudioSample> inputs;
	vector<AudioSample> hitWaves;
	vector<int> hitPeakPositions;
	int numChannels;
	
	MultiLatSpring solver; 
	
	
	long sampleCounter;

	
	long peakPosition;
	

	//vector<float> offsetVolumes;
	
	ofSoundStream soundStream;
	*/
	
	ofParameterGroup params;
	vector<ofParameter<float> > thresholds;
	ofParameter<float> scalar; 
	
	
	ofxPanel gui;
};
