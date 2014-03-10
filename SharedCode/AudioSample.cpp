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

	absolutePosition = 0;
	position = 0;
	currentVolume = 0;
	peakVolume = 0; 


}

void AudioSample::append(float sample) {

	
	absolutePosition ++;
	position = absolutePosition % numSamples;
	
	samples[position] = sample;
	
	//if(absolutePosition%100 == 0 ) {
	//	currentVolume *= 0.99;
		if((absolutePosition%1000 == 0 )&&(absolutePosition-lastPeakTime > 200000)) {
			peakVolume -=0.005;
		}
	//}
	currentVolume *= 0.9995;
	currentVolume = CLAMP(currentVolume + (abs(sample) * 0.01),0,1);
	
	
	if(peakVolume < currentVolume) {
		peakVolume = currentVolume;
		lastPeakTime = absolutePosition; 
	}
	
	
	
		
}


void AudioSample::drawLevel(float x, float y, float w, float h) {
	ofPushMatrix();
	ofPushStyle();
	ofFill();
	ofTranslate(x,y+h);
	ofScale(1,-1);
	ofRect(0,0,w, h * currentVolume);
	ofLine(0,h * peakVolume, w, h*peakVolume);
	ofPopStyle();
	ofPopMatrix();
	
}

void AudioSample::drawWaveform(float x, float y, float w, float h) {

	ofPushStyle();
	ofPushMatrix();
	ofTranslate(x, y);
	ofDisableBlendMode();
	ofFill();
	ofSetColor(ofColor::black);
	ofRect(0,0,w,h);
	
	ofSetColor(0,255,0);
	ofNoFill();
	ofSetLineWidth(1);
	ofRect(0,0,w,h);
	
	ofTranslate(0,(h/2));
	
	
	//ofLine(x,y+h/2,x+w,y+h/2);
	
	ofBeginShape();
	//ofVertex(x+w,y+h/2);
	//ofVertex(x,y+h/2);
	
	/*
	for(int xpos = 0; xpos<w; xpos++) {
		
		int i = round(ofMap(xpos, 0, w, 0, numSamples));
		int sampleindex = ((i-numSamples+1)+absolutePosition) %numSamples;
		float sample = 0;
		if(sampleindex>=0) sample = samples[sampleindex];
		
		ofVertex(ofMap(i,0,numSamples, 0, w), ofMap(sample, -1,1,-h/2,h/2));
		
	}*/
	
	//float averageSample = 0;
	//int numSamplesToAverage = 0;
	float xpos = 0;
	float lastxpos = -1;
	float maxSample; 
	
	for(int i = 0; i<numSamples; i++) {
		
		int sampleindex = ((i-numSamples+1)+absolutePosition) %numSamples;
		float sample = 0;
		if(sampleindex>=0) sample = samples[sampleindex];
	
		if(abs(sample) > abs(maxSample)) maxSample = sample;
//		averageSample += sample;
//		numSamplesToAverage++;
		
		xpos=ofMap(i, 0, samples.size(), 0, w);
		//cout << xpos - lastxpos << endl;
		if((xpos) >= lastxpos + 1.0f) {
			lastxpos = xpos; //floor(xpos);
//			sample = averageSample / numSamplesToAverage;
			ofVertex(xpos, ofMap(maxSample, -1,1,-h/2,h/2));
			//averageSample = 0;
			//numSamplesToAverage = 0;
			maxSample = 0;

		}
		
				
		
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


/*void AudioSample::updateVolume() {
	
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
*/
// TODO  :  should take into account offset

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
	// TO DO should really be -1 so we no there was no hit found.
	return 0;//-1;
	
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