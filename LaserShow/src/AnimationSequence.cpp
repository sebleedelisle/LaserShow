//
//  AnimationSequence.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 15/03/2014.
//
//

#include "AnimationSequence.h"

void AnimationSequence :: update() {


}


void AnimationSequence:: draw(Synchroniser& sync, float volume) {

	ofPushStyle();
    
    ofSetColor(0,255,0);
    ofLine(0, -512,0, 512);
    
	ofFill();
	ofSetColor(255,0,0);
	    
	// pulse vars go from 0 to 1
//	ofCircle(100,100, sync.barPulse * 50);
//	ofCircle(200,100, sync.beatPulse * 50);
//	ofCircle(300,100, sync.eighthPulse * 50);
    ofCircle(400,100, sync.sixteenthPulse * 50);
    
	// get bar / beat / note numbers :
	
	int bar = sync.currentBar;
	int beat = sync.currentBeat;
	int eighth = sync.current8th;
	int sixteenth = sync.current16th;
	
	// get bar as float :
    float barfloat = sync.currentBarFloat;
	
    //get some type set up
    ofTrueTypeFont::setGlobalDpi(72);
    
	proximaNovaL.loadFont("Proxima Nova Light", 30, true, true);
	proximaNovaL.setLineHeight(62.0f);
	proximaNovaL.setLetterSpacing(1);
    
    
    // THE BIG-ASS CONDITIONAL
    if (bar >1 && bar < 20) {
        ofSetColor(225);
        string fontString ="HEY I HAVE SOME FONT STUFFS!";
        proximaNovaL.drawString(fontString, -350, 0);
    }
    
    if (bar >8 && bar < 9) {
        CurveSquare square;
        square.init(0,0,ofColor::pink);
        square.draw(sync.sixteenthPulse, false);
    
    }
 
    
    
    
    
  
    

    
 
    
    ofPopStyle();

}




