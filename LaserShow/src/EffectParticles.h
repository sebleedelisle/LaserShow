//
//  EffectParticles.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 16/03/2014.
//
//

#pragma once
#include "ParticleSystemManager.h"
#include "ParticleRendererLaser.h"
#include "ParticleRendererLaserLine.h"
#include "PipeOrganData.h"
#include "DomeData.h"


class EffectParticles {

	public : 
	EffectParticles() : particleSystemManager(*ParticleSystemManager::instance()){};

	void update();
	
	void draw();

	void makeParticleForPipe(int pipeindex);
	
	void makeRainbowBurst();
	void makeStarBurst(float timespeed = 0.5);
	
	void setObjects(PipeOrganData* pipeorgandata, DomeData* domedata); 


	ParticleSystemManager& particleSystemManager;
	PipeOrganData* pipeOrganData = NULL;
	DomeData* domeData = NULL;

};