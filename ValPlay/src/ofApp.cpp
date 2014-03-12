#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofEnableSmoothing();
    
    cSq.init(200,300,ofColor::pink, 0);
    octo.init(400,500,ofColor::magenta);
    arrow.init(200,100,ofColor::yellow,0);
    
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
        mySquare.init(x, y, ofColor::cyan, deg);
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
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetLineWidth(2);
    cSq.draw(1, true);
    //cSq.drawPoly(200, 200);
    arrow.draw(1, false);
    octo.draw(1, false);
    //octo.drawPoly(100, 100);
    
    //just messing with drawing out some squares in a pattern
    for (int i = 0; i < squares.size(); i++){
        squares[i].draw(1, false);
    }
    
    
    //draw the arrows
    for (int j = 0; j < arrows.size(); j++){
        arrows[j].draw(1, false);
    }
  
}


//--------------------------------------------------------------
void ofApp::splitArrows(){
    float x = 400;
    float y = 400;
    
    float degs = 45;
    float radius = 150;
    
    for (int j = 0; j < 4; j++) {
        ArrowShape myArrow;
    
        myArrow.init(x,y, ofColor::cyan , degs);
        arrows.push_back(myArrow);
        degs+= 90;
       // cout << "degrees" << degs << endl;
    }
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
