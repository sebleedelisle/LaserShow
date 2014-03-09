#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofSetFrameRate(60);

	screenWidth = 1280;
	screenHeight = 960;
	
	guideImage.loadImage("img/LaserableArea.jpg");
	smashingTitle.init("img/SmashingLogo.png", 0, 2000);
	
	
	previewProjector = false;
	
	projectorFbo.allocate(1024, 768, GL_RGB, 4);

	projectorFbo.begin();
	ofSetColor(0);
	ofRect(0,0,1024,768);
	projectorFbo.end();
	ofSetColor(255);
	projectorPosition.set(screenWidth/5*2, screenHeight*4/5, screenWidth/5, screenHeight/5);
	
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
	gui.setPosition(ofPoint(screenWidth+220 - panelwidth - 10,10));
	gui.setVisible(true);
	gui.add(&laserManager.connectButton);
	gui.add(laserManager.parameters);
	

	
	gui.load();
	
	
	music.loadSound("../../../Music/02 Down the Road.aif");
	music.play(); 
	
	
	sync.tempo = 111;
	sync.startPosition = 60000/111;
		
}


//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	laserManager.update();
	
	sync.update(music.getPositionMS());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	if(!previewProjector) {
		ofSetColor(200);
		guideImage.draw(0,0,screenWidth, screenHeight);
		ofSetColor(255);
		ofRect(projectorPosition.x-1, projectorPosition.y-1, projectorPosition.width+2, projectorPosition.height+2);
		projectorFbo.draw(projectorPosition);
		
	} else {
		projectorFbo.draw(screenWidth/2 - projectorFbo.getWidth()/2, screenHeight/2 - projectorFbo.getHeight()/2);
		
	}
	
	ofDrawBitmapString(ofToString(round(ofGetFrameRate())), 0,10);
		
	int numBands = 500;
	float * val = ofSoundGetSpectrum(numBands);
	
	
	laserManager.draw();
	laserManager.renderLaserPath(ofRectangle(0,0,screenWidth, screenHeight), false);
	laserManager.renderPreview();
	numBands = 100; 
	int barWidth = (1024/numBands);
	ofFill();
	for(int i = 0; i<numBands; i++) {
		
		float size = val[i] * 100; 
		//ofRect(i*barWidth, 768 - size, barWidth-1, size );
		ofRect(i*barWidth, 0, barWidth-1, size );

	}
	ofNoFill();
	//ofRect(0, 668, numBands*barWidth, 100);
		
	
	
	float time = music.getPositionMS()/1000.0f;
	//bar = time /
	
	ofDrawBitmapString(ofToString(time), 0,25);

/*
	beatNumber = int((music.getPositionMS() - lastTime) / (60000.0f/tempo) - 1) ;
	int barNumber = beatNumber/4;
	
	ofDrawBitmapString(ofToString(barNumber) + " " + ofToString(beatNumber%4+1), 0,40);
*/
	
	
	projectorFbo.begin();
	ofPushStyle();

	ofFill();
	ofSetColor(0);
	ofRect(0,0,1024,768);

	if(sync.currentBar<=9) {
		ofPushStyle();
		ofSetColor(ofColor::cyan);
		ofSetLineWidth(3);
		float size = val[30] * 100;
		ofNoFill(); 
		ofCircle(512,384,size);
		ofPopStyle();
		
	}
	
	smashingTitle.draw(sync);
	
	ofPopStyle();
	projectorFbo.end();
	
	ofDrawBitmapString(sync.getString(), 1000,10);
	sync.draw(1100,10);
	
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if(key == 'f') ofToggleFullscreen();
	if(key == '\t') gui.toggleVisible();
	if(key == 'w') laserManager.showWarpPoints = !laserManager.showWarpPoints;
	if(key == ' ') previewProjector = !previewProjector;
	if(key == OF_KEY_UP) music.setPosition(0);
	
	
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