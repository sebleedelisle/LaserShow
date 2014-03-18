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
	
	DomeLine(float startposition, float timetotarget, ofColor colour, bool _lateral = true, float _target = 1, float fullcircle = false) {
		pos = startposition;
		startPos = pos; 
		timeToTarget = timetotarget;
		col = colour;
		lateral = _lateral;
		target = _target;
		elapsedTime = 0;
		fullCircle = fullcircle;
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
	bool fullCircle;
	
	
	
};

struct MarchingCircle {
	
	float startAngle = -180;
	float targetAngle = 0;
	float currentAngle = -180;
	float duration = 1;
	float elapsedTime = 0;
	float size = 25;
	
	float bezierPosition; 
	ofColor col;
	
	void update(float deltaTime) {
		elapsedTime+=deltaTime;
		currentAngle = startAngle + ((targetAngle-startAngle)*(elapsedTime/duration));
	}
	
};

class EffectDomeLines {
	
	public :
	
	EffectDomeLines();
	
	void update(float deltaTime);
	void draw(Synchroniser& sync, float volume, LaserManager& lm);
	
	void setDomeData(DomeData* domedata);
	void setMode(int mode); 
	
	DomeData* domeData = NULL;
	deque <DomeLine> lines; 
	
	float hue;
	int mode=3; // off
	
	bool doSecondCircleRow = false; 
	
	deque<float> volumes;
	
	vector<ofColor> ringColours;
	int currentColourIndex = 0;
	
	deque<MarchingCircle> circles; 
	

};

