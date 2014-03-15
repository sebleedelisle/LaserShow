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
	
	
	ofPoint pos;
	float length;
	
	
	
};

class LaserBeamEffect {
	

	
	
	public :
	
	LaserBeamEffect(); 
	
	void update();
	void draw(LaserManager& lm);
	
	deque<LaserBeam> beams;
	float speed;
	
	float elapsedTime;
	float emitCount;
	float emitRate;
	int maxBeams;
	
	bool running; 
	

	
};