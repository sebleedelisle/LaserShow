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
    proximaNovaL.loadFont("Proxima Nova Light", 26, true, true);
	proximaNovaL.setLineHeight(62.0f);
	proximaNovaL.setLetterSpacing(1);
    proximaNovaL.setSpaceSize(.4);
    
    //load up images
    smashingTitle.loadImage("img/SmashingLogo.png");
	smashingTitle.setAnchorPercent(.5, .5);
    
    ofSetLineWidth(2);
    
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
    if (barfloat >0 && barfloat <0.25) {
        smashingTitle.resize(30,30);
        smashingTitle.draw(0,0);
    }
    
    if (barfloat >0.5 && barfloat <1) {
        smashingTitle.resize(30,30);
        smashingTitle.draw(0,0);
    }
    
    if (barfloat > 0.25 && barfloat < 1) {
        //fake fade out our image!
        for (int i = 1024; i <0; i--) {
            ofSetColor(ofMap(i, 0, 1024, 0, 255));
        }
    }
    
    if (barfloat > 1 && bar < 3) {
        
        //fade in the text colour
        float op = 1;
        for (int i = 0; i < 1024; i++) {
            ofSetColor(225, 255,255,op);
            op = i;
        }
        
       writeinPNL("MARCH 18 & 19");
        
    }
    
    if (bar >= 3 && bar < 4) {
        float op = 255;
        for (int i = 255; i > 0; i--) {
            ofSetColor(225, 255,255,op);
            op = i;
        }
        
        writeinPNL("MARCH 18 & 19");

    }
    
    
    if (barfloat >= 3 && bar < 6) {
        
        //fade in the text colour
        float op = 1;
        for (int i = 0; i < 1024; i++) {
            ofSetColor(225, 255,255,op);
            op = i;
        }
        
        writeinPNL("#SMASHINGCONF");
        
    }
    
    if (bar >= 6 && bar < 7) {
        float op = 255;
        for (int i = 255; i > 0; i--) {
            ofSetColor(225, 255,255,op);
            op = i;
        }
        
        writeinPNL("#SMASHINGCONF");
        
    }

    
    if (barfloat > 1 && barfloat < 5) {
        //circle with guitar on qurts
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(100,200, ofMap(sync.beatPulse, 0, 1, 0,25));
    }
    
    if (barfloat >= 1.25 && barfloat < 2) {
        // square with eighths - harmonica
        ofSetColor(ofColor::yellow);
        ofNoFill();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(250,-200, ofMap(sync.eighthPulse, 0, 1, 5,25),ofMap(sync.eighthPulse, 0, 1, 10,25));
    }
    
    if (barfloat > 2.5 && barfloat < 3) {
        // square with eighths - harmonica
        ofSetColor(ofColor::yellow);
        ofNoFill();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(250,-200, ofMap(sync.eighthPulse, 0, 1, 5,25),ofMap(sync.eighthPulse, 0, 1, 10,25));
    }
    
    if (barfloat >= 3 && barfloat < 6) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(-50, -150, ofMap(sync.beatPulse, 0, 1, 5,25));
    }
    
    if (barfloat >= 3.25 && barfloat < 3.5) {
        //vocals
        CurveSquare square;
        square.init(-300,-75,ofColor::pink);
        square.draw(sync.beatPulse, false);
    }
    
    if (barfloat >= 3.5 && barfloat < 3.75) {
        //vocals
        CurveSquare square;
        square.init(-300,-75,ofColor::pink);
        square.draw(sync.eighthPulse, false);
    }
    
    if (barfloat >= 3.75 && barfloat < 4.5) {
        //vocals
        CurveSquare square;
        square.init(-300,-75,ofColor::pink);
        square.draw(sync.beatPulse*2, false);
        
        if (sync.currentBeat > 3) {
            ofFill();
            ofSetColor(255);
            ofRect(0,0,200,200);
            square.draw(2, false);
        }

}
    
    
    //4 step up gutiar
    if (barfloat >=6 && barfloat < 8) {
        //orange to keep the beat throughout the two 4 seps
        ofSetColor(ofColor::orange);
        ofNoFill();
        ofCircle(0,0, ofMap(sync.beatPulse, 0, 1, 10,35));
    }
    
    if (barfloat >= 6 && barfloat < 6.25) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0, ofMap(sync.eighthPulse, 0, 1, 10,35));
    }
    
    if (barfloat >= 6.25 && barfloat < 6.25) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0, 35);
        ofCircle(0,0, ofMap(sync.beatPulse, 0, 1, 20,65));
    }
    
    if (barfloat >= 6.5 && barfloat < 6.5) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0, 35);
        ofCircle(0,0, 65);
    }
    
    if (barfloat >= 6.75 && barfloat < 7) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0, 35);
        ofCircle(0,0, 65);
        ofCircle(0,0, ofMap(sync.beatPulse, 0, 1, 40,85));
        
         if (sync.currentBeat > 2) {
            ofSetColor(ofColor::orange);
             ofCircle(0,0, 100);
         }
    }
    
    //second 4 step up guitar
    if (barfloat >= 7 && barfloat < 7.25) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(-0,0, ofMap(sync.eighthPulse, 0, 1, 10,35));
    }
    
    if (barfloat >= 7.25 && barfloat < 7.25) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0, 35);
        ofCircle(0,0, ofMap(sync.beatPulse, 0, 1, 20,65));
    }
    
    if (barfloat >= 7.5 && barfloat < 7.75) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0, 35);
        ofCircle(0,0, 65);
    }

    
    if (barfloat >= 7.75 && barfloat < 8) {
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0, 35);
        ofCircle(0,0, 65);
        ofCircle(0,0, ofMap(sync.beatPulse, 0, 1, 40,85));
        
        if (sync.currentBeat > 1) {
            ofSetColor(ofColor::orange);
            ofCircle(0,0, 100);
            
            ofSetColor(ofColor::purple);
            ofCircle(0,0, 85);
        }
    }
    
//    if (bar >=8 && barfloat < 8.25) {
//        //four shapes in the center
//        ofSetColor(ofColor::cyan);
//        ofNoFill();
//        ofCircle(0,0,30);
//        ofCircle(0,0,30);
//        
//        ofSetRectMode(OF_RECTMODE_CENTER);
//        ofRect(0,0,60,60);
//        ofRect(0,0,60,60);
//    }
    
    if (barfloat >=8 && barfloat < 8.25) {
        //four shapes to corner
        ofSetColor(ofColor::cyan);
        ofNoFill();
        float progress = ofMap(barfloat, 8, 8.25, 0,1);
        
        progress*=progress;
        progress*=progress;
    
       
        ofPoint circlePos(200,200);
        circlePos *=progress;
        ofCircle(circlePos, 30);
        
        ofPoint circle2Pos(-200,-200);
        circle2Pos *=progress;
        ofCircle(circle2Pos, 30);
        
         ofSetRectMode(OF_RECTMODE_CENTER);
        ofPoint rectPos(200,-200);
        rectPos *=progress;
        ofRect(rectPos, 60,60);
        
        ofPoint rect2Pos(-200,200);
        rect2Pos *=progress;
        ofRect(rect2Pos, 60,60);
        ofFill();
        ofSetColor(0, 0, 0);
        ofRect(rect2Pos, 60,60);
    }
    
    if (barfloat >=8.25 && barfloat < 8.75) {
        //four shapes in center
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(200,200,30);
        ofCircle(-200,-200,30);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(200,-200,60,60);
        ofRect(-200,200,60,60);
    }
    
    
    if (bar >=8.5 && barfloat < 8.75) {
        //four shapes turn colour and back out to corners
        
    }
    
    
//    //grow circles
//    if (bar >=8 && barfloat < 8.25) {
//        ofNoFill();
//        ofSetColor(ofColor::cyan);
//        ofCircle(-0,0, sync.barPulse *60);
//        ofSetColor(ofColor::pink);
//        ofCircle(0,0, sync.barPulse *80);
//        ofSetColor(255,0,111);
//        ofCircle(0,0, sync.barPulse*100);
//    }
//   
//    //hold circles
//    if (barfloat >= 8.25 && barfloat < 8.5){
//        ofNoFill();
//        ofSetColor(ofColor::cyan);
//        ofCircle(0,0,60);
//        ofSetColor(ofColor::pink);
//        ofCircle(0,0,80);
//        ofSetColor(255,0,111);
//        ofCircle(0,0, 100);
//    }
//    
//    if (barfloat >= 8.5 && barfloat < 9){
//        CurveSquare square;
//        square.init(0,0, ofColor::cyan);
//        square.draw(2, false);
//    
//        CurveSquare square2;
//        square2.init(0,0, ofColor::pink);
//        square2.draw(3, false);
//        
//        CurveSquare square3;
//        square3.init(0,0, ofColor(255,0,111));
//        square3.draw(4, false);
//    }
    

    
//    if (bar > 7 && bar < 8) {
//        CurveSquare square;
//        square.init(0,0,ofColor::pink);
//        square.draw(sync.sixteenthPulse, false);
//    }
    
    
    
    //center guide line
    //ofSetColor(255,0,0);
    //ofLine(0, -512,0, 512);
 
    ofPopStyle();

}

void AnimationSequence::writeinPNL(string message) {
    float halfWidth = proximaNovaL.stringWidth(message)/2;
    proximaNovaL.drawString(message, -1*halfWidth, 0);
}


