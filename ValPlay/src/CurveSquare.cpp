
#include "CurveSquare.h"

CurveSquare::CurveSquare(){
   init(0,0, ofColor::white,0);
}

CurveSquare::CurveSquare(float x, float y, ofColor col) {
    init(x,y, col, 0);
};

void CurveSquare::init(float x, float y, ofColor col, float rot) {
    pos.set(x,y);
    colour = col;
    visible = true;
    rotation = rot;
    size = 1;
}

void CurveSquare::draw(float scale = 1, bool fill=false){
    
//    ofSetColor(colour);
//    ofPushMatrix();
//    ofPushStyle();
//    ofTranslate(pos);
//    ofScale(size*scale, size*scale);
//    ofRotate(rotation);
//    
//    if (!fill) {
//        ofNoFill();
//        ofSetLineWidth(2);
//    }
//    
//    ofBeginShape();
//    ofVertex(0,0);
//    ofBezierVertex(0,0,-6,1,-9,6);
//    ofBezierVertex(-12,9,-12,17,-12,17);
//    ofVertex(-12,44);
//    ofVertex(14,44);
//    ofBezierVertex(14,44,22,44,26,41);
//    ofBezierVertex(30,38,30,32,30,32);
//    ofVertex(30,0);
//    ofVertex(0,0);
//    ofEndShape();
//    
//    ofPopStyle();
//    ofPopMatrix();
//    
    
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
    
   
    ofCircle(0, 0, 1);
    
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

