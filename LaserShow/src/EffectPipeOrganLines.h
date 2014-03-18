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
#include "ParticleSystemManager.h"
#include "ParticleRendererLaser.h"
#include "ParticleRendererLaserLine.h"



struct PipeOrganLine {
	
	PipeOrganLine(ofPoint toppos, ofPoint bottompos, ofColor colour, float starttop = 0, float startbottom = 1, float endtop = 0, float endbottom = 1, float durationsecs = 0.2 ) {
		top = toppos;
		bottom = bottompos; 
		set(colour, starttop, startbottom, endtop, endbottom, durationsecs);
				
	}
	
	void set(ofColor colour, float starttop = 0, float startbottom = 1, float endtop = 0, float endbottom = 1, float durationsecs = 0.2 ) {
		
		elapsedTime = 0;
		startTop =  starttop;
		startBottom =  startbottom;
		endTop = endtop;
		endBottom = endbottom;
		currentTop = top;
		currentBottom = bottom;
		duration = durationsecs;
		
		col = colour;

		
	}
	
	void update(float deltaTime) {
		elapsedTime+=deltaTime;
		
		topUnit = ofMap(elapsedTime, 0, duration, startTop, endTop, true);
		currentTop = top + ((bottom - top) * topUnit);
		bottomUnit = ofMap(elapsedTime, 0, duration, startBottom, endBottom, true);
		currentBottom = top + ((bottom - top)  * bottomUnit);
		
		
	}
	
	
	float elapsedTime; 
	ofColor col;
	
	float startTop, startBottom, endTop, endBottom, duration, topUnit, bottomUnit;
	ofPoint top, bottom, currentTop, currentBottom;
	
	
	
};


class EffectPipeOrganLines {
	
	public :
	
	void update(float deltaTime);
	void draw(Synchroniser& sync, float volume, LaserManager& lm, float currentPeak);
	
	void setObjects(PipeOrganData* pipeOrganData, ParticleSystemManager* psm);
	void makeParticleForPipe(int pipeindex, ofColor col);

	void setMode(int newmode); 
	
	PipeOrganData* pipeOrganData = NULL;
	ParticleSystemManager* particleSystemManager  = NULL;
	
	
	deque <PipeOrganLine> lines;
	int currentPipeIndex = 0; 
	
	float hue;
	
	protected :
	int mode=2; // 0 : off
	

};

