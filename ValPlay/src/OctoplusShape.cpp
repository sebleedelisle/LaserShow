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
    
    if (!fill) {
        ofNoFill();
        ofSetLineWidth(2);
    }
    
    ofBeginShape();
    ofVertex(0,0);
    ofBezierVertex(0,4,0,13,0,13);
    ofVertex(-3,18);
    ofVertex(-7,18);
    ofBezierVertex(-7,18,-16,17,-19,20);
    ofBezierVertex(-24,23,-24,29,-24,29);
    ofBezierVertex(-24,29,-24,23,-28,20);
    ofBezierVertex(-32,17,-40,18,-40,18);
   ofVertex(-46,18);
    ofVertex(-46,13);
    ofBezierVertex(-46,13,-45,4,-48,0);
    ofBezierVertex(-51,-4,-57,-4,-57,-4);
    ofBezierVertex(-57,-4,-51,-4,-48,-8);
    ofBezierVertex(-45,-12,-46,-21,-46,-21);
    ofVertex(-46,-27);
    ofBezierVertex(-43,-27,-40,-27,-40,-27);
    ofBezierVertex(-40,-27,-32,-26,-28,-29);
    ofBezierVertex(-24,-32,-24,-38,-24,-38);
    ofBezierVertex(-24,-38,-24,-32,-19,-29);
    ofBezierVertex(-16,-26,-7,-27,-7,-27);
    ofVertex(-3,-27);
    ofVertex(-3,-21);
    ofBezierVertex(-3,-21,-3,-12,0,-8);
    ofBezierVertex(3,-4,9,-4,9,-4);
    ofBezierVertex(9,-4,3,-4,0,0);
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
