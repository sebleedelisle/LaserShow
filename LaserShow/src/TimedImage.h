//
//  TimedImage.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 09/03/2014.
//
//

#pragma once 

#include "TimedElement.h" 

class TimedImage : public TimedElement {

	public :
	
	
	
	void init (string filename, float start, float end) {
		
		img.loadImage(filename);
		startTime = start;
		endTime = end;
		
		
		
	}

	
	void draw(Synchroniser& sync) {
	
		if((sync.currentPosition> startTime) && (sync.currentPosition<endTime)) {
			ofPushStyle();
			ofSetColor(255);
			img.draw(0,0);
			ofPopStyle();
		}
		
		
	}
	
	ofImage img;
	float startTime;
	float endTime;




} ;