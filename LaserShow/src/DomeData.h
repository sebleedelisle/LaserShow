//
//  DomeData.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 11/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "EditableBezier.h"
#include "DragHandle.h"

class DomeData {

	public :
	
	DomeData();
	
	void draw();
	
	void save();
	void load();
	
	void mouseDragged(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);
	
	ofParameterGroup params;
	ofXml settings;
	bool editable;

	ofParameter<ofPoint> pos;
	ofParameter<ofPoint> rotation;
	ofParameter<ofPoint> start, end, c1, c2, scaleXY;
	ofParameter<float> scale, divAngle;
	
	ofParameter<ofVec3f> level1, level2, level3, level4;
	//ofPoint level1Point, level2Point, level3Point, level4Point;//, level2, level3, level4;
	
	DragHandle level1Handle, level2Handle, level3Handle, level4Handle;
	
	//EditableBezier level1;
	
	
	ofxPanel gui;
	

};