//
//  LaserBeamEffect.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 12/03/2014.
//
//

#include "LaserBeamEffect.h"



LaserBeamEffect :: LaserBeamEffect() {
	
	speed = 1000;
	emitCount = 0;
	emitRate = 10;
	elapsedTime = 0;
	maxBeams = 50;
	running = true;


}


void LaserBeamEffect :: update(){

	float deltaTime = ofGetLastFrameTime();
	elapsedTime+=deltaTime;
	
	if((running) && (elapsedTime * emitRate > emitCount)) {
		
		// make a new one!
		beams.push_back(LaserBeam());
		LaserBeam& beam = beams.back();
		
		ofPoint pos(0,-ofRandom(200,300));
		pos.rotate(ofRandom(-130, 130), ofPoint(0,0,1));
		beam.pos.set(640,480,-2500);
		beam.pos+=pos;

		emitCount++;
	} else if(!running) {
		emitCount = elapsedTime * emitRate;
	}
	
	
	for(int i = 0; i<beams.size(); i++) {
			
		LaserBeam& beam = beams[i];
		
		beam.pos.z+=(speed*deltaTime);
		
		//if(beam.pos.z>0) {
		//	beam.pos.z =-2000;
		//}
		
		while(beams.size()>maxBeams) {
			beams.pop_front();
			//speed = 0;
		}
		
		while((beams.size()>0) && (beams.front().pos.z > 600)) {
			beams.pop_front();
		}
		
	}
	
}


void LaserBeamEffect :: draw(LaserManager& laserManager) {
	
	
	float xRotation = 20;
	float frontPlane = 300;
	float backPlane = -2500;

	ofPushMatrix();
	ofPushStyle();
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(1);
	
	for(int i = 0; i<beams.size(); i++) {
		
		LaserBeam& beam = beams[i];
	
		ofPoint start = beam.pos;
		ofPoint end = beam.pos;
		end.z-=300;
		
		
		if(start.z > frontPlane) start.z = frontPlane;
		if(end.z < backPlane) end.z = backPlane; 
		if(end.z<frontPlane) {
			start.rotate(xRotation, ofPoint(1,0,0));
			end.rotate(xRotation, ofPoint(1,0,0));
			
			laserManager.addLaserLineEased(start, end, ofColor::white);
			ofLine(start, end);//beam.pos, beam.pos + ofPoint(0,0,200));
		}
	}
	
	ofPopStyle(); 

	ofPopMatrix();

}