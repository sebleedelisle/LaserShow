//
//  DomeData.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 11/03/2014.
//
//

#include "DomeData.h"



void draw();



DomeData :: DomeData() {
	
	params.add(pos.set("pos", ofPoint(640,480), ofPoint(-1280,-960, -4000), ofPoint(2560,1920, -2000)));
	params.add(scale.set("scale", 1, 0.1, 4));
	
	params.add(rotation.set("rot", ofPoint(30,0,0), ofPoint(0,-10,-10), ofPoint(50,10,10)));
	params.add(start.set("start", ofPoint(-500,300), ofPoint(-640,-480),ofPoint(640,480)));
	params.add(end.set("end", ofPoint(0,-220), ofPoint(-640,-480),ofPoint(640,480)));
	params.add(c1.set("c1", ofPoint(-480, -50), ofPoint(-640,-480),ofPoint(640,480)));
	params.add(c2.set("c2", ofPoint(-350,-220), ofPoint(-640,-480),ofPoint(640,480)));
	params.add(scaleXY.set("scaleXY", ofPoint(1,1,1), ofPoint(0.1,0.1,1),ofPoint(3,3,1)));
	
	gui.setup("Dome data", "domeData.xml");
	gui.setVisible(true);
	
	gui.add(params);
	

	
}

void DomeData :: draw() {
	//if(!editable) return;

	ofPushStyle();
	ofPushMatrix();
	ofTranslate(640,480);
	
	ofSetLineWidth(3);
	ofSetColor(255,0,255);
	ofBezier(start, c1, c2, end);
	ofLine(start, c1);
	ofLine(end,c2);
		
	ofPopMatrix();
	ofPushMatrix();
	
	ofTranslate(pos);
	
	ofRotateX(rotation->x);
	ofRotateY(rotation->y);
	ofRotateZ(rotation->z);
	ofScale(scale, scale, scale);
	ofScale(scaleXY->x, scaleXY->y, scaleXY->z);
	ofSetColor(255, 100);
	ofSetLineWidth(0.5);

	for(float x = start->x; x <= -start->x; x+= start->x / -5.0f) {
		
		ofLine(x, start->y, x, end->y);
		
		
	}
	for(float y = start->y; y >= end->y; y+= (end->y - start->y)/10.0f) {
		
		ofLine(start->x, y, -start->x, y);
	}
	
	ofSetColor(0,255,0);
	
	for(float angle = 0; angle>= -180.1; angle-=(180.0f/13.0f)) {
		ofPushMatrix();
		ofRotateY(angle);
		ofBezier(start, c1, c2, end);
		ofPopMatrix();
		//ofBezierPoint(<#ofPoint a#>, <#ofPoint b#>, <#ofPoint c#>, <#ofPoint d#>, <#float t#>)
		
	}
	

	ofPopStyle();
	ofPopMatrix();
	
	
	gui.draw();
	
}


void DomeData::mouseDragged(int x, int y){
	if(!editable) return;
	/*
	for(int i = 0; i<pipes.size(); i++) {
		pipes[i].mouseDragged(x, y);
		
	}*/
	
	
}

void DomeData::mousePressed(int x, int y){
	if(!editable) return;
	/*for(int i = 0; i<pipes.size(); i++) {
		// only click the first one it finds
		if (pipes[i].mousePressed(x, y)) break;
	}*/
	
	
}

void DomeData::mouseReleased(int x, int y){
	if(!editable) return;
	/*for(int i = 0; i<pipes.size(); i++) {
		pipes[i].mouseReleased(x, y);
		
	}*/
	
	save();
	
}


void DomeData::save(){
	
	gui.save();
}



void DomeData::load(){
	gui.load();
	
}

