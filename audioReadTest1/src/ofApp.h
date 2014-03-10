#pragma once

#include "ofMain.h"
#include "AudioSample.h"
#include "ofxGui.h"

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
	void calculateOffsets(); 
	
	AudioSample left;
	AudioSample right; 
	
	
	/*
	deque <float> left;
	deque <float> right;
	deque <float> volHistory;
	*/
	AudioSample leftPeakPreview;
	AudioSample rightPeakPreview;

	int firstPeakLeft;
	int firstPeakRight;
	 
	int leftPeak;
	int rightPeak;

	float peakThreshold;
	int peakResetSamples; 

	float waveformSize;
	
	long 	bufferCounter;
	long	sampleCounter; 
	int 	drawCounter;
	int		maxSampleCount;
	
	long peakPosition;
	
		
	float smoothedVol;
	float curVol;
	float scaledVol;
	
	vector<float> offsetVolumes; 
	
	ofSoundStream soundStream;
	
	
	ofParameterGroup params;
	ofParameter<float> leftThreshold;
	ofParameter<float> rightThreshold;
	
	
	ofxPanel gui;
};
