#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofSetFrameRate(60);

	screenWidth = 1024;
	screenHeight = 768;
	
	laserManager.setup(screenWidth, screenHeight);
	//laserManager.connectToEtherdream();
	
	laserManager.renderLaserPreview = true;
	laserManager.showPostTransformPreview = true;
	
	
	int panelwidth = 200;
	
	ofxBaseGui::setDefaultWidth(panelwidth);
    ofxBaseGui::setDefaultHeight(16);
	ofxBaseGui::setDefaultSpacing(3);
    ofxBaseGui::setDefaultElementSpacing(3);
	ofxBaseGui::setDefaultElementIndentation(1);
	ofxBaseGui::setDefaultTextPadding(5);
	ofxBaseGui::setUseTTF(true);
	
	ofxBaseGui::loadFont("VeraMoIt.ttf",8, true);
	
	gui.setup("Settings");
	gui.setPosition(ofPoint(screenWidth - panelwidth - 10,10));
	gui.setVisible(true);
	gui.add(&laserManager.connectButton);
	gui.add(laserManager.parameters);
	

	
	gui.load();
	
	
	music.loadSound("../../../Music/02 Down the Road.aif");
	music.play(); 
	
		
}


//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	laserManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofDrawBitmapString(ofToString(round(ofGetFrameRate())), 0,10);
		
	int numBands = 500;
	float * val = ofSoundGetSpectrum(numBands);
	
	//ofCircle(512,384,100);
	
	//ofCircle(512,384,val[0]*1000);
	//laserManager.addLaserCircle(ofPoint(512,384),ofColor(255,0,0	), val[0]*1000);
	//laserManager.addLaserCircle(ofPoint(512,384),ofColor(255,255,255), val[1]*2000);
	
	
	laserManager.draw();
	laserManager.renderLaserPath(ofRectangle(0,0,screenWidth, screenHeight), false);
	laserManager.renderPreview();
	
	int barWidth = (1024/numBands);
	ofFill();
	for(int i = 0; i<numBands; i++) {
		
		float size = val[i] * 100; 
		ofRect(i*barWidth, 768 - size, barWidth-1, size );
		
	}
	ofNoFill();
	ofRect(0, 668, numBands*barWidth, 100);
	
	
	
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if(key == 'f') ofToggleFullscreen();
	if(key == '\t') gui.toggleVisible();
	if(key == 'w') laserManager.showWarpPoints = !laserManager.showWarpPoints;
	
}



//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int numChannels){
	
		
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
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::exit() {
	gui.save();
	
	laserManager.warp.saveSettings();

}