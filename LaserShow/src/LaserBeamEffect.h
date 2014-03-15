//
//  LaserBeamEffect.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 12/03/2014.
//
//
#pragma once

#include "ofMain.h"
#include "LaserManager.h"

struct LaserBeam {
	
	LaserBeam() {
		pos.set(0,0,0);
		length = 300;
		colour = ofColor::white;
		intensity = 0;
		
	};
	ofPoint pos;
	float length;
	ofColor colour;
	float intensity; 
	
	
};

class LaserBeamEffect {
	
	public :
	
	LaserBeamEffect(); 
	
	void update();
	void draw(LaserManager& lm, float intensity);
	
	deque<LaserBeam> beams;
	float speed;
	
	float elapsedTime;
	float emitCount;
	float emitRate;
	int maxBeams;
	
	bool running;
	bool multiColoured;
	float currentHue;
	bool rotateEmission;
	float currentAngle;
	bool respondToVolume;
	

	
};