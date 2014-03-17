//
//  EffectDomeLines.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#include "EffectDomeLines.h"



void EffectDomeLines:: update(float deltaTime) {

	if(domeData == NULL) return;
	
	
	for(int i = 0; i<lines.size(); i++) {
			
		lines[i].update(deltaTime);
		
		
	}
	
	
}

// also gonna need : LaserManager
void EffectDomeLines::draw(Synchroniser& sync, float volume, LaserManager& lm) {
	ofPolyline poly;
	
	
	if(domeData == NULL) return;
	
	// domeData gives us position, rotation, scale and bezier data
	
	if(mode ==0) return;
	// MODE 1 is 4 bands on the first beat
	
	else if(mode ==1) {
		
		if((sync.currentBeat ==0) && (sync.sixteenthTriggered)) {
			// make a new line!
			ofColor col = ofColor::white;
			//col.setHsb(255,255,255);
			hue+=10;
			lines.push_back(DomeLine(1,1.5,col,true, -0.2, true));
			//lines.push_back(DomeLine(0.5,1,col, false, 1));
			//lines.push_back(DomeLine(0.5,1,col, false, 0));
			
			if(hue>255) hue =0;
			
		}
		
		
	}else if(mode ==2) {
		
		if((sync.currentBeat ==0) && (sync.sixteenthTriggered)) {
			// make a new line!
			ofColor col;
			col.setHsb(hue,255,255);
			hue+=10;
			lines.push_back(DomeLine(0,1,col));
			lines.push_back(DomeLine(0.5,1,col, false, 1));
			lines.push_back(DomeLine(0.5,1,col, false, 0));
			
			if(hue>255) hue =0;
			
		}
		
	// BLIPPY CIRCLES
	} else if(mode == 3) {
		
		
		for (float i = -1.5; i<2.5; i++) { //if((sixteenth>0) && (sixteenth<16)) {
			poly.clear();
			int sixteenth = sync.current16th;;// -i;
			if((sixteenth - i<1) || (sixteenth - i>15))  continue;
			float size = 1;
			if((sixteenth == 2) || (sixteenth == 3) || (sixteenth == 5)  || (sixteenth == 6) || (sixteenth == 8) || (sixteenth == 10) || (sixteenth == 11) || (sixteenth == 14)){
				size = 50;
			}
	
			
			float rotation = ofMap(sync.barPulse + ((float)i/16.0f), 1, 0, 0, -180); 
			ofPoint p = domeData->getBezierPoint(0.34);
			
			for(float angle = 0; angle< 360; angle +=5) {
				ofPoint q(0,0,size*sync.sixteenthPulse);
				
				q.rotate(angle, ofPoint(1,0,0));
				q.rotate(45,ofPoint(0,0,1));
				q+=p;
				
				q.rotate(rotation, ofPoint(0,1,0));
				q *= domeData->scaleXY;
				q.rotate(domeData->rotation->z, ofPoint(0,0,1));
				q.rotate(domeData->rotation->y, ofPoint(0,1,0));
				q.rotate(domeData->rotation->x, ofPoint(1,0,0));
				q *= domeData->scale;
				q += domeData->pos;
				poly.addVertex(q);
			}
			
			lm.addLaserPolyline(poly, new ColourSystem());

			
			//lm.addLaserDot(p, ofColor::white);
			//lm.addLaserCircle(p, ofColor::white, size*sync.sixteenthPulse);
			
		}
		
	} else if (mode ==4) {
		
		//expanding arrows
		
		float totalshapes = 8;
        float progress = ofMap(sync.barPulse, 1,0.75, 0, 1, true);
		
        float endshapes = floor(progress * totalshapes);
		float startshapes = floor(ofMap(sync.barPulse, 0.75,0.5, 0,totalshapes, true));
		ofPoint centre(680,780);
		ofPoint left = centre + ofPoint(-200,200);
		ofPoint right = centre + ofPoint(200,200);
		
		ofColor c; 
		for(int i = startshapes; i<endshapes; i++) {
            c.setHsb(255-i*12, 255, 255);
			//ofSetColor(c);
			
			ofPoint offset(0,i*-50);
			lm.addLaserLineEased( left + offset, centre+offset, c);
			lm.addLaserLineEased(centre + offset, right + offset, c);
			
			
			
			
		}

		
		
		
	}
	
	
	// render all the lines
	// THIS SHOULD COME OUT OF THE CONDITIONAL!
	
	for(int i = 0; i<lines.size(); i++) {
		
		DomeLine& line = lines[i];
		
		if(line.elapsedTime>=line.timeToTarget) {
			lines.erase(lines.begin() + i);
			i--;
			continue;
		}
		
		// REUSE!
		poly.clear();
		
		if(line.lateral) {
			
			ofPoint p = domeData->getBezierPoint(line.pos);
			
			for(float rotation = 0; rotation>= ((line.fullCircle)? -360 : -180); rotation-=3) {
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
				ofPoint q = domeData->getBezierPoint(t);
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
