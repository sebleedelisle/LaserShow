//
//  EffectLaserBeams.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 12/03/2014.
//
//

#include "EffectLaserBeams.h"



EffectLaserBeams :: EffectLaserBeams() {
	
	speed = 1000;
	emitCount = 0;
	emitRate = 5;
	elapsedTime = 0;
	maxBeams = 50;
	//running = false;
	multiColoured = true;
	currentHue = 0;
	rotateEmission = true;
	currentAngle = 0;
	respondToVolume = true;
	

}


void EffectLaserBeams :: update(float deltaTime){

	//float deltaTime = ofGetLastFrameTime();
	elapsedTime+=deltaTime;
	
	if(mode == 1) {
		multiColoured = false;
		rotateEmission = false;
		respondToVolume = false;
	} else if (mode ==2) {
		
		multiColoured = true;
		rotateEmission = true;
		respondToVolume = true;
	}
	
	if((mode>0) && (elapsedTime * emitRate > emitCount)) {
		
		// make a new one!
		beams.push_back(LaserBeam());
		LaserBeam& beam = beams.back();
		
		if(multiColoured) {
			beam.hue = currentHue;
			beam.saturation = 255;
			currentHue += 3;
		}
		
		ofPoint pos(0,-ofRandom(400,400));
		if(rotateEmission) {
			pos.rotate(currentAngle, ofPoint(0,0,1));
			currentAngle += 22;
			if(currentAngle>120) currentAngle -=240;
			
		} else {
			pos.rotate(ofRandom(-120, 120), ofPoint(0,0,1));
		}
			
			
		beam.pos.set(640,480,-2500);
		beam.pos+=pos;

		emitCount++;
	} else if(mode == 0) {
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


void EffectLaserBeams :: draw(LaserManager& laserManager, float intensity) {
	
	
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
	
		if(i<beams.size()-1) {
			beam.intensity = beams[i+1].intensity;
		} else {
			if(respondToVolume) beam.intensity = intensity;
			else beam.intensity = 0;
		}
		
		ofPoint start = beam.pos;
		ofPoint end = beam.pos;
		end.z-=beam.length;
		
		//if(intensity>0.6) {
			float scalar = ofMap(beam.intensity, 0,1, 0,1, true);
			start.z+=scalar*beam.length;
			end.z-=scalar*beam.length;
			
			
		//}
		
		
		if(start.z > frontPlane) start.z = frontPlane;
		if(end.z < backPlane) end.z = backPlane; 
		if(end.z<frontPlane) {
			start.rotate(xRotation, ofPoint(1,0,0));
			end.rotate(xRotation, ofPoint(1,0,0));
			ofColor col;
			col.setHsb(beam.hue, beam.saturation, 255);
			if(multiColoured) col.setSaturation(ofMap(beam.intensity, 0,1,beam.saturation, beam.saturation*0.5,true));
			//col.setHsb(beam.colour.getHue(), 255, ofMap(intensity, 0,1,255,255,true));
			
			laserManager.addLaserLineEased(start, end, col);
			//ofSetColor(col);
			//ofLine(start, end);//beam.pos, beam.pos + ofPoint(0,0,200));
		}
	}
	
	ofPopStyle(); 

	ofPopMatrix();

}