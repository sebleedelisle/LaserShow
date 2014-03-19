//
//  ClappyBird.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 18/03/2014.
//
//

#include "ClappyBird.h"



void ClappyBird :: update(float inputlevel, float deltatime) {

	inputlevel = ofClamp(inputlevel, 0, 1) * sensitivity;

	
	if((elapsedTime > 0) && (columnsMade / elapsedTime < columnsPerSecond)) {
		// make column
		columns.push_back(Column(1280, top + ((bottom-top)/2), ofMap(columnsMade, 0, 5, 100, 50, true)));
		columnsMade++; 
		
	}
	
	
	// bird physics
	
	//yvel -= inputlevel*deltatime*500;
	
	//ypos += yvel;
	
	// drag
	//yvel*=0.99;
	// gravity
	//yvel+=deltatime* 200;
	
	if(alive) {
		yvel*=0.9;
		float target = ofMap(inputlevel, 0, 1, bottom, top, true);
		yvel += (target-ypos) * 0.02;
	} else {
		yvel +=2;
	}
	ypos+=yvel;
	
	if(ypos > bottom - radius) {
		if(alive) yvel *= -0.8;
		else yvel = 0; 
		ypos = bottom - radius;
	}

	
	for(int i = 0; i<columns.size(); i++) {
		Column & column = columns[i];
		
		if((column.xpos < xpos + radius) && (column.xpos+50 > xpos-radius)){
			if((ypos-radius < column.gapHeight - column.gapSize) || (ypos+radius > column.gapHeight + column.gapSize)) {
				alive = false;
			}
			
		}
		
		float lastpos = column.xpos;
		
		if(alive) column.xpos -=deltatime*200;
		
		if((lastpos+50>=xpos-radius) && (column.xpos+50<xpos-radius)) score++;
		
		if(column.xpos <-50) {
			columns.erase(columns.begin()+i);
			i--;
		}
		
		
		
	}
	
	
	elapsedTime += deltatime; 

}

void ClappyBird :: draw() {
	
	
	
	for(int i = 0; i<columns.size(); i++) {
		Column & column = columns[i];

			laserManager.addLaserRectEased(ofPoint(column.xpos, top), ofPoint(50,column.gapHeight - column.gapSize - top), ofColor::green);
			laserManager.addLaserRectEased(ofPoint(column.xpos, column.gapHeight + column.gapSize), ofPoint(50,bottom - (column.gapHeight + column.gapSize)), ofColor::green);
		
	}
	
	//laserManager.addLaserCircle(ofPoint(xpos, ypos),ofColor:: yellow, radius);
	//laserManager.addLaserDot(ofPoint(xpos, ypos),ofColor:: yellow);
	float rotation = ofMap(yvel, -15,15,-45,45, true);
	laserManager.addLaserSVG(birdSVGs[currentBirdSVG], ofPoint(xpos, ypos), ofPoint(1,1), rotation);
	
	if(yvel<-1) {
		currentBirdSVG++;
		if(currentBirdSVG>=birdSVGs.size()) currentBirdSVG = 0;
		
	} else {
		currentBirdSVG = 0;
	}
	
	if(!alive) laserManager.addLaserText("SCORE "+ofToString(score), ofPoint(640,480), 10, ofColor::magenta, true);
	//else laserManager.addLaserText(ofToString(score), ofPoint(100,top), 6, ofColor::magenta, true);
}

void ClappyBird :: reset() {
	
	alive = true;
	elapsedTime = -1;
	columnsMade = 0;
	score = 0;
	columns.clear();

}