//
//  EffectLaserBeams.h
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
		hue =0;
		saturation = 0; 
		intensity = 0;
		
	};
	ofPoint pos;
	float length;
	float hue;
	float saturation; 
	float intensity; 
	
	
};

class EffectLaserBeams {
	
	public :
	
	EffectLaserBeams(); 
	
	void update(float deltaTime);
	void draw(LaserManager& lm, float intensity);
	
	deque<LaserBeam> beams;
	float speed;
	
	float elapsedTime;
	float emitCount;
	float emitRate;
	int maxBeams;
	
	int mode = 0;
	bool multiColoured;
	float currentHue;
	bool rotateEmission;
	float currentAngle;
	bool respondToVolume;
	

	
};