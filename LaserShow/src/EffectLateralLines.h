//
//  EffectLateralLines.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//
#pragma once 



#include "ofMain.h"
#include "Synchroniser.h"
#include "DomeData.h"
#include "LaserManager.h"



struct LateralLine {
	
	LateralLine(float position, float velocity, ofColor colour) {
		pos = position;
		vel = velocity;
		col = colour;
	}
	
	void update() {
		float deltaTime = ofGetLastFrameTime();
		pos+=(vel*deltaTime);
		//vel-=(deltaTime);
	}
	
	float pos; // 0 to 1 from bottom to top
	float vel; // per second?
	ofColor col;
	
	
};


class EffectLateralLines {
	
	public :
	
	void update();
	void draw(Synchroniser& sync, float volume, LaserManager& lm);
	
	void setDomeData(DomeData* domedata); 
	
	DomeData* domeData = NULL;
	deque <LateralLine> lines; 
	
	float hue; 

};

