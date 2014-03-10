//
//  ColourSystem.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 29/10/2013.
//
//
#pragma once

class ColourSystem {

	public :
	
	ColourSystem() {
		defaultColour = ofColor::white;
	};
	
	ColourSystem(ofColor col) {
		defaultColour = col;
	};
	
	virtual ofColor getColourForPoint(float unitProgress, ofPoint& pos) {
		return defaultColour;
	}

	ofColor defaultColour;
};