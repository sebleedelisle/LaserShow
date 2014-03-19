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
	
	Column(float x, float y)  {
		xpos = x;
		gapHeight = y;
		
	};
	
	float xpos, gapHeight;
	
	
};

class ClappyBird {

	public:
	
	ClappyBird() : laserManager(*LaserManager::instance()) {
	
		top = 400;
		bottom = 700;
		ypos = top;
		xpos = 340;
		yvel = 0;
		
		elapsedTime = -3;
		columnsMade = 0; 
	
	}

	LaserManager& laserManager;
	
	void update(float inputlevel, float deltatime);
	void draw() ;
	
	float top, bottom, ypos, yvel, xpos ;
	float elapsedTime;
	int columnsMade;
	float columnsPerSecond = 0.5;
	deque<Column> columns; 

};