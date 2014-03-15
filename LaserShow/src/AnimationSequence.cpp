//
//  AnimationSequence.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#include "AnimationSequence.h"

AnimationSequence::AnimationSequence () {
    
    //load type
    proximaNovaL.loadFont("Proxima Nova Light", 30, true, true);
	proximaNovaL.setLineHeight(62.0f);
	proximaNovaL.setLetterSpacing(1);
    proximaNovaL.setSpaceSize(.4);
    
    //load up images
    smashingTitle.loadImage("img/SmashingLogo.png");
	smashingTitle.setAnchorPercent(.5, .5);
}


void AnimationSequence :: update() {


}


void AnimationSequence:: draw(Synchroniser& sync, float volume) {

	
    ofPushStyle();
    
    //ofFill();
	//ofSetColor(255,0,0);
	    
	// pulse vars go from 0 to 1
//	ofCircle(100,100, sync.barPulse * 50);
//	ofCircle(200,100, sync.beatPulse * 50);
//	ofCircle(300,100, sync.eighthPulse * 50);
    //ofCircle(400,100, sync.sixteenthPulse * 50);
    
	// get bar / beat / note numbers :
	
	int bar = sync.currentBar;
	int beat = sync.currentBeat;
	int eighth = sync.current8th;
	int sixteenth = sync.current16th;
	
	// get bar as float :
    float barfloat = sync.currentBarFloat;
	
    //get some type set up
    ofTrueTypeFont::setGlobalDpi(72);
    

    // WHERE THE MAGIC HAPPENS
    if (bar < 1) {
        
        ofNoFill();
        smashingTitle.resize(80,80);
        smashingTitle.draw(0,0);
        //smashingTitle.draw(0,0, ofMap(sync.currentBarFloat,0,4,-100,100));
    }
    
    if (barfloat > 1 && barfloat <1.5) {
        
        //fake fade out our image!
        for (int i = 1024; i <0; i--) {
            ofSetColor(ofMap(i, 0, 1024, 0, 255));
        }
    }
    
    if (barfloat > 1.5 && bar < 4) {
        
        //fade in the text colour
        float op = 1;
        for (int i = 0; i < 255; i++) {
            ofSetColor(225, 255,255,op);
            op = i/2;
        }
        
       writeinPNL("MARCH 18 & 19");
        
    }
    
    if (barfloat > 2 && barfloat < 5) {
        //circle with guitar on qurts
        ofSetColor(ofColor::cyan);
        ofNoFill();
        
        ofCircle(100,300, ofMap(sync.sixteenthPulse, 0, 100, 10,100));
        
    }
    
    
    if (bar > 4 && bar < 8) {
        CurveSquare square;
        square.init(0,0,ofColor::pink);
        square.draw(sync.sixteenthPulse, false);
    
    }
    
    
    
    //center guide line
    //ofSetColor(255,0,0);
    //ofLine(0, -512,0, 512);
 
    ofPopStyle();

}

void AnimationSequence::writeinPNL(string message) {
    float halfWidth = proximaNovaL.stringWidth(message)/2;
    proximaNovaL.drawString(message, -1*halfWidth, 0);
}


