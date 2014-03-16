//
//  EffectDomeLines.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#include "EffectPipeOrganLines.h"



void EffectPipeOrganLines:: update(float deltaTime) {

	if(pipeOrganData == NULL) return;
	
	for(int i = 0; i<lines.size(); i++) {
			
		lines[i].update(deltaTime);
		
		
	}
	
	
}

// also gonna need : LaserManager
void EffectPipeOrganLines::draw(Synchroniser& sync, float volume, LaserManager& lm, float currentPeak) {
	ofPolyline poly;
	ofPushStyle(); 
	
	if(pipeOrganData == NULL) return;
	
	// domeData gives us position, rotation, scale and bezier data
	
	if(mode ==0) return;
	// MODE 1 is 4 bands on the first beat
	
	else if(mode ==1) {
		
		
		if(sync.beatTriggered) {//   ==0) && (sync.sixteenthTriggered)) {
			
			currentPipeIndex = 0;
		}
		int numpipes = pipeOrganData->pipes.size()/2;
		if(currentPipeIndex <= numpipes) {
		// make a new line!
			ofColor col;
			col.setHsb(hue,255,255);
			hue+=3;
			
			Pipe& pipe = pipeOrganData->pipes[numpipes + currentPipeIndex];
			lines.push_back(PipeOrganLine(pipe.top, pipe.bottom, col ));
	
			
			if(currentPipeIndex>0) {
				Pipe& pipe2 = pipeOrganData->pipes[numpipes - currentPipeIndex];
				lines.push_back(PipeOrganLine(pipe2.top, pipe2.bottom, col ));
							}
			
			if(hue>255) hue -= 255;
			currentPipeIndex++;
			
		}
	
		
		

		
	} else if((mode ==2) && (currentPeak>=0)) {
		
		
		int numpipes = pipeOrganData->pipes.size()/2;

		int pipeindex = currentPeak * numpipes;
		currentPipeIndex += (pipeindex-currentPipeIndex) *0.1;

		
		if((currentPipeIndex <= numpipes) ){//&&(sync.sixteenthTriggered)) {
			// make a new line!
			ofColor col;
			col.setHsb(hue,255,255);
			hue+=3;
			
			Pipe& pipe = pipeOrganData->pipes[numpipes + currentPipeIndex];
			lines.push_back(PipeOrganLine(pipe.top, pipe.bottom, col, 1,0,0,0,0.1 ));
			
		
			
			if(currentPipeIndex>0) {
				Pipe& pipe2 = pipeOrganData->pipes[numpipes - currentPipeIndex];
				lines.push_back(PipeOrganLine(pipe2.top, pipe2.bottom, col ));
				
			}

			
			if(hue>255) hue -= 255;
						
		}
		
		
	} 	
	for(int i = 0; i<lines.size(); i++) {
		
		PipeOrganLine& line = lines[i];
		
		if(line.elapsedTime>=line.duration) {
			lines.erase(lines.begin() + i);
			i--;
			continue;
		}
		ofSetColor(line.col);
		//ofLine(line.currentTop, line.currentBottom);
		lm.addLaserLineEased(line.currentTop, line.currentBottom, line.col);
	
	}
	
	ofPopStyle();

}


void EffectPipeOrganLines :: setObjects(PipeOrganData* pipeorgandata, ParticleSystemManager* psm ){
	pipeOrganData = pipeorgandata;
	particleSystemManager = psm; 
}
