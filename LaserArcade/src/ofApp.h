// STILL TO DO :
// Test TDOAs in SonicHitFinder to show where TDOA radii should be - set up on mouse click.
// Add numbers to projections
// Check volume in sound clips - see if there's a volume threshold we can check? 


#pragma once

#include "ofMain.h"
#include "LaserManager.h"
#include "SonicHitFinder.h"
#include "TargetPracticeGame.h"
#include "AsteroidsGame.h"
#include "CoconutShy.h"
#include "BottlesGame.h"
#include "DuckGame.h"

class ofApp : public ofBaseApp{

	public:
	void setup();
	void update();
	void draw();
	void audioIn(float * input, int bufferSize, int numChannels);
	void keyPressed(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void gotMessage(ofMessage msg);
	void exit();
	
	void setGame(int index); 
	
	int screenWidth, screenHeight;

	ofxPanel gui;
	LaserManager laserManager;
	AsteroidsGame asteroidsGame;
	TargetPracticeGame targetGame;
	CoconutShy coconutGame;
	DuckGame duckGame; 
	BottlesGame bottlesGame; 
	
	BaseGame* currentGame;
	int currentGameIndex; 
	
	vector <BaseGame*> games; 
	
	SonicHitFinder hitFinder;

		
};
