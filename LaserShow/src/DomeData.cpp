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
	
	
	
	/*
	params.add(pos.set("pos", ofPoint(640,480), ofPoint(-1280,-960, -4000), ofPoint(2560,1920, 0)));
	params.add(scale.set("scale", 1, 0.1, 4));
	
	params.add(rotation.set("rot", ofPoint(30,0,0), ofPoint(0,-10,-10), ofPoint(50,10,10)));
	params.add(start.set("start", ofPoint(-500,300), ofPoint(-640,-480),ofPoint(640,480)));
	params.add(c1.set("c1", ofPoint(-480, -50), ofPoint(-640,-480),ofPoint(640,480)));
	params.add(c2.set("c2", ofPoint(-350,-220), ofPoint(-640,-480),ofPoint(640,480)));
	params.add(end.set("end", ofPoint(0,-220), ofPoint(-640,-480),ofPoint(640,480)));
	
	params.add(level1.set("level1", ofPoint(-500,0), ofPoint(-640,-480),ofPoint(0,480)));
	params.add(level2.set("level2", ofPoint(-500,100), ofPoint(-640,-480),ofPoint(0,480)));
	params.add(level3.set("level3", ofPoint(-500,200), ofPoint(-640,-480),ofPoint(0,480)));
	params.add(level4.set("level4", ofPoint(-500,300), ofPoint(-640,-480),ofPoint(0,480)));
	
	params.add(scaleXY.set("scaleXY", ofPoint(1,1,1), ofPoint(0.1,0.1,1),ofPoint(3,3,1)));
	params.add(divAngle.set("division angle",12, 0, 30));

	*/ 
	 
	gui.setup("Dome data", "domeData.xml");
	gui.setVisible(true);
	
	gui.add(params);
	

	
}

void DomeData :: draw() {
	//if(!editable) return;

	
	level1.draw();
	
	
	
	
	/*
	ofSetupScreenPerspective(1280,960,50);

	ofPushStyle();
	ofPushMatrix();
	ofTranslate(640,480);
	
	ofSetLineWidth(3);
	ofSetColor(255,0,255);
	ofBezier(start, c1, c2, end);
	ofLine(start, c1);
	ofLine(end,c2);
	
	ofCircle(start, 3);
	ofCircle(c1, 3);
	ofCircle(c2, 3);
	ofCircle(end, 3);

	ofSetColor(0,255,255);
	ofCircle(level1, 3);
	ofCircle(level2, 3);
	ofCircle(level3, 3);
	ofCircle(level4, 3);
		
	ofPopMatrix();
	ofPushMatrix();
	
	ofTranslate(pos);
	
	ofRotateX(rotation->x);
	ofRotateY(rotation->y);
	ofRotateZ(rotation->z);
	ofScale(scale, scale, scale);
	//ofScale(scaleXY->x, scaleXY->y, scaleXY->z);
	ofSetColor(255, 100);
	ofSetLineWidth(0.5);

	ofPushMatrix();
	ofScale(scaleXY->x, scaleXY->y, scaleXY->z);
	for(float x = level4->x; x <= -level4->x; x+= level4->x / -5.0f) {
		ofLine(x, level4->y, x, end->y);
	}
	for(float y = level4->y; y >= end->y; y+= (end->y - level4->y)/10.0f) {
		
		ofLine(level4->x, y, -level4->x, y);
	}
	
	
	ofPopMatrix();
	
	ofSetColor(0,255,0);
	ofPoint scalarXY = scaleXY.get(); 
	
	for(float angle = 0; angle>= -90; angle-=divAngle) {
			ofPushMatrix();
			ofRotateY( angle);
			ofScale(scaleXY->x, scaleXY->y, scaleXY->z);
			ofSetLineWidth(0.5);

			//ofBezier(start, c1, c2, end);
			ofSetLineWidth(3);
			
			ofCircle(level1, 1);
			ofCircle(level2, 1);
			ofCircle(level3, 1);
			ofCircle(level4, 1);

			ofPopMatrix();
			
			ofPushMatrix();
			ofRotateY( -180 - angle);
			ofScale(scaleXY->x, scaleXY->y, scaleXY->z);
			ofSetLineWidth(0.5);
			
			//ofBezier(start, c1, c2, end);
			ofSetLineWidth(3);
			
			ofCircle(level1, 1);
			ofCircle(level2, 1);
			ofCircle(level3, 1);
			ofCircle(level4, 1);
			
			ofPopMatrix();
			
	}

	ofPopStyle();
	ofPopMatrix();
	*/
	
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

