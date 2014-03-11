#include "curvedSquare.h"

ofPolyline myPoly;

curvedSquare::curveSquare()
{
    
    x = 100;
    y = 100;
    
    speedX = ofRandom(-1, 1);           // and random speed and direction
    speedY = ofRandom(-1, 1);
    
    dim = 20;
    
    myPoly.addVertex(x,y);
    myPoly.bezierTo(x,y,x-6,y+1,x-9, y+6);
    myPoly.bezierTo(x-12,y+9,x-12,y+17,x-12,y+17);
    myPoly.addVertex(x-12,y+44);
    myPoly.addVertex(x+14,y+44);
    myPoly.bezierTo(x+14,y+44,x+22,y+44,x+26,y+41);
    myPoly.bezierTo(x+30,y+38,x+30,y+32,x+30,y+32);
    myPoly.addVertex(x+30,y);
    myPoly.addVertex(x+30,y);
    myPoly.close();
    
    
}

void curvedSquare::update(){
    x++;
    y++;
    
}

void curvedSquare::draw(){
    ofSetColor(255,0,0);
    myPoly.draw();
}