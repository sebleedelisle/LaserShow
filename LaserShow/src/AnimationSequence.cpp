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
    ofNoFill();
    
    hue = 50;
    
}


void AnimationSequence :: update() {


}


void AnimationSequence:: draw(Synchroniser& sync, float volume) {

    float startAngle = -40;
    
    ofPushStyle();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(36);
  
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
      //  smashingTitle.resize(30,30);
        //smashingTitle.draw(0,0);
    }
    
    if (barfloat >0.5 && barfloat <1) {
        //smashingTitle.resize(30,30);
        //smashingTitle.draw(0,0);
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
        
         if (sync.currentBeat > 1) {
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
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        //four shapes move
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofSetLineWidth(2);
        float progress = ofMap(barfloat, 8, 8.25, 0,1);
        
        progress*=progress;
        progress*=progress;
        
        ofPoint start(200,200);
        ofPoint end(0,0);
    
        ofPoint circlePos = start + ((end-start)*progress);
        ofCircle(circlePos, 30);
        
        
        //------
        start.set(-200,-200);
        circlePos = start + ((end-start)*progress);
        ofCircle(circlePos, 30);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        start.set(200,-200);
        circlePos = start + ((end-start)*progress);
        ofRect(circlePos, 60,60);
        
        start.set(-200,200);
        circlePos = start + ((end-start)*progress);
        ofFill();
        ofSetColor(0, 0, 0);
        ofRect(circlePos, 60,60);
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofRect(circlePos, 60,60);
    }
    
    if (barfloat >=8.25 && barfloat < 8.5) {
       ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        //four shapes in center
        ofFill();
        ofSetColor(0,0,0);
        ofCircle(0,0,30);
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofCircle(0,0,30);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofFill();
        ofSetColor(0,0,0);
        ofRect(0,0,60,60);
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofRect(0,0,60,60);
    }
    
    
    if (barfloat >=8.5 && barfloat < 9.25) {
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        //square pulse center
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofSetRectMode(OF_RECTMODE_CENTER);
        if (sync.current8th > 1) {
            ofRect(0,0,ofMap(sync.beatPulse, 0, 1, 60,50),ofMap(sync.beatPulse, 0, 1, 60,50));
        }
        if (sync.current8th > 3 ) {
            ofSetColor(0,255,171);
            ofRect(0,0,ofMap(sync.eighthPulse, 0, 1, 60,50),ofMap(sync.eighthPulse, 0, 1, 60,50));
        }
        
        }
    
    if (barfloat >=9 && barfloat < 9.25) {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        //four shapes to corner
        ofSetColor(0,255,171);
        ofNoFill();
        float progress = ofMap(barfloat, 9, 9.25, 0,1);
        
        progress*=progress;
        progress*=progress;
        progress*=progress;
        
        ofPoint end(200,200);
        ofPoint start(0,0);
        
        float scale = 1.2;
        
        ofPoint circlePos = start + ((end-start)*progress);
        ofSetColor(0,255,171);
        //ofCircle(circlePos, 30);
        
        arrow.init(circlePos.x, circlePos.y, ofColor(255,25,0));
        arrow.draw(scale, false);
        
        end.set(-200,-200);
        circlePos = start + ((end-start)*progress);
        ofSetColor(206,255,0);
       
        square.init(circlePos.x, circlePos.y, ofColor(85,0,255));
        square.draw(scale, false);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        end.set(200,-200);
        circlePos = start + ((end-start)*progress);
       
        octo.init(circlePos.x, circlePos.y, ofColor(169,255,9));
        octo.draw(scale, false);
        
        end.set(-200,200);
        //fill a black square to cover
        ofFill();
        ofSetColor(0, 0, 0);
        ofRect(circlePos, 100,100);
        
        //the sqaure outline
        ofSetColor(0,255,171);
        ofNoFill();
        circlePos = start + ((end-start)*progress);
        ofRect(circlePos, 60,60);
        
    }

    if (barfloat >=9.4 && barfloat < 9.75) {
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        
        //rotate shapes once they're in place
        float scale = 1.2;
        
        ArrowShape arrow2;
        arrow2.init(200,200,ofColor(255,0,169));
        arrow2.rotation = sync.eighthPulse*20;
        arrow2.draw(scale, false);
        
        CurveSquare square2;
        square2.init(-200,-200, ofColor(0,175,255));
        square2.rotation = sync.eighthPulse*20;
        square2.draw(scale, false);
        
        OctoplusShape octo2;
        octo2.init(200, -200, ofColor(255,253));
        octo2.rotation = sync.eighthPulse*20;
        octo2. draw(scale, false);
        
        ofPushMatrix();
        ofTranslate(-200,200);
        ofRotate(sync.eighthPulse*20);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofRect(0,0,60,60);
        ofPopMatrix();
    }
    
     if (barfloat >=10 && barfloat < 10.5) {
         
         if (sync.current16th < 8) {
             octo.draw(1.2, false);
         }else {
             octo.colour = ofColor(169,255,9);
             octo.draw(1.2, false);
         }
         
         if (sync.current16th > 4) {
             square.colour = ofColor(0,0,0);
             square.draw(1.2, false);
         }else {
             square.colour = ofColor(0,175,255);
             square.draw(1.2, false);
         }
     }
    
    if (barfloat >=10.5 && barfloat < 11.25) {
        //rotate shapes MORE once they're in place -- CHANGE COLOURS HERE!
        
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        float scale = 1.2;
        
        ArrowShape arrow2;
        arrow2.init(200,200,ofColor(255,0,169));
        arrow2.rotation = sync.eighthPulse*volume*50;
        arrow2.draw(scale, false);
        
        CurveSquare square2;
        square2.init(-200,-200, ofColor(0,175,255));
        square2.rotation = sync.eighthPulse*volume*50;
        square2.draw(scale, false);
        
        OctoplusShape octo2;
        octo2.init(200, -200, ofColor(255,253));
        octo2.rotation = sync.eighthPulse*volume*60;
        octo. draw(scale, false);
        
        ofPushMatrix();
        ofTranslate(-200,200);
        ofRotate(sync.eighthPulse*volume*50);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(ofColor::cyan);
        ofNoFill();
        ofRect(0,0,60,60);
        ofPopMatrix();
        
}

    
    
    if (barfloat >=9.25 && barfloat < 11.75) {
        
         ofEnableBlendMode(OF_BLENDMODE_ADD);
        
        
        ofSetColor(ofColor::cyan);
        ofNoFill();
        
        float scale =1.2;
        
        arrow.init(200, 200, ofColor(255,25,0));
        arrow.rotation = 0;
        arrow.draw(scale, false);
        
        square.init(-200, -200, ofColor(85,0,255));
        square.rotation = 0;
        square.draw(scale, false);

        octo.init(200, -200, ofColor(169,255,9));
        octo.rotation = 0;
        octo.draw(scale, false);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(-200,200,60,60);
        
    }

    if (barfloat >=11.75 && barfloat < 12) {
        //four shapes back in to center
        
        float progress = ofMap(barfloat, 11.75, 12, 0,1);
        
        progress*=progress;
        progress*=progress;
    
        
        ofPoint end(0,0);
        ofPoint start(200,200);
        
        float scale = 1.2;
        
        ofPoint circlePos = start + ((end-start)*progress);
        arrow.init(circlePos.x, circlePos.y, ofColor(255,25,0));
        arrow.draw(scale, false);
        
        start.set(-200,-200);
        circlePos = start + ((end-start)*progress);
        square.pos = circlePos;
        //square.init(circlePos.x, circlePos.y, ofColor(85,0,255));
        square.draw(scale, false);
        
        start.set(210,-210);
        circlePos = start + ((end-start)*progress);
        //octo.init(circlePos.x, circlePos.y, ofColor(169,255,9));
        octo.pos = circlePos;
        octo.draw(scale, false);
        
        start.set(-210,210);
         ofSetRectMode(OF_RECTMODE_CENTER);
        //fill a black square to cover
        ofFill();
        ofSetColor(0, 0, 0);
        ofRect(circlePos, 100,100);
        
        //the sqaure outline
        ofSetColor(0,255,171);
        ofNoFill();
        circlePos = start + ((end-start)*progress);
        ofRect(circlePos, 60,60);
    }
    
    
    if (barfloat >=12 && barfloat < 15) {
       //volume bounce rounded squares
       ofEnableBlendMode(OF_BLENDMODE_ADD);
        vector<CurveSquare> squares;
        float hue = 100;
        
        for (int i =0; i < 6; i++) {
            CurveSquare sq;
            ofColor c;
            c.setHsb(hue, 255, 255);
            ofSetColor(c);
            sq.init(0, 0, ofColor(c));
           
            if (hue < 255 ){
                hue= hue +25;
            } else {
                hue =0;
            }
            squares.push_back(sq);
        }
        
        float startSize = 1.2;
        
        for (int j=0; j < squares.size(); j++) {
            Boolean fill;
            if (j%2==0) {
                
                fill = false;
                squares[j].draw(ofMap(sync.eighthPulse, 0, 8, startSize,startSize*2), fill);
            }
            else {
                fill = false;
                squares[j].draw(ofMap(volume, 0, 1, startSize,startSize*2), fill);
            }
           
            startSize+=1.75;
        }
    }
    
    
    if (barfloat >=15 && barfloat < 16.75) {
        //awesome volume flexing octos
        ofColor c;
        c.setHsb(hue, 255, 255);
        ofSetColor(c);
        
        OctoplusShape octo1;
        octo1.init(-100, 0, ofColor(c));
        octo1.draw(1.5*volume, false);
       
        OctoplusShape octo2;
        octo2.init(0, 0, ofColor(c));
        octo2.draw(1.5*volume, false);
        
        OctoplusShape octo3;
        octo3.init(100, 0, ofColor(c));
        octo3.draw(1.5*volume, false);
        octo3.rotation = 0;
        
        if (hue < 255 ){
            hue= hue +50;
        } else {
            hue =0;
        }
    }
    
    if (barfloat >=17 && barfloat < 19.75) {
         //first spirograph
         float allrotation = ofMap(barfloat, 17,19,180,0);
         float progress = ofMap(barfloat, 17,17.25, 0, 1, true);
         float totalshapes = 36;
         int endshapesnum = progress * totalshapes;
         int startshapesnum = ofMap(barfloat, 19.5,19.75, 0, totalshapes, true);
         
         CurveSquare mySq;
         mySq.init(400, 0, ofColor());
         
         ofColor c;
         
         for(int i = startshapesnum; i<endshapesnum; i++) {
             ofPushMatrix();
             ofTranslate(-400, 300);
             //ofCircle(0,0,10);
             ofRotate(ofMap(i, 0, totalshapes,-60 + allrotation, 360-60+ allrotation));
             
             c.setHsb(ofMap(i,0,totalshapes, 0, 255), 230, 50);
             mySq.colour = c;
             
             mySq.draw(8, true);
             
             ofPopMatrix();
         }
     }
    

    if (barfloat >=19.5 && barfloat < 22) {
        // Second spirograph
        float allrotation = ofMap(barfloat, 19.5,21,180,0);
        float progress = ofMap(barfloat, 19.75,20, 0, 1, true);
        float totalshapes = 36;
        int endshapesnum = progress * totalshapes;
        int startshapesnum = ofMap(barfloat, 21.75,22, 0, totalshapes, true);
        
        CurveSquare mySq;
        mySq.init(400, 0, ofColor());
        
        ofColor c;
        
        for(int i = startshapesnum; i<endshapesnum; i++) {
            ofPushMatrix();
            ofTranslate(400, -500);
            //ofCircle(0,0,10);
            ofRotate(ofMap(i, 0, totalshapes,-60 + allrotation, 360-60+ allrotation));
            
            c.setHsb(ofMap(i,0,totalshapes, 0, 255), 230, 50);
            mySq.colour = c;
            
            mySq.draw(8, true);
            
            ofPopMatrix();
        }
    }

    if (barfloat >=22 && barfloat < 23) {
        //arrows squares build in
        
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        float totalshapes = 5;
        float progress = ofMap(barfloat, 22,23, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
     
            ofPushMatrix();
            ofTranslate(0, 384);
            ofRotate(45);
            ofSetRectMode(OF_RECTMODE_CENTER);
        
            ofColor c;
        
         for(int i = endshapes; i>=0; i--) {
            c.setHsb(255-i*12, 255, 255);
              ofSetColor(c);
             ofRect(0,0,i*200,i*200);
             
         }
            ofPopMatrix();
          
    }
    
    
    if (barfloat >=23.25 && barfloat < 24) {
       //arrow square flicker to 16ths
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        float totalshapes = 5;
        float progress = ofMap(barfloat, 23.25,23.5, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(0, 384);
        ofRotate(45);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        
        for(int i = endshapes; i>=0; i--) {
            c.setHsb(255-i*12, 255, ofMap(sync.sixteenthPulse, 0,1,100,255));
            ofSetColor(c);
            ofRect(0,0,i*200,i*200);
            
        }
        ofPopMatrix();
        
    }
    
    if (barfloat >=24 && barfloat < 24.75) {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        
        // arrow squares OUT
        float totalshapes = 5;
        float progress = ofMap(barfloat, 24.5,24.75, 1, 0, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(0, 384);
        ofRotate(45);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        for(int i = endshapes; i>=0; i--) {
            c.setHsb(255-i*12, 255, 255);
            ofSetColor(c);
            ofRect(0,0,i*200,i*200);
            
        }
        ofPopMatrix();
        
    }
   
    // removing accent octos and 3 up shapes to make room for arrows


    // end of cut
    
    if (barfloat >=32 && barfloat < 35) {
        
        // scrolly squares -horizontal lower
        float totalshapes = 12;
        float progress = ofMap(barfloat, 32, 36, -1200,200);
        
        ofPushMatrix();
        ofTranslate(progress, 50);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        
        for(int i = 0; i < totalshapes; i++) {
            c.setHsb(235-i*ofRandom(15), 255, 255);
            ofSetColor(c);
    
                ofFill();
                ofRect(posX,0,sync.beatPulse*40,sync.beatPulse*40);
                ofNoFill();
                ofRect(posX,0,volume*40,volume*40);
                posX += 300;
        }
        ofPopMatrix();
    }
   
    
    if (barfloat >=32.25 && barfloat < 35) {
        
       // scrolly squares -horizontal upper
        float totalshapes = 12;
        float progress = ofMap(barfloat, 32, 36, 200,-1200);
        
        ofPushMatrix();
        ofTranslate(progress, -50);
        //ofCircle(0,0,10);
        //ofRotate(progress); // should move across instead of rotating 20 to 60 degrees?
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        
        for(int i = 0; i <totalshapes; i++) {
            c.setHsb(235-i*ofRandom(15), 255, 255);
            ofSetColor(c);
            
            ofFill();
            ofRect(posX,0,sync.beatPulse*40,sync.beatPulse*40);
            ofNoFill();
            ofRect(posX,0,volume*40,volume*40);
            posX += 300;
        }
        ofPopMatrix();
    }
    
    
    
     if (barfloat >=35 && barfloat < 35.5) {
         //vocal break in harmonica solo
         //REST
         
     }
    
    if (barfloat >=35.25 && barfloat < 35.75) {
        //vocal break in harmonica solo
        // 4 circle multi pulse
        float totalshapes = 3;
        float progress = ofMap(barfloat, 35.25,35.75, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(-200, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        float posY =0;
        for(int i = endshapes; i>0; i--) {
            c.setHsb(255-i*12, 255, 255);
            ofSetColor(c);
            
            //posY = ofRandom(-100,100);
            //draw our squares
            ofFill();
            ofCircle(posX,100,sync.eighthPulse*20);
            
            ofNoFill();
            ofCircle(posX,-100,volume*20*i);
            posX += 400;
        }
        ofPopMatrix();

    }
    
    if (barfloat >=36 && barfloat < 39) {
        
        // scrolly squares - vertical left
        float totalshapes = 24;
        float progress = ofMap(barfloat, 36, 39, -1200, 200);
        
        ofPushMatrix();
        ofTranslate(50, progress);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posY =0;
        
        for(int i = 0; i < totalshapes; i++) {
            c.setHsb(235-i*ofRandom(15), 255, 255);
            ofSetColor(c);
            
            ofFill();
            ofRect(0,posY,sync.beatPulse*40,sync.beatPulse*40);
            ofNoFill();
            ofRect(0,posY,volume*40,volume*40);
            posY += 200;
        }
        ofPopMatrix();
    }
    
    
    if (barfloat >=36.25 && barfloat < 39) {
        
        // scrolly squares - vertical
        float totalshapes = 24;
        float progress = ofMap(barfloat, 36.25, 40, 200, -1200);
        
        ofPushMatrix();
        ofTranslate(-50,progress);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posY =0;
        
        for(int i = 0; i <totalshapes; i++) {
            c.setHsb(235-i*ofRandom(15), 255, 255);
            ofSetColor(c);
            
            ofFill();
            ofRect(0, posY,sync.beatPulse*40,sync.beatPulse*40);
            ofNoFill();
            ofRect(0,posY,volume*40,volume*40);
            posY += 200;
        }
        ofPopMatrix();
    }
    

    if (barfloat >=39 && barfloat < 39.75)  {
       
        // 4 circle multi pulse - blue hue
        float totalshapes = 3;
        float progress = ofMap(barfloat, 39,39.75, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(-200, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        float posY =0;
        for(int i = endshapes; i>0; i--) {
            c.setHsb(235-i*12, 255, 255);
            ofSetColor(c);
            
            //posY = ofRandom(-100,100);
            //draw our squares
            ofFill();
            ofCircle(posX,100,sync.eighthPulse*20);
            
            ofNoFill();
            ofCircle(posX,-100,volume*20*i);
            posX += 400;
        }
        ofPopMatrix();
        
    }
    
    
    
    if (barfloat >=40 && barfloat < 42.25) {
        //awesome volume flexing octos
        ofColor c;
        c.setHsb(hue, 255, 255);
        ofSetColor(c);
        
        OctoplusShape octo1;
        octo1.init(-100, 0, ofColor(c));
        octo1.draw(1.5*volume, false);
        
        OctoplusShape octo2;
        octo2.init(0, 0, ofColor(c));
        octo2.draw(1.5*volume, false);
        
        OctoplusShape octo3;
        octo3.init(100, 0, ofColor(c));
        octo3.draw(1.5*volume, false);
        octo3.rotation = 0;
        
        if (hue < 255 ){
            hue= hue +50;
        } else {
            hue =0;
        }
    }

    
    if (barfloat >=43 && barfloat < 45.75) {
        //first spirograph - second round
        
        }
    
    
    if (barfloat >=45.5 && barfloat < 49) {
        // Second spirograph - second round
     
    }

    
    // moving cut up to 63
    
    if (barfloat >=63 && barfloat < 63.25) {
        
        //half note laser launching centered octo
        ofColor c;
        c.setHsb(hue, 255, 255);
        ofSetColor(c);
        
        OctoplusShape octo1;
        octo1.init(0, 0, ofColor(c));
        octo1.draw(5*volume, false);
        
        if (hue < 255 ){
            hue= hue +50;
        } else {
            hue =0;
        }
    }
    
    
    if (barfloat >=63.25 && barfloat < 64) {
        
        // 3 square horz lineup
        float totalshapes = 4;
        float progress = ofMap(barfloat, 63.25,64, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(-200, 0);
        //ofRotate(45);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        
        for(int i = endshapes; i>0; i--) {
            c.setHsb(255-i*12, 255, 255);
            ofSetColor(c);
            
            //draw our squares
            ofFill();
            ofRect(posX,0,sync.eighthPulse*40,sync.eighthPulse*40);
            
            ofNoFill();
            ofRect(posX,0,volume*40,volume*40);
            posX += 200;
        }
        ofPopMatrix();
    }
    
    //REPEATING SECTION
    
    if (barfloat >=64 && barfloat < 64.25) {
        
        //half note laser launching centered octo
        ofColor c;
        c.setHsb(hue, 255, 255);
        ofSetColor(c);
        
        OctoplusShape octo1;
        octo1.init(0, 0, ofColor(c));
        octo1.draw(5*volume, false);
        
        if (hue < 255 ){
            hue= hue +50;
        } else {
            hue =0;
        }
    }
    
    
    if (barfloat >=64.25 && barfloat < 65) {
        
        // 3 circle lineup pulse
        float totalshapes = 4;
        float progress = ofMap(barfloat, 64.25,65, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(-200, 0);
        //ofRotate(45);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        
        for(int i = endshapes; i>0; i--) {
            c.setHsb(255-i*12, 255, 255);
            ofSetColor(c);
            
            //draw our squares
            ofFill();
            ofCircle(posX,0,sync.eighthPulse*60);
            
            ofNoFill();
            ofCircle(posX,0,volume*60*i);
            posX += 200;
        }
        ofPopMatrix();
    }
    
    if (barfloat >=65 && barfloat < 65.5) {
        
        //circles cinch in middle
        float progress = ofMap(barfloat, 65.25, 65.5, 0,1);
        
        progress*=progress;
        progress*=progress;
        
        ofColor c;
        c.setHsb(ofMap(progress, 0,1, 220,255), 255, 255);
        ofSetColor(c);
        ofPoint end(0,0);
        ofPoint start(-200,0);
        ofPoint circlePos = start + ((end-start)*progress);
        
        start.set(-200,0);
        ofNoFill();
        circlePos = start + ((end-start)*progress);
        //ofFill();
        ofCircle(circlePos,sync.beatPulse*60);
        
        start.set(0,0);
        ofNoFill();
        circlePos = start + ((end-start)*progress);
        ofFill();
        ofCircle(circlePos,sync.beatPulse*60);
        
        start.set(200,0);
        ofNoFill();
        circlePos = start + ((end-start)*progress);
        //ofFill();
        ofCircle(circlePos,sync.beatPulse*60);
        
    }
    /*--- REPEAT 2 BARS */
    
    if (barfloat >=66 && barfloat < 66.25) {
        
        //half note laser launching centered octo
        ofColor c;
        c.setHsb(hue, 255, 255);
        ofSetColor(c);
        
        OctoplusShape octo1;
        octo1.init(0, 0, ofColor(c));
        octo1.draw(5*volume, false);
        
        if (hue < 255 ){
            hue= hue +50;
        } else {
            hue =0;
        }
    }
    
    
    if (barfloat >=66.25 && barfloat < 67) {
        
        // 3 circle lineup pulse
        float totalshapes = 4;
        float progress = ofMap(barfloat, 66.25,67, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(-200, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        
        for(int i = endshapes; i>0; i--) {
            c.setHsb(255-i*12, 255, 255);
            ofSetColor(c);
            
            //draw our squares
            ofFill();
            ofCircle(posX,0,sync.eighthPulse*60);
            
            ofNoFill();
            ofCircle(posX,0,volume*60*i);
            posX += 200;
        }
        ofPopMatrix();
    }
    
    if (barfloat >=68 && barfloat < 68.5) {
        
        float progress = ofMap(barfloat, 68.25, 68.5, 0,1);
        
        progress*=progress;
        progress*=progress;
        
        ofColor c;
        c.setHsb(ofMap(progress, 0,1, 220,255), 255, 255);
        ofSetColor(c);
        
        ofPoint end(0,0);
        ofPoint start(-200,0);
        ofPoint circlePos = start + ((end-start)*progress);
        
        start.set(-200,0);
        circlePos = start + ((end-start)*progress);
        ofNoFill();
        ofCircle(circlePos,sync.beatPulse*60);
        
        start.set(0,0);
        circlePos = start + ((end-start)*progress);
        ofNoFill();
        ofCircle(circlePos,sync.beatPulse*60);
        start.set(200,0);
        
        circlePos = start + ((end-start)*progress);
        ofNoFill();
        ofCircle(circlePos,sync.beatPulse*60);
    }
    
    // REPEAT TWO BARS AGAIN
    
    if (barfloat >=69 && barfloat < 69.25) {
        
        //half note laser launching centered octo
        ofColor c;
        c.setHsb(hue, 255, 255);
        ofSetColor(c);
        
        OctoplusShape octo1;
        octo1.init(0, 0, ofColor(c));
        octo1.draw(5*volume, false);
        
        if (hue < 255 ){
            hue= hue +50;
        } else {
            hue =0;
        }
    }
    
    
    if (barfloat >=69.25 && barfloat < 70) {
        
        // 3 squares lineup pulse
        float totalshapes = 4;
        float progress = ofMap(barfloat, 69.25,70, 0, 1, true);
        float endshapes = floor(progress * totalshapes);
        
        ofPushMatrix();
        ofTranslate(-200, 0);
        //ofRotate(45);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofColor c;
        float posX =0;
        
        for(int i = endshapes; i>0; i--) {
            c.setHsb(255-i*12, 255, 255);
            ofSetColor(c);
            
            //draw our squares
            ofFill();
            ofRect(posX,0,sync.eighthPulse*60,sync.eighthPulse*60);
            
            ofNoFill();
            ofRect(posX,0,volume*60*i,volume*60*i);
            posX += 200;
        }
        ofPopMatrix();
    }
    
    if (barfloat >=70 && barfloat < 70.5) {
        
        //circles cinch in middle
        float progress = ofMap(barfloat, 70.25, 70.5, 0,1);
        
        progress*=progress;
        progress*=progress;
        
        ofColor c;
        c.setHsb(ofMap(progress, 0,1, 220,255), 255, 255);
        ofSetColor(c);
        ofPoint end(0,0);
        ofPoint start(-200,0);
        ofPoint circlePos = start + ((end-start)*progress);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        start.set(-200,0);
        ofNoFill();
        circlePos = start + ((end-start)*progress);
        //ofFill();
        ofRect(circlePos,sync.beatPulse*60,sync.beatPulse*60);
        
        start.set(0,0);
        
        circlePos = start + ((end-start)*progress);
        ofFill();
        ofRect(circlePos,sync.beatPulse*60,sync.beatPulse*60);
        
        start.set(200,0);
        ofNoFill();
        circlePos = start + ((end-start)*progress);
        ofRect(circlePos,sync.beatPulse*60,sync.beatPulse*60);
        
    }
    
    
    
    
    
    ///end of moved cut
    
    
       ofPopStyle();

}

void AnimationSequence::writeinPNL(string message) {
    float halfWidth = proximaNovaL.stringWidth(message)/2;
    proximaNovaL.drawString(message, -1*halfWidth, 0);
}




