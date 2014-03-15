//
//  .h
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



struct DomeLine {
	
	DomeLine(float startposition, float timetotarget, ofColor colour, bool _lateral = true, float _target = 1) {
		pos = startposition;
		startPos = pos; 
		timeToTarget = timetotarget;
		col = colour;
		lateral = _lateral;
		target = _target;
		elapsedTime = 0; 
	}
	
	void update(float deltaTime) {
		elapsedTime+=deltaTime;
		pos=startPos + (target - startPos) * (elapsedTime / timeToTarget);
		//vel-=(deltaTime);
	}
	
	float pos;
	float startPos; 
	float target; 
	float timeToTarget; // per second?
	float elapsedTime; 
	ofColor col;
	bool lateral;
	
	
	
};


class EffectDomeLines {
	
	public :
	
	void update(float deltaTime);
	void draw(Synchroniser& sync, float volume, LaserManager& lm);
	
	void setDomeData(DomeData* domedata); 
	
	DomeData* domeData = NULL;
	deque <DomeLine> lines; 
	
	float hue;
	int mode=0; // off
	

};

