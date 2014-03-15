#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    
    ofBackground(0,0,0);
    ofEnableSmoothing();
    
    cSq.init(100,100,ofColor::pink);
    octo.init(200,100,ofColor::magenta);
    arrow.init(300,100,ofColor::yellow);
    
    //draw something shaky
    shakething.init(cSq, 15, 10);
    
    float x = 100;
    float y = 200;
    

    for (int i = 0; i < 12; i++) {
        CurveSquare mySquare;
        float deg;
        if (i%2==0){
            deg = 90;
        }else {
            deg =0;
        }
        mySquare.init(x, y, ofColor::cyan);
        squares.push_back(mySquare);
        if (i%2==0){
            x+= 70;
        }else {
            x+= 74;
        }
        y = 200;
    }
    
    
    splitArrows();

    
}




//--------------------------------------------------------------
void ofApp::update(){
    
    //arrow.pos.x = ofRandom(200);
    //arrow.pos.y = ofRandom(500);
    
    anglething.update();
    shakething.update();
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetLineWidth(2);
   // cSq.draw(1, true);
    //cSq.drawPoly(200, 200);
    
    arrow.draw(1, false);
    octo.draw(1, false);
    //octo.drawPoly(100, 100);
    
    //just messing with drawing out some squares in a pattern
    for (int i = 0; i < squares.size(); i++){
        squares[i].draw(1, false);
    }
    
    
    anglething.draw();
    shakething.draw();
  
   
}


//--------------------------------------------------------------
void ofApp::splitArrows(){
    float x = 400;
    float y = 400;
    
    float degs = 45;

    for (int j = 0; j < 4; j++) {
        ArrowShape myArrow;
        myArrow.init(x,y, ofColor::cyan);
        arrows.push_back(myArrow);
         degs+= 90;
    }
    
   //draw some arrows with our angle move
    anglething.init(arrows);
    


}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
