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
void EffectPipeOrganLines::setMode(int newmode) {
	if(mode == newmode) return;
	mode = newmode;
	hue = 0; 
	
}
// also gonna need : LaserManager
void EffectPipeOrganLines::draw(Synchroniser& sync, float volume, LaserManager& lm, float currentPeak) {

	
	if(pipeOrganData == NULL) return;
	
	// domeData gives us position, rotation, scale and bezier data
	
	//if(mode ==0) return;
	// MODE 1 is 4 bands on the first beat
	
	ofPolyline poly;
	ofPushStyle();
	
	if(mode ==1) {
		
		
		if(sync.beatTriggered) {//   ==0) && (sync.sixteenthTriggered)) {
			
			currentPipeIndex = 0;
		}
		int numpipes = pipeOrganData->pipes.size()/2;
		if(currentPipeIndex <= numpipes) {
		// make a new line!
			ofColor col;
			col.setHsb((int)hue%255,255,255);
			hue+=3;
			PipeOrganLine& line = lines[numpipes+currentPipeIndex];
			line.set( col, 1,0,1,1,0.2 );
			
			
			if(currentPipeIndex>0) {
				PipeOrganLine& line2 = lines[numpipes - currentPipeIndex];
				//Pipe& pipe2 = pipeOrganData->pipes[numpipes - currentPipeIndex];
				line2.set(col, 1,0,1,1,0.2 );
				
			

			}
			
			//if(hue>255) hue -= 255;
			currentPipeIndex++;
			
		}
	
		
		

		
	} else if((mode ==2) && (currentPeak>=0)) {
		
		
		int numpipes = pipeOrganData->pipes.size()/2;

		int pipeindex = currentPeak * numpipes*1.7;
		currentPipeIndex += (pipeindex-currentPipeIndex) *0.1;

		
		if((currentPipeIndex <= numpipes) ){//&&(sync.sixteenthTriggered)) {
			// make a new line!
			ofColor col;
			col.setHsb((int)hue%255,255,255);
			hue+=3;
			
			//Pipe& pipe = pipeOrganData->pipes[numpipes + currentPipeIndex];
			//lines.push_back(PipeOrganLine(pipe.top, pipe.bottom, col, 1,0,0,0,0.1 ));
			PipeOrganLine& line = lines[numpipes+currentPipeIndex];
			
			
			if(line.elapsedTime > line.duration) makeParticleForPipe(numpipes+currentPipeIndex, col) ;
			line.set( col, 1,0,1,1,0.2 );
			   
			if(currentPipeIndex>0) {
				PipeOrganLine& line2 = lines[numpipes - currentPipeIndex];
				//Pipe& pipe2 = pipeOrganData->pipes[numpipes - currentPipeIndex];
				if(line2.elapsedTime > line2.duration) makeParticleForPipe(numpipes - currentPipeIndex, col) ;
				
				line2.set(col, 1,0,1,1,0.2 );
				
			}

			
			//if(hue>255) hue -= 255;
						
		}
		
	
	} else if(mode ==3) {
		//DRUM BEAT MODE
		
		
		if((sync.beatTriggered) && (sync.currentBeat%2==0)) {
			lines[0].set(ofColor::magenta, 0.75, 0.25, 0.5, 0.5,0.1);
			lines[1].set(ofColor::magenta, 1, 0, 0.5, 0.5,0.2);
			lines[2].set(ofColor::magenta, 0.75, 0.25, 0.5, 0.5,0.1);
			
		}
		if((sync.beatTriggered) && (sync.currentBeat%2==1)) {
			lines[lines.size()-1].set(ofColor::cyan, 0.75, 0.25, 0.5, 0.5,0.1);
			lines[lines.size()-2].set(ofColor::cyan, 1, 0, 0.5, 0.5,0.2);
			lines[lines.size()-3].set(ofColor::cyan, 0.75, 0.25, 0.5, 0.5,0.1);
		}
		if(sync.sixteenthTriggered) {
			//lines[lines.size()/2 -1].set(ofColor::red, 0.75, 0.25, 0.5, 0.5,0.05);
			lines[lines.size()/2 + sync.current16th -8 ].set(ofColor(100,0,255), 1, 0, 1, 1,0.1);
			//lines[lines.size()/2 + 1].set(ofColor::red, 0.75, 0.25, 0.5, 0.5,0.05);
			
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	for(int i = 0; i<lines.size(); i++) {
		
		PipeOrganLine& line = lines[i];	
		
		if(line.elapsedTime>=line.duration) {
			continue;
		}
		ofSetColor(line.col);
		//ofLine(line.currentTop, line.currentBottom);
		lm.addLaserLineEased(line.currentTop, line.currentBottom, line.col);
	
	}
	
	ofPopStyle();

}


void EffectPipeOrganLines :: makeParticleForPipe(int pipeindex, ofColor col) {
	if(pipeOrganData == NULL) return;
	
	ParticleSystemManager& psm = *(ParticleSystemManager::instance());
	ParticleSystem &ps = *psm.getParticleSystem();
	
	ParticleSystemSettings pss;
	pss.emitLifeTime = 0.1;
	pss.emitMode = PARTICLE_EMIT_BURST;
	pss.emitCount = 1;
	pss.renderer = new ParticleRendererLaser();
	pss.speedMin = 600 ;
	pss.speedMax = 650;
	pss.drag = 0.9;
	//pss.gravity.set(0,500,0);
	
	pss.sizeStartMin = pss.sizeStartMax = 1;
	pss.sizeChangeRatio = 0.1;
	//pss.emitShape = &explodeMesh;
	pss.directionYVar = pss.directionZVar = 0;
	pss.directionY = 0;
	pss.directionX = -35;
	
	pss.hueStartMin = pss.hueStartMax = col.getHue();
	pss.hueChange = 0;
	pss.saturationMin = pss.saturationMax = 255;
	pss.saturationEnd = 255;
	pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
	pss.lifeMin = pss.lifeMax = 0.5;
	pss.shimmerMin = 0;
	pss.timeSpeed = 0.7;
	//pss.doNotScale = true;
	
	ps.pos = pipeOrganData->pipes[pipeindex].top;
	ps.init(pss);
	
	
	
}

void EffectPipeOrganLines :: setObjects(PipeOrganData* pipeorgandata, ParticleSystemManager* psm ){
	pipeOrganData = pipeorgandata;
	particleSystemManager = psm;
	
	lines.clear();
	for(int i = 0; i<pipeOrganData->pipes.size(); i++) {
		Pipe& pipe = pipeOrganData->pipes[i];
		lines.push_back(PipeOrganLine(pipe.top, pipe.bottom, ofColor::white));
	}
	
	
}
