//
//  EffectParticles.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 16/03/2014.
//
//

#include "EffectParticles.h"


void EffectParticles :: makeParticleForPipe(int pipeindex) {
	if(pipeOrganData == NULL) return; 
	
	ParticleSystem &ps = *particleSystemManager.getParticleSystem();
	
	ParticleSystemSettings pss;
	pss.emitLifeTime = 0.1;
	pss.emitMode = PARTICLE_EMIT_BURST;
	pss.emitCount = 1;
	pss.renderer = new ParticleRendererLaserLine(10);
	pss.speedMin = 600 ;
	pss.speedMax = 650;
	pss.drag = 1;
	pss.gravity.set(0,500,0);
	
	pss.sizeStartMin = pss.sizeStartMax = 1;
	pss.sizeChangeRatio = 0.1;
	//pss.emitShape = &explodeMesh;
	pss.directionYVar = pss.directionZVar = 0;
	pss.directionX = -35;
	
	pss.hueStartMin = pss.hueStartMax = 0;
	pss.hueChange = 960;
	pss.saturationMin = pss.saturationMax = 255;
	pss.saturationEnd = 255;
	pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
	pss.lifeMin = pss.lifeMax = pipeindex%2 +1;
	pss.shimmerMin = 0;
	pss.timeSpeed = 0.9;
	//pss.doNotScale = true;
	
	ps.pos = pipeOrganData->pipes[pipeindex].top;
	ps.init(pss);
	
	
	
}

void EffectParticles:: makeRainbowBurst() {
	if(pipeOrganData == NULL) return; 
	
	float numpipes = pipeOrganData->pipes.size();
	
	
	for(int i =0; i<numpipes; i+=1) {
		makeParticleForPipe(i) ;
		
	}
	
	
}


void EffectParticles:: makeStarBurst() {
	
	if(pipeOrganData == NULL) return; 
	
	
	int numpipes = pipeOrganData->pipes.size();
	
	for(int i =0; i<numpipes; i+=1) {
		
		ParticleSystem &ps = *particleSystemManager.getParticleSystem();
		
		ParticleSystemSettings pss;
		pss.emitLifeTime = 0.1;
		//pss.emitMode = PARTICLE_EMIT_BURST;
		pss.emitCount = 20;
		pss.renderer = new ParticleRendererLaser();
		pss.speedMin = 2200 ;
		pss.speedMax = 3050;
		pss.drag = 0.90;
		pss.gravity.set(0,600,0);
		
		pss.sizeStartMin = pss.sizeStartMax = 1;
		pss.sizeChangeRatio = 0.5;
		//pss.emitShape = &explodeMesh;
		pss.directionYVar = pss.directionZVar = 0;
		pss.directionX = -35;
		pss.directionXVar = 20;
		pss.directionZVar = 5;
		
		pss.hueStartMin = pss.hueStartMax = 0;
		pss.hueChange = 0;
		pss.saturationMin = pss.saturationMax = 0;
		pss.saturationEnd = 0;
		pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
		pss.lifeMin = 2;
		pss.lifeMax = 3;
		pss.shimmerMin = 0;
		pss.timeSpeed = 0.5;
	
		pss.emitDelay = ofRandom(0.1);

		ps.pos = pipeOrganData->pipes[i].bottom;
		ps.init(pss);
	}
	
	
}


void EffectParticles ::  setObjects(PipeOrganData* pipeorgandata, DomeData* domedata) {
	pipeOrganData = pipeorgandata;
	domeData = domedata; 
	
}

