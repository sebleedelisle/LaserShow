
#include "ArrowShape.h"


ArrowShape::ArrowShape(){
    init(0,0, ofColor::white, 0);
}

ArrowShape::ArrowShape(float x, float y, ofColor col) {
    init(x,y, col, 0);
};

void ArrowShape::init(float x, float y, ofColor col, float rot) {
    pos.set(x,y);
    colour = col;
    visible = true;
    rotation = rot;
    size = 1;
}


void ArrowShape::draw(float scale = 1, bool fill = false){
    
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
    ofBezierVertex(1,4,7,10,7,10);
    ofVertex(13,16);
    ofBezierVertex(18,11,26,3,26,3);
    ofVertex(40,16);
    ofVertex(44,12);
    ofBezierVertex(44,12,50,6,51,1);
    ofBezierVertex(52,-4,48,-8,48,-8);
    ofVertex(26,-31);
    ofVertex(4,-10);
    ofBezierVertex(4,-10,0,-5,0,0);
    ofEndShape();
    
    ofPopStyle();
    ofPopMatrix();
    
}

void ArrowShape::drawPoly(float x, float y) {
    
    arrowPoly.addVertex(x,y);
    arrowPoly.bezierTo(x+1,y+4,x+7,y+10,x+7,y+10);
    arrowPoly.addVertex(x+13,y+16);
    arrowPoly.bezierTo(x+18,y+11,x+26,y+3,x+26,y+3);
    arrowPoly.addVertex(x+40,y+16);
    arrowPoly.addVertex(x+44,y+12);
    arrowPoly.bezierTo(x+44,y+12,x+50,y+6,x+51,y+1);
    arrowPoly.bezierTo(x+52,y-4,x+48,y-8,x+48,y-8);
    arrowPoly.addVertex(x+26,y-31);
    arrowPoly.addVertex(x+4,y-10);
    arrowPoly.bezierTo(x+4,y-10,x,y-5,x,y);
    arrowPoly.close();
    arrowPoly.draw();
}