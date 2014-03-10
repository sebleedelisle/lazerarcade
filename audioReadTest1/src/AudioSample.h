//
//  AudioBuffer.h
//  multilaterationTest
//
//  Created by Seb Lee-Delisle on 30/01/2014.
//
//

#pragma once
#include "ofMain.h"

class AudioSample {


	public :
	AudioSample() {
		numSamples = 0;
	}
	AudioSample(int numsamples);
	
	vector <float> samples;
	vector <float> volumes;
	int numSamples;
	int position;
	bool volumesUpdated; 
	long absolutePosition;
	
	void append(float sample);
	void draw(float x, float y, float w, float h);
	void copyFrom(AudioSample& sample, long startPosition);
	float getSampleAtPosition(long absposition);
	void updateVolume();
	void normalise(); 
	
	int findFirstPeakOverThreshold(float threshold);

};