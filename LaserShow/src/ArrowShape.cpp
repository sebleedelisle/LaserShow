
#include "ArrowShape.h"


ArrowShape::ArrowShape(){
    init(0,0, ofColor::white);
}

ArrowShape::ArrowShape(float x, float y, ofColor col) {
    init(x,y, col);
};

void ArrowShape::init(float x, float y, ofColor col) {
    pos.set(x,y);
    colour = col;
    visible = true;
    size = 1;
    vel.set(0,0);
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
    
    //ofCircle(0, 0, 1);
    
    ofBeginShape();
    ofVertex(-25,7);
    ofBezierVertex(-25,11,-18,17,-18,17);
    ofVertex(-13,23);
    ofBezierVertex(-8,18,0,10,0,10);
    ofVertex(13,23);
    ofVertex(17,18);
    ofBezierVertex(17,18,24,13,25,8);
    ofBezierVertex(25,3,21,0,21,0);
    ofVertex(0,-23);
    ofVertex(-22,-2);
    ofBezierVertex(-22,-2,-26,2,-25,7);
    ofEndShape();

    ofPopStyle();
    ofPopMatrix();
    
}

void ArrowShape::drawPoly(float x, float y) {
    
    arrowPoly.addVertex(x,y);
    arrowPoly.bezierTo(1,4,7,10,7,10);
    arrowPoly.addVertex( 13,16);
    arrowPoly.bezierTo(18,11, 26,3, 26,3);
    arrowPoly.addVertex(40,16);
    arrowPoly.addVertex(44,12);
    arrowPoly.bezierTo(44,12, 50,6, 51,1);
    arrowPoly.bezierTo(52,-4, 48,-8, 48,-8);
    arrowPoly.addVertex(26,-31);
    arrowPoly.addVertex(4,-10);
    arrowPoly.bezierTo(4,-10,x,-5,x,y);
    arrowPoly.close();
    arrowPoly.draw();
}