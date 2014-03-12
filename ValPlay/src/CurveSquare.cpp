
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
    
    ofBeginShape();
    ofVertex(0,0);
    ofBezierVertex(0,0,-6,1,-9,6);
    ofBezierVertex(-12,9,-12,17,-12,17);
    ofVertex(-12,44);
    ofVertex(14,44);
    ofBezierVertex(14,44,22,44,26,41);
    ofBezierVertex(30,38,30,32,30,32);
    ofVertex(30,0);
    ofVertex(0,0);
    ofEndShape();
    
    ofPopStyle();
    ofPopMatrix();
}



void CurveSquare::drawPoly(float x, float y) {
   // cSquare.clear();
    cSquare.addVertex(x,y);
    cSquare.bezierTo(x,y,x-6,y+1,x-9, y+6);
    cSquare.bezierTo(x-12,y+9,x-12,y+17,x-12,y+17);
    cSquare.addVertex(x-12,y+44);
    cSquare.addVertex(x+14,y+44);
    cSquare.bezierTo(x+14,y+44,x+22,y+44,x+26,y+41);
    cSquare.bezierTo(x+30,y+38,x+30,y+32,x+30,y+32);
    cSquare.addVertex(x+30,y);
    cSquare.addVertex(x+30,y);
    cSquare.close();
    cSquare.draw();
}

