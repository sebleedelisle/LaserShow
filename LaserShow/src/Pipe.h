//
//  Pipe.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 11/03/2014.
//
//

#pragma once


class Pipe {

	public :
	
	Pipe(int index){
		
		topDragging = false;
		bottomDragging = false;
		topParam.set("top"+ofToString(index), ofPoint(0,0));
		bottomParam.set("bottom"+ofToString(index), ofPoint(0,0));
		pipeNumber = index;
		
	};
	
	void draw() {
		
		ofPushStyle();
		ofSetColor(255);
		ofSetLineWidth(2);
		ofNoFill();
		ofLine(top, bottom);
		ofCircle(top, handleSize);
		ofCircle(bottom, handleSize);
		ofPopStyle();
	}
	
	void setTop(float x, float y) {
		top.set(x,y);
		topParam.set(top);
	}
	void setBottom(float x, float y) {
		bottom.set(x,y);
		bottomParam.set(bottom);
		
	}
	
	void copyDataFromParams() {
		top.set(topParam);
		bottom.set(bottomParam);
	}
	
	bool mousePressed(int x, int y) {
		if(((ofVec3f)top).distance(ofPoint(x,y))<handleSize) {
			topDragging = true;
			startDragOffset.set(top - ofPoint(x,y));
			return true;
		}
		if(((ofVec3f)bottom).distance(ofPoint(x,y))<handleSize) {
			bottomDragging = true;
			startDragOffset.set(bottom - ofPoint(x,y));
			return true;
		}
		return false;

		
	};
	void mouseDragged(int x, int y) {
		if(topDragging) {
			top = ofPoint(x,y) + startDragOffset;
		} else if(bottomDragging) {
			bottom = ofPoint(x,y) + startDragOffset;
			
		}
	};
	
	void mouseReleased(int x, int y) {
		
		topDragging = false;
		bottomDragging = false;
		
		topParam.set(top);//(top.x, top.y);
		bottomParam.set(bottom);
		cout << pipeNumber << " SET TOP PARAM TO " << top.x << " " << top.y << " " <<topParam.get().x << " " << topParam.get().y << endl;
		
	};

	// pretty nasty to have duplication but working with
	// ofParameter<ofVec3f> causes loads of problems.
	ofParameter<ofVec3f> topParam;
	ofParameter<ofVec3f> bottomParam;
	ofVec3f top;
	ofVec3f bottom; 
	
	float handleSize = 5; 
	
	bool topDragging;
	bool bottomDragging;
	ofVec3f startDragOffset;
	int pipeNumber;
	
};