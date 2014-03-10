//
//  AudioBuffer.cpp
//  multilaterationTest
//
//  Created by Seb Lee-Delisle on 30/01/2014.
//
//

#include "AudioSample.h"


AudioSample::AudioSample(int numsamples) {
	
	numSamples = numsamples;
	samples.assign(numSamples, 0);
	volumes.assign(numSamples, 0);
	absolutePosition = 0;
	position = 0;
	volumesUpdated = false;

}

void AudioSample::append(float sample) {

	absolutePosition ++;
	position = absolutePosition % numSamples;
	
	samples[position] = sample;
	
	volumesUpdated = false;
	
}


void AudioSample::draw(float x, float y, float w, float h) {

	ofPushStyle();
	ofPushMatrix();
	ofTranslate(x, y+(h/2));
	
	ofSetColor(0,255,0);
	ofNoFill();
	ofSetLineWidth(1);
	//ofLine(x,y+h/2,x+w,y+h/2);
	
	ofBeginShape();
	//ofVertex(x+w,y+h/2);
	//ofVertex(x,y+h/2);
	for(int i = 0; i<samples.size(); i++) {
		
		int sampleindex = ((i-numSamples+1)+absolutePosition) %numSamples;
		float sample = 0;
		if(sampleindex>=0) sample = samples[sampleindex];
		
		ofVertex(ofMap(i,0,numSamples, 0, w), ofMap(sample, -1,1,-h/2,h/2));
		
		
	}
	
	ofEndShape(false); 
	
	/*
	if(volumesUpdated) {
		
		ofFill();
		ofSetColor(0,100,100);
		
		ofBeginShape();
		
		for(int i = 0; i<volumes.size(); i++) {
			
			int volumeindex = ((i-numSamples+1)+absolutePosition) %numSamples;
			float volume = 0;
			if(volumeindex>=0) volume = volumes[volumeindex];
			
			ofVertex(ofMap(i,0,numSamples, 0, w), ofMap(volume, 0,1,h/2, 0));
			
			
		}
		
		for(int i = volumes.size()-1; i<=0; i++) {
			
			int volumeindex = ((i-numSamples+1)+absolutePosition) %numSamples;
			float volume = 0;
			if(volumeindex>=0) volume = volumes[volumeindex];
			
			ofVertex(ofMap(i,0,numSamples, 0, w), ofMap(volume, 0,1,h/2, h));
			
			
		}
		ofEndShape(true); 
		
		
	}
	 
	 */
	ofPopMatrix();
	ofPopStyle();

}

void AudioSample::copyFrom(AudioSample &audiosample, long startPosition){
	
	
	for (int i = 0; i<numSamples; i++) {
		
		samples[i] = audiosample.getSampleAtPosition(startPosition+i); 
		
		
	}
	position = numSamples;
	absolutePosition = numSamples;
	
}

float AudioSample::getSampleAtPosition(long absposition){
	
	// if we are too far back in time
	if(absposition < absolutePosition - numSamples) return 0;
	// or if we are too far forward in time
	else if (absposition>absolutePosition) return 0; 
	 
	int index = absposition % numSamples;
	
	return samples[index];
	
}


void AudioSample::updateVolume() {
	
	float averageVolume = 0, sample;
	
	for(int i = 0; i<samples.size(); i++) {
		
		sample = samples[i];
		sample*=sample;
		
		averageVolume *= 0.999;
		averageVolume += sample * 0.05;
		
		volumes[i] = averageVolume;
		
		
	}
	volumesUpdated = true; 
}

int AudioSample :: findFirstPeakOverThreshold(float threshold) {
	
	bool thresholdreached = false;
	
	float sample = 0, lastsample = 0;
	
	for(int i = 0; i<numSamples; i++){
	
		sample = abs(samples[i]);
		
		if(sample>threshold) {
			thresholdreached = true;
		}
		
		if(thresholdreached) {
			if(lastsample>sample) return i;
		}
		
		lastsample = sample; 
		
	}
	
}


void AudioSample::normalise() {

	float maxlevel = 0;
	float sample;
	for(int i = 0; i<numSamples; i++) {
		sample = samples[i];
		if(abs(sample) > maxlevel) maxlevel = abs(sample);
		
	}
	
	float multiplier = 1/maxlevel;
	
	for(int i = 0; i<numSamples; i++) {
		samples[i]*=multiplier; 

	}


}