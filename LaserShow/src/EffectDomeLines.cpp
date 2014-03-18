//
//  EffectDomeLines.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#include "EffectDomeLines.h"

EffectDomeLines:: EffectDomeLines() {
	
	ringColours.push_back(ofColor::white);
	ringColours.push_back(ofColor::cyan);
	ringColours.push_back(ofColor::magenta);
	ringColours.push_back(ofColor(100,0,255));
	
}

void EffectDomeLines::setMode(int newmode) {
	if(mode == newmode) return;
	currentColourIndex = 0;
	mode = newmode;
	hue = 0;
	doSecondCircleRow = false;
  
}

void EffectDomeLines:: update(float deltaTime) {

	if(domeData == NULL) return;
	
	
	for(int i = 0; i<lines.size(); i++) {
			
		lines[i].update(deltaTime);
		
		
	}
	
	for(int i = 0; i<circles.size(); i++) {
		
		circles[i].update(deltaTime);
		if(circles[i].elapsedTime>circles[i].duration) {
			circles.erase(circles.begin() + i);
			i--;
	
		}
	}

	
	
}

// also gonna need : LaserManager
void EffectDomeLines::draw(Synchroniser& sync, float volume, LaserManager& lm) {
	ofPolyline poly;
	
	volumes.push_front(volume);
	if(volumes.size()>100) volumes.pop_back(); 
	
	if(domeData == NULL) return;
	
	// domeData gives us position, rotation, scale and bezier data
	
	//if(mode ==0) return;
	// MODE 1 is 4 bands on the first beat
	
	if(mode ==1) {
		
		if((sync.currentBeat ==0) && (sync.sixteenthTriggered)) {
			// make a new line!
			ofColor col = ringColours[currentColourIndex];
			//col.setHsb(255,255,255);
			//hue+=10;
			lines.push_back(DomeLine(1,1.5,col,true, -0.2, true));
			//lines.push_back(DomeLine(0.5,1,col, false, 1));
			//lines.push_back(DomeLine(0.5,1,col, false, 0));
			
			//if(hue>255) hue =0;
			
		}
		if((sync.beatTriggered) && (sync.currentBeat ==3)) {
			currentColourIndex = (currentColourIndex+1) % ringColours.size();
		}
		
	// spinny lines!
	}else if(mode ==2) {
		
		//if((sync.currentBeat <=1) &&
		 if  (sync.eighthTriggered) {
			// make a new line!
			ofColor col;
			col.setHsb(hue,255,255);
			hue+=10;
			
			// ORIGINAL WITH MULTI LINES :
			//lines.push_back(DomeLine(0,1,col));
			//lines.push_back(DomeLine(0.5,1,col, false, 1));
			//lines.push_back(DomeLine(0.5,1,col, false, 0));
			
			//lines.push_back(DomeLine(0,1,col));
			lines.push_back(DomeLine(0,2,col, false, 1));
			//lines.push_back(DomeLine(0.5,1,col, false, 0));
			
			
			if(hue>255) hue =0;
			
		}
		
		
	// BLIPPY CIRCLES
	} else if(mode == 3) {
		
		if((sync.sixteenthTriggered) && (volume>0.1)) {
			
			// make a flashy circle object
			ofPoint p = domeData->getBezierPoint(0.32);
			
			p.rotate(ofRandom(-40,-140), ofPoint(0,1,0));
			p *= domeData->scaleXY;
			p.rotate(domeData->rotation->z, ofPoint(0,0,1));
			p.rotate(domeData->rotation->y, ofPoint(0,1,0));
			p.rotate(domeData->rotation->x, ofPoint(1,0,0));
			p *= domeData->scale;
			p += domeData->pos;
			lm.addLaserSpiral(p, ofColor::white, 0, 120);
			
		}
//
//		for (float i = 0; i<4; i++) { //if((sixteenth>0) && (sixteenth<16)) {
//			poly.clear();
//			//int sixteenth = sync.current16th;;// -i;
//			//if((sixteenth - i<1) || (sixteenth - i>15))  continue;
//			//float size = 1;
//			//if((sixteenth == 2) || (sixteenth == 3) || (sixteenth == 5)  || (sixteenth == 6) || (sixteenth == 8) || (sixteenth == 10) || (sixteenth == 11) || (sixteenth == 14)){
//			//	size = 50;
//			//}
//			
//			float size = 50 * volume;
//			if(4-i<=volumes.size())
//				size = 50 * volumes[4-i];
//			
//			float rotation = ofMap(sync.barPulse, 0.5, 0, 0, -200) - (i*10);
//			if((rotation>0) || (rotation<-180)) continue;
//			
//			ofPoint p = domeData->getBezierPoint(0.34);
//			
//			// draw a circle
//			for(float angle = 0; angle< 360; angle +=5) {
//				ofPoint q(0,0,size);
//				
//				q.rotate(angle, ofPoint(1,0,0));
//				q.rotate(45,ofPoint(0,0,1));
//				q+=p;
//				
//				q.rotate(rotation, ofPoint(0,1,0));
//				q *= domeData->scaleXY;
//				q.rotate(domeData->rotation->z, ofPoint(0,0,1));
//				q.rotate(domeData->rotation->y, ofPoint(0,1,0));
//				q.rotate(domeData->rotation->x, ofPoint(1,0,0));
//				q *= domeData->scale;
//				q += domeData->pos;
//				poly.addVertex(q);
//			}
//			
//			lm.addLaserPolyline(poly, new ColourSystem());
//
//			
//			//lm.addLaserDot(p, ofColor::white);
//			//lm.addLaserCircle(p, ofColor::white, size*sync.sixteenthPulse);
			
	//	}
		
	} else if (mode ==4) {
		
		//expanding arrows
		
		float totalshapes = 5;
        float progress = ofMap(sync.barPulse, 1,0.875, 0, 1, true);
		
        float endshapes = floor(progress * totalshapes);
		float startshapes = floor(ofMap(sync.barPulse, 0.75,0.5, 0,totalshapes, true));
		
		ofPoint centre(675,640);
		ofPoint left = centre + ofPoint(-140,140);
		ofPoint right = centre + ofPoint(140,140);
		float colourOffset = ofMap(sync.barPulse, 1, 0, 0, 100);
		ofColor c; 
		for(int i = startshapes; i<endshapes; i++) {
            c.setHsb((int)(colourOffset + 200-i*12)%255, 255, 255);
			//ofSetColor(c);
			
			ofPoint offset(0,i*-40);
			lm.addLaserLineEased( left + offset, centre+offset, c);
			lm.addLaserLineEased(centre + offset, right + offset, c);
			
		}
			
			
	} else if (mode ==5) {
					
		//marching circles
		
		
		if(sync.beatTriggered) {
			circles.push_front(MarchingCircle());
			MarchingCircle& circle = circles.front();
			
			circle.startAngle = circle.currentAngle = -170;
			circle.targetAngle = -10;
			circle.duration = 1/sync.tempo * 60 * 8;
			
			ofColor col;
			col.setHsb(hue,255,255);
			
			circle.col = col;
			circle.bezierPosition = 0.25;
			
			if(doSecondCircleRow) {
				circles.push_front(MarchingCircle());
				MarchingCircle& circle2 = circles.front();
			
				circle2.startAngle = circle2.currentAngle = -10;
				circle2.targetAngle = -170;
				circle2.duration = 1/sync.tempo * 60 * 8;
			
				col.setHsb(hue,255,255);
			
				circle2.col = col;
				circle2.bezierPosition = 0.35;
			}
			
			hue-=2;
			if(hue<0) hue = 255;
		}
		/*
		for (float i = 0; i<4; i++) { //if((sixteenth>0) && (sixteenth<16)) {
			poly.clear();
			//int sixteenth = sync.current16th;;// -i;
			//if((sixteenth - i<1) || (sixteenth - i>15))  continue;
			//float size = 1;
			//if((sixteenth == 2) || (sixteenth == 3) || (sixteenth == 5)  || (sixteenth == 6) || (sixteenth == 8) || (sixteenth == 10) || (sixteenth == 11) || (sixteenth == 14)){
			//	size = 50;
			//}
			
			float size = 50 * volume;
			if(4-i<=volumes.size())
				size = 100 * volumes[4-i];
			
			float rotation = ofMap(sync.barPulse, 0.5, 0, 0, -140) - (i*10);
			if((rotation>0) || (rotation<-180)) continue;
			
			ofPoint p = domeData->getBezierPoint(0.34);
			
			// draw a circle
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
		

		 */ 
	
		
		
	}
	
	
	// render all the lines	
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
			for(float t = 0; t<0.45; t+=0.01) {
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
	
	// render all the circles!
	
	for(int i = 0; i<circles.size(); i++) {
		poly.clear();
		
		MarchingCircle& circle = circles[i];
		ofPoint p = domeData->getBezierPoint(circle.bezierPosition);
		
		for(float angle = 0; angle<=360; angle +=5) {
			ofPoint q(0,0,(volume+sync.beatPulse)/2*circle.size*0.5);
			
			q.rotate(angle, ofPoint(1,0,0));
			q.rotate(45,ofPoint(0,0,1));
			q+=p;
			
			q.rotate(circle.currentAngle, ofPoint(0,1,0));
			q *= domeData->scaleXY;
			q.rotate(domeData->rotation->z, ofPoint(0,0,1));
			q.rotate(domeData->rotation->y, ofPoint(0,1,0));
			q.rotate(domeData->rotation->x, ofPoint(1,0,0));
			q *= domeData->scale;
			q += domeData->pos;
			poly.addVertex(q);
		}
//		
//		lm.addLaserPolyline(poly, new ColourSystem(circle.col));
//		
//		 poly.clear();
//		for(float angle = 0; angle<=360; angle +=5) {
//			ofPoint q(0,0,sync.beatPulse*circle.size);
//			
//			q.rotate(angle, ofPoint(1,0,0));
//			q.rotate(45,ofPoint(0,0,1));
//			q+=p;
//			
//			q.rotate(circle.currentAngle, ofPoint(0,1,0));
//			q *= domeData->scaleXY;
//			q.rotate(domeData->rotation->z, ofPoint(0,0,1));
//			q.rotate(domeData->rotation->y, ofPoint(0,1,0));
//			q.rotate(domeData->rotation->x, ofPoint(1,0,0));
//			q *= domeData->scale;
//			q += domeData->pos;
//			poly.addVertex(q);
//		}
		
		lm.addLaserPolyline(poly, new ColourSystem(circle.col));
		
		
		
		
	}

}


void EffectDomeLines :: setDomeData(DomeData* domedata){
	domeData = domedata;
	
}
