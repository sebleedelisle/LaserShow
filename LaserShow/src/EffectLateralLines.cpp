//
//  EffectLateralLines.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#include "EffectLateralLines.h"



void EffectLateralLines:: update() {

	if(domeData == NULL) return;
	
	for(int i = 0; i<lines.size(); i++) {
			
		lines[i].update();
		
		
	}
	
	
}

// also gonna need : LaserManager
void EffectLateralLines::draw(Synchroniser& sync, float volume, LaserManager& lm) {
	ofPolyline poly;
	
	
	if(domeData == NULL) return;
	
	// domeData gives us position, rotation, scale and bezier data
	

	if((sync.currentBeat ==0) && (sync.sixteenthTriggered)) {
		// make a new line!
		ofColor col;
		col.setHsb(hue,255,255);
		hue+=10;
		lines.push_back(LateralLine(0,0.7,col));
		if(hue>255) hue =0; 

	}

	// render all the lines
	
	
	for(int i = 0; i<lines.size(); i++) {
		
		LateralLine& line = lines[i];
		
		//ofSetColor(line.col);
		//ofNoFill();
		//ofSetLineWidth(5);
		if(line.pos>=1) {
			//line.pos = 1;
			//line.vel*=-1;
		}
		if(line.pos>1) {
			lines.erase(lines.begin() + i);
			i--;
			continue; 
		}
		ofPoint p = domeData->getBezierPoint(line.pos);
		// REUSE!
		poly.clear();
		for(float rotation = 0; rotation> -180; rotation--) {
			ofPoint q = p;
			q.rotate(rotation, ofPoint(0,1,0));
			q *= domeData->scaleXY;
			q.rotate(domeData->rotation->z, ofPoint(0,0,1));
			q.rotate(domeData->rotation->y, ofPoint(0,1,0));
			q.rotate(domeData->rotation->x, ofPoint(1,0,0));
			q *= domeData->scale;
			q += domeData->pos;
			
			//q+=ofPoint(640,480);
			
			poly.addVertex(q);
			//ofCircle(q,10);
			
		}
		//ofCircle(640,480,line.pos*100);
		//poly.draw();
		lm.addLaserPolyline(poly, new ColourSystem(line.col));
		
	}
	
	

}


void EffectLateralLines :: setDomeData(DomeData* domedata){
	domeData = domedata;
	
}
