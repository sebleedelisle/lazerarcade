#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	mics.push_back(ofVec2f(100,100));
	mics.push_back(ofVec2f(700,100));
	mics.push_back(ofVec2f(700,500));
	mics.push_back(ofVec2f(100,500));
	
	calculatedPoint = ofVec2f(400,300);
	mouseClickPoint = ofVec2f(400,300);
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	
	

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	ofNoFill();
	ofSetColor(255);
	ofRect(100,100,600,400);
	ofCircle(calculatedPoint, 10);
	ofCircle(mouseClickPoint, 1);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int mousex, int mousey, int button){
	
	
	mouseClickPoint.set(mousex,mousey);
	
	float closest = 20000;
	int closestindex = -1;
	
	for(int i = 0; i<4; i++) {
		
		float distance = mics[i].distance(mouseClickPoint);
		if(distance<closest) {
			closest = distance;
			closestindex = i;
		}
	}
	
	tdoas.erase(tdoas.begin(), tdoas.end());
	for(int i = 0; i<4; i++) {
		float distance = mics[i].distance(mouseClickPoint) - closest;
		if(distance > 0) distance += ofRandom(-1,1);
		tdoas.push_back(distance);
	}
	
	float height = 400;
	float width = 600;
	closestindex = 0; 
	float a = tdoas[closestindex];
	float b = tdoas[(closestindex+1)%4];
	float c = tdoas[(closestindex+2)%4];
	float d = tdoas[(closestindex+3)%4];
	
	cout << "a:"<<a<<" b:"<<b<<" c:"<<c<<" d:"<<d << endl; 

	float rad = (b*b-a*a+d*d-c*c) / (2*(a-b+c-d));
	cout << "rad:" << rad << endl;
	
	
	a+=rad;
	b+=rad;
	c+=rad;
	d+=rad;
	
	float p = (d+a+height) / 2;
	cout << "p:" << p << endl;
	
	float area = sqrt(p*(p-d)*(p-a)*(p-height));

	cout << "area:" << area << endl;
	float x = 2*area/height;
	
	p = (a+b+width) / 2;
	area = sqrt(p*(p-a)*(p-b)*(p-width));
	float y = 2*area/width;
	cout << "area:" << area << endl;
	
	calculatedPoint.set(x+100,y+100);
	
	cout << x << " " << y << endl;
	
}
