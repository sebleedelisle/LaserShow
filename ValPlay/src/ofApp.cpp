#include "ofApp.h"


// these are global variables - better to make them properties of the ofApp object.
// Also, pixel positions should probably be floating point numbers, or better still
// an ofPoint or ofVec3f.

int xpos;
int ypos;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    cSq.init(200,300,ofColor::pink, 0);
    octo.init(400,500,ofColor::magenta);
    arrow.init(200,100,ofColor::yellow);
    
    float x = 100;
    float y = 200;
    
    for (int i = 0; i < 12; i++) {
        CurveSquare mySquare;
        float deg;
        if (i%2==0){
            deg = 90;
            y+=12; //adjust for non centered registration point
     
        }else {
            deg =0;
        }
        mySquare.init(x, y, ofColor::cyan, deg);
        squares.push_back(mySquare);
        if (i%2==0){
            x+= 70;
        }else {
            x+= 73;
        }
        y = 200;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetLineWidth(2);
    //cSq.draw(1);
    //cSq.drawPoly(200, 200);
    arrow.draw(1);
    octo.draw(1);
    //octo.drawPoly(100, 100);
    
    for (int i = 0; i < squares.size(); i++){
        squares[i].draw(1);
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
