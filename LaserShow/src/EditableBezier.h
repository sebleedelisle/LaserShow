//
//  EditableBezier.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 12/03/2014.
//
//
#pragma once
#include "ofMain.h"

class EditableBezier {


	public :
	EditableBezier();
	EditableBezier(ofPoint& _start, ofPoint& _c1, ofPoint& _c2, ofPoint& _end);
	EditableBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2);

	void set(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2); 
	void set(ofPoint _start, ofPoint _c1, ofPoint _c2, ofPoint _end);
	void draw();
	
	
	void mouseDragged(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	
	
	ofPoint start, c1, c2, end;
	
	
	bool editable;
	
	bool startDragging, c1Dragging, c2Dragging, endDragging;
	ofPoint lastMousePos;
	
	ofPoint dragOffset;
	float handleSize; 









};