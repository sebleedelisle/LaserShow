//
//  DragHandle.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 13/03/2014.
//
//
#pragma once

#include "ofMain.h"

class DragHandle {
	
	public:
	DragHandle () {
		
		ofAddListener(ofEvents().mousePressed, this, &DragHandle::mousePressed);
		ofAddListener(ofEvents().mouseDragged, this, &DragHandle::mouseDragged);
		ofAddListener(ofEvents().mouseReleased, this, &DragHandle::mouseReleased);
		
		visible = true;
		targetPoint = NULL;
		dragging = false;
		handleSize = 5; 
	
	}
	
	void render() {
		if(targetPoint==NULL) return;
		ofCircle(*targetPoint, handleSize);
		
	}
	
	
	void mousePressed(ofMouseEventArgs &e) {
		ofPoint mousepos(e.x,e.y);
		mousepos+=clickOffset;
		if((!visible)||(targetPoint ==NULL)) return;
		
		ofParameter<ofPoint> &point = *targetPoint;
		
		if(point->distance(mousepos)<handleSize) {
			dragging = true;
		} 
		lastMousePos = mousepos;
		
		
	}
	
	void mouseReleased(ofMouseEventArgs &e) {
		ofPoint mousepos(e.x,e.y);
		mousepos+=clickOffset;
		if((!visible)||(targetPoint ==NULL)) return;
		dragging = false;
	}
	
	void mouseDragged(ofMouseEventArgs &e) {
		ofPoint mousepos(e.x,e.y);
		mousepos+=clickOffset;
		if((!visible)||(targetPoint ==NULL)) return;
		
		ofPoint diff = mousepos - lastMousePos;
		ofParameter<ofPoint>& point = *targetPoint;
		
		if(dragging) {
			point+=diff;
		}
		
		lastMousePos = mousepos;
	}
	

	void setPoint(ofParameter<ofPoint>* point, ofPoint clickoffset) {
		targetPoint = point;
		clickOffset = clickoffset; 
	}
	void setPoint(ofParameter<ofPoint>* point) {
		setPoint(point, ofPoint(0,0));
		
	}
	ofPoint lastMousePos;
	ofParameter<ofPoint> *targetPoint;
	bool visible;
	ofPoint dragOffset;
	ofPoint clickOffset;
	float handleSize;
	bool dragging;
	
	
};