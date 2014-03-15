//
//  EffectDomeLines.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#include "EffectDomeLines.h"



void EffectDomeLines:: update() {

	if(domeData == NULL) return;
	
	for(int i = 0; i<lines.size(); i++) {
			
		lines[i].update();
		
		
	}
	
	
}

// also gonna need : LaserManager
void EffectDomeLines::draw(Synchroniser& sync, float volume, LaserManager& lm) {
	ofPolyline poly;
	
	
	if(domeData == NULL) return;
	
	// domeData gives us position, rotation, scale and bezier data
	

	if((sync.currentBeat ==0) && (sync.sixteenthTriggered)) {
		// make a new line!
		ofColor col;
		col.setHsb(hue,255,255);
		hue+=10;
		lines.push_back(DomeLine(0,0.7,col));
		lines.push_back(DomeLine(0,0.7,col, false));

		if(hue>255) hue =0; 

	}

	// render all the lines
	
	
	for(int i = 0; i<lines.size(); i++) {
		
		DomeLine& line = lines[i];
		
		if(line.pos>1) {
			lines.erase(lines.begin() + i);
			i--;
			continue; 
		}
		
		// REUSE!
		poly.clear();
		
		if(line.lateral) {
			
			ofPoint p = domeData->getBezierPoint(line.pos);
			
			for(float rotation = 0; rotation> -180; rotation-=3) {
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
		} else {
			for(float t = 0; t<1; t+=0.01) {
				ofPoint q = domeData->getBezierPoint(t);;
				q.rotate(line.pos * -180, ofPoint(0,1,0));
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
			
			
		}
		//ofCircle(640,480,line.pos*100);
		//poly.draw();
		lm.addLaserPolyline(poly, new ColourSystem(line.col));
		
	}
	
	

}


void EffectDomeLines :: setDomeData(DomeData* domedata){
	domeData = domedata;
	
}
