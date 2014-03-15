#include "ShakeMove.h"


ShakeMove::ShakeMove(){
    //nuthin'
    active = false;
}

ShakeMove::ShakeMove(CurveSquare s){
    init(s, 0,1);

}

void ShakeMove::init(CurveSquare s, float rot, float its) {
    pos.set(100,100);
    square = s;
    targetRot = rot;
    active = true;
    iterations = its;
    
   
    internalSquare.init(-40, -40, ofColor::purple, 0);
    
    //if i draw the shape in here I can popmatrix/stuff to draw it a little highter up and the reg point will seem to be in the middle?
}


void ShakeMove::draw() {
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    if (!active){
        return;
    }
    
    square.draw(1, false);
    //internalSquare.draw(1, false);
    
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(100,100);
    internalSquare.draw(1, false);
    ofPopMatrix();
    ofPopStyle();

}

void ShakeMove::update() {

//    diff = square.rotation - targetRot;
//    diff= diff/10;
//    square.rotation += diff;
//    
//    if (square.rotation >= 20) {
//        targetRot = -20;
//    }
    
    square.rotation = ofRandom(targetRot, -targetRot);
    internalSquare.rotation = ofRandom(targetRot, -targetRot);
        
        
}
    





