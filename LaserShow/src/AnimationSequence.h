//
//  AnimationSequence.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#pragma once 

#include "ofMain.h"
#include "Synchroniser.h"
#include "CurveSquare.h"
#include "ArrowShape.h"
#include "OctoplusShape.h"
#include "SoundShape.h"



class AnimationSequence {
	

	public :
	
	void update();
	void draw(Synchroniser& sync, float volume);
    void writeinPNL(string message);
    
    ofTrueTypeFont	proximaNovaL;
    ofTrueTypeFont	proximaNovaLB;
    ofImage smashingTitle;
    
    float hue;
    
	ArrowShape arrow;
    CurveSquare square;
    OctoplusShape octo;
    
    AnimationSequence();
	
	deque<float> volumes; 
    
	
	
	
	
};

