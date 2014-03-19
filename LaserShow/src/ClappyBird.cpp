//
//  ClappyBird.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 18/03/2014.
//
//

#include "ClappyBird.h"



void ClappyBird :: update(float inputlevel, float deltatime) {

	inputlevel = ofClamp(inputlevel*3, 0, 1);

	
	if((elapsedTime > 0) && (columnsMade / elapsedTime < columnsPerSecond)) {
		// make column
		columns.push_back(Column(1280, 640));
		columnsMade++; 
		
	}
	
	for(int i = 0; i<columns.size(); i++) {
		Column & column = columns[i];
		column.xpos -=deltatime*200;
		if(column.xpos <0) {
			columns.erase(columns.begin()+i);
			i--;
		} else {
			laserManager.addLaserRectEased(ofPoint(column.xpos, 0), ofPoint(50,500), ofColor::green); 
			
		}
		
	}
	
	
	// bird physics
	
	yvel -= inputlevel*deltatime*500;
	
	ypos += yvel;
	
	// drag
	yvel*=0.99; 
	// gravity
	yvel+=deltatime* 200;
	
	
	if(ypos > bottom) {
		yvel *= 0;//-0.3;
		ypos = bottom; 
	}


	//ypos = ofMap(inputlevel, 0, 1, top, bottom, true);

	//cout << inputlevel << endl;
	
	elapsedTime += deltatime; 

}

void ClappyBird :: draw() {
	
	laserManager.addLaserCircle(ofPoint(xpos, ypos),ofColor:: yellow, 30);

}