//
//  EditableBezier.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 12/03/2014.
//
//

#include "EditableBezier.h"


EditableBezier :: EditableBezier(){
	set(100,100,200,50,300,5,400,100);
}

EditableBezier :: EditableBezier(ofPoint& _start, ofPoint& _c1, ofPoint& _c2, ofPoint& _end){
	set(_start, _c1, _c2, _end);
}


EditableBezier::EditableBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2) {
	set(x1, y1, c1x, c1y, c2x, c2y, x2, y2);
		
}



void EditableBezier::set(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2){
	
	set(ofPoint(x1,y1,0), ofPoint(c1x,c1y,0), ofPoint(c2x,c2y,0), ofPoint(x2,y2,0));
	
}
// MASTER SET FUNCTION - all constructors call this.
void EditableBezier :: set(ofPoint _start, ofPoint _c1, ofPoint _c2, ofPoint _end){
	start = _start;
	end = _end;
	c1 = _c1;
	c2 = _c2;
	
	
	editable = true;
	handleSize = 5;
	
	ofAddListener(ofEvents().mousePressed, this, &EditableBezier::mousePressed);
	//ofAddListener(ofEvents().mouseMoved, this, &EditableBezier::_mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &EditableBezier::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &EditableBezier::mouseReleased);

}

void EditableBezier::draw() {

	ofBezier(start, c1, c2, end);
	
	if(editable) {
		ofPushStyle();
		ofNoFill();
		ofCircle(start, handleSize);
		ofCircle(c1, handleSize);
		ofCircle(c2, handleSize);
		ofCircle(end, handleSize);
		ofLine(start, c1);
		ofLine(end, c2);
		ofPopStyle();
	}
	
}

void EditableBezier::mousePressed(ofMouseEventArgs &e) {
	ofPoint mousepos(e.x,e.y);
	
	if(!editable) return; 
	
	if(start.distance(mousepos)<handleSize) {
		startDragging = true;
	} else if(c1.distance(mousepos)<handleSize) {
		c1Dragging = true;
	} else if(c2.distance(mousepos)<handleSize) {
		c2Dragging = true;
	} else if(end.distance(mousepos)<handleSize) {
		endDragging = true;
	}
	lastMousePos = mousepos; 
	
	
}

void EditableBezier::mouseReleased(ofMouseEventArgs &e) {
	ofPoint mousepos(e.x,e.y);
	if(!editable) return; 
	startDragging = c1Dragging = c2Dragging = endDragging = false;
	
}

void EditableBezier::mouseDragged(ofMouseEventArgs &e) {
	ofPoint mousepos(e.x,e.y);
	if(!editable) return; 
	ofPoint diff = mousepos - lastMousePos;
	if(startDragging) {
		start+=diff;
	}
	if(c1Dragging || startDragging) {
		c1+=diff;
	}
	if(c2Dragging || endDragging) {
		c2+=diff;
	}
	if(endDragging) {
		end+=diff;
	}
	
	
	lastMousePos = mousepos;
}


