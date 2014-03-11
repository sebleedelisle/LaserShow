#include "octoplusShape.h"

octoplusShape::octoplusShape(){
    
    x = 300;
    y = 100;
    
    
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
}

void octoplusShape::update(){

    
}

void octoplusShape::draw(){
    ofSetColor(255,0,0);
    octoShape.draw();
    
    
    
    
}