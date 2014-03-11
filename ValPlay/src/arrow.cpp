
#include "arrow.h"

ofPolyline arrowPoly;

arrow::arrow() {
    
    x = 200;
    y = 200;
    
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
    
}

void arrow::update(){
    
 
    
}

void arrow::draw(){
    
    ofSetColor(0,255,0);
    arrowPoly.draw();
}