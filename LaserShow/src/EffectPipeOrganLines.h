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
#include "PipeOrganData.h"
#include "LaserManager.h"



struct PipeOrganLine {
	
	PipeOrganLine(ofPoint toppos, ofPoint bottompos, ofColor colour, float starttop = 0, float startbottom = 1, float endtop = 0, float endbottom = 1, float durationsecs = 0.2 ) {
		
		
		elapsedTime = 0;
		startTop =  starttop;
		startBottom =  startbottom;
		endTop = endtop;
		endBottom = endbottom;
		top = currentTop = toppos;
		bottom = currentBottom = bottompos;
		duration = durationsecs; 
		
		col = colour;
		
	}
	
	void update(float deltaTime) {
		elapsedTime+=deltaTime;
		
		float topunit = ofMap(elapsedTime, 0, duration, startTop, endTop);
		currentTop = top + ((bottom - top) * topunit);
		float bottomunit = ofMap(elapsedTime, 0, duration, startBottom, endBottom);
		currentBottom = top + ((bottom - top)  * bottomunit);
		
		
	}
	
	
	float elapsedTime; 
	ofColor col;
	
	float startTop, startBottom, endTop, endBottom, duration;
	ofPoint top, bottom, currentTop, currentBottom;
	
	
	
};


class EffectPipeOrganLines {
	
	public :
	
	void update(float deltaTime);
	void draw(Synchroniser& sync, float volume, LaserManager& lm, float currentPeak);
	
	void setPipeOrganData(PipeOrganData* pipeOrganData); 
	
	PipeOrganData* pipeOrganData = NULL;
	deque <PipeOrganLine> lines;
	int currentPipeIndex = 0; 
	
	float hue;
	int mode=2; // 0 : off
	

};

