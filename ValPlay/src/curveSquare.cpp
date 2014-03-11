
#include "curveSquare.h"

curveSquare::curveSquare(){
    x = 100;
    y = 100;
    outlineShape(x,y);
}

void curveSquare::update(){
 
    x++;
    y++;
    outlineShape(x,y);
    
}

void curveSquare::draw(){
    
    ofSetColor(0,255,255);
    cSquare.draw();
    
}


void curveSquare::outlineShape(int x, int y) {
   
    cSquare.clear();
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
}

