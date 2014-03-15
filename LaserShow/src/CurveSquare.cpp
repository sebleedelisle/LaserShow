
#include "CurveSquare.h"

CurveSquare::CurveSquare(){
   init(0,0, ofColor::white);
}

CurveSquare::CurveSquare(float x, float y, ofColor col) {
    init(x,y, col);
};

void CurveSquare::init(float x, float y, ofColor col) {
    pos.set(x,y);
    colour = col;
    visible = true;
    size = 1;
}

void CurveSquare::draw(float scale = 1, bool fill=false){
    
    ofSetColor(colour);
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(pos);
    ofScale(size*scale, size*scale);
    ofRotate(rotation);
    
    if (!fill) {
        ofNoFill();
        ofSetLineWidth(2);
    }
    
   
    //ofCircle(0, 0, 1);
    
    ofBeginShape();
    ofVertex(-9,-21);
    ofBezierVertex(-9,-21,-15,-21,-18,-17);
    ofBezierVertex(-21,-13,-21,-5,-21,-5);
    ofVertex(-21,21);
    ofVertex(4,21);
    ofBezierVertex(4,21,12,22,16,19);
    ofBezierVertex(20,16,21,10,21,10);
    ofVertex(21,-21);
    ofVertex(-9,-21);
    ofEndShape();    
    ofPopStyle();
    ofPopMatrix();
}



void CurveSquare::drawPoly(float x, float y) {
    // cSquare.clear();
    cSquare.addVertex(x,y);
    cSquare.bezierTo(x,y,-6,1,-9, 6);
    cSquare.bezierTo(-12,9,-12,17,-12,17);
    cSquare.addVertex(-12,44);
    cSquare.addVertex(14,44);
    cSquare.bezierTo(14,44,22,44,26,41);
    cSquare.bezierTo(30,38,30,32,30,32);
    cSquare.addVertex(30,y);
    cSquare.addVertex(30,y);
    cSquare.close();
    cSquare.draw();
}

