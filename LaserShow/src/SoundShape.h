//
//  SoundShape.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 10/03/2014.
//
//
#pragma once

#include "ofMain.h"

class SoundShape {

	public :
	
	SoundShape() {
		init(0,0, ofColor::white);
	}
	
	SoundShape(float x, float y, ofColor col) {
		init(x,y, col);
	};
	
	void init(float x, float y, ofColor col){
		pos.set(x,y);
		colour = col;
		visible = true;
		size = 50;
	};
	
	void draw(float scale = 1) {
	
		if(!visible) return;
		
		scale = ofClamp(scale, 0,1);
		
		ofPushMatrix();
		ofPushStyle();
		ofTranslate(pos);
		ofScale(size*scale, size*scale);
		ofNoFill();
		ofSetLineWidth(2);
		ofSetColor(colour); 
		ofRect(-0.5, -0.5, 1, 1);
	
		ofPopStyle();
		ofPopMatrix();
		
	};
	
	bool visible;
	
	ofVec3f pos;
	float size;
	ofColor colour;
	













};