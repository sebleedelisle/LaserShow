//
//  ClappyBird.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 18/03/2014.
//
//

#pragma once

#include "LaserManager.h"

struct Column {
	
	Column(float x, float gapheight, float gapsize)  {
		xpos = x;
		
		gapHeight = gapheight;
		gapSize = gapsize; 
		
	};
	
	float xpos, gapHeight, gapSize;
	
};

class ClappyBird {

	public:
	
	ClappyBird() : laserManager(*LaserManager::instance()) {
	
		top = 300;
		bottom = 700;
		ypos = top;
		xpos = 400;
		yvel = 0;
		radius = 30; 
		
		sensitivity = 1;
		
		columnsPerSecond= 0.4;
		
		birdSVGs.push_back(ofxSVG());
		birdSVGs.back().load("flappy bird.svg");
		birdSVGs.push_back(ofxSVG());
		birdSVGs.back().load("flappy bird.svg");
		birdSVGs.push_back(ofxSVG());
		birdSVGs.back().load("flappy wing up.svg");
		birdSVGs.push_back(ofxSVG());
		birdSVGs.back().load("flappy wing up.svg");
		birdSVGs.push_back(ofxSVG());
		birdSVGs.back().load("flappy bird.svg");
		birdSVGs.push_back(ofxSVG());
		birdSVGs.back().load("flappy bird.svg");
		birdSVGs.push_back(ofxSVG());
		birdSVGs.back().load("flappy wing down.svg");
		currentBirdSVG = 0;
		birdSVGs.back().load("flappy wing down.svg");
		currentBirdSVG = 0;
		
		reset(); 
		
	}

	LaserManager& laserManager;
	
	void update(float inputlevel, float deltatime);
	void draw() ;
	void reset(); 
	
	float top, bottom, ypos, yvel, xpos ;
	float elapsedTime;
	int columnsMade;
	float columnsPerSecond;
	float radius;
	
	ofParameter<float> sensitivity; 
	deque<Column> columns;
	
	bool alive;
	
	int score; 
	
	vector<ofxSVG> birdSVGs;
	int currentBirdSVG; 

};