#include "OctoplusShape.h"



OctoplusShape::OctoplusShape(){
    init(0,0, ofColor::white);
}

OctoplusShape::OctoplusShape(float x, float y, ofColor col) {
    init(x,y, col);
}

void OctoplusShape::init(float x, float y, ofColor col) {
    pos.set(x,y);
    colour = col;
    visible = true;
    size = 1;
}


void OctoplusShape::draw(float scale = 1, bool fill = false){
    
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
    ofVertex(24,4);
    ofBezierVertex(21,8,21,17,21,17);
    ofVertex(21,22);
    ofVertex(17,22);
    ofBezierVertex(17,22,8,21,4,24);
    ofBezierVertex(0,27,0,33,0,33);
    ofBezierVertex(0,33,0,27,-3,24);
    ofBezierVertex(-7,21,-16,22,-16,22);
    ofVertex(-21,22);
    ofVertex(-21,17);
    ofBezierVertex(-21,17,-21,8,-24,4);
    ofBezierVertex(-27,0,-33,0,-33,0);
    ofBezierVertex(-33,0,-27,0,-24,-3);
    ofBezierVertex(-21,-7,-21,-16,-21,-16);
    ofVertex(-21,-22);
    ofBezierVertex(-18,-22,-16,-22,-16,-22);
    ofBezierVertex(-16,-22,-7,-21,-3,-24);
    ofBezierVertex(0,-27,0,-33,0,-33);
    ofBezierVertex(0,-33,0,-27,4,-24);
    ofBezierVertex(8,-21,17,-22,17,-22);
    ofVertex(21,-22);
    ofVertex(21,-16);
    ofBezierVertex(21,-16,21,-7,24,-3);
    ofBezierVertex(27,0,33,0,33,0);
    ofBezierVertex(33,0,27,0,24,4);
    ofEndShape();
    
    ofPopStyle();
    ofPopMatrix();
}


void OctoplusShape::drawPoly(float x, float y){
    
    octoShape.addVertex(x,y);
    octoShape.bezierTo(x,y+4,x,y+13,x,y+13);
    octoShape.addVertex(x-3,y+18);
    octoShape.addVertex(x-7,y+18);
    octoShape.bezierTo(x-7,y+18,x-16,y+17,x-19,y+20);
    octoShape.bezierTo(x-24,y+23,x-24,y+29,x-24,y+29);
    octoShape.bezierTo(x-24,y+29,x-24,y+23,x-28,y+20);
    octoShape.bezierTo(x-32,y+17,x-40,y+18,x-40,y+18);
    octoShape.addVertex(x-46,y+18);
    octoShape.addVertex(x-46,y+13);
    octoShape.bezierTo(x-46,y+13,x-45,y+4,x-48,y);
    octoShape.bezierTo(x-51,y-4,x-57,y-4,x-57,y-4);
    octoShape.bezierTo(x-57,y-4,x-51,y-4,x-48,y-8);
    octoShape.bezierTo(x-45,y-12,x-46,y-21,x-46,y-21);
    octoShape.addVertex(x-46,y-27);
    octoShape.bezierTo(x-43,y-27,x-40,y-27,x-40,y-27);
    octoShape.bezierTo(x-40,y-27,x-32,y-26,x-28,y-29);
    octoShape.bezierTo(x-24,y-32,x-24,y-38,x-24,y-38);
    octoShape.bezierTo(x-24,y-38,x-24,y-32,x-19,y-29);
    octoShape.bezierTo(x-16,y-26,x-7,y-27,x-7,y-27);
    octoShape.addVertex(x-3,y-27);
    octoShape.addVertex(x-3,y-21);
    octoShape.bezierTo(x-3,y-21,x-3,y-12,x,y-8);
    octoShape.bezierTo(x+3,y-4,x+9,y-4,x+9,y-4);
    octoShape.bezierTo(x+9,y-4,x+3,y-4,x,y);
    octoShape.close();
    octoShape.draw();
}
