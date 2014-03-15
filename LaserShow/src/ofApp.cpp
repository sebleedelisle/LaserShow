#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofSetFrameRate(60);

	screenWidth = 1280;
	screenHeight = 960;
	
	guideImage.loadImage("img/LaserableArea.jpg");
	
	
	previewProjector = false;
	
	projectorFbo.allocate(1024, 768, GL_RGB, 4);
	uiFbo.allocate(screenWidth, screenHeight, GL_RGB, 2); 

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
	
	laserGui.setup("LaserManager");
	laserGui.setPosition(ofPoint(screenWidth+220 - panelwidth - 10,10));
	laserGui.setVisible(true);
	laserGui.add(&laserManager.connectButton);
	laserGui.add(laserManager.parameters);
	
	laserGui.load();
	panels.push_back(&laserGui);
	
	
	music.loadSound("../../../Music/02 Down the Road.aif");
	
	soundPositionMS = 70000;
	
	sync.tempo = 111;
	sync.startPosition = 60000/111; // start after 1 beat intro

	cube1.init(200,200,ofColor::cyan);
	cube2.init(-200,200,ofColor::cyan);
	cube3.init(-200,-200,ofColor::cyan);
	
	pipeOrganData.load();
	domeData.init();
	domeData.load();
	
	domeData.gui.setPosition(ofPoint(screenWidth+220 - panelwidth - 10,10));
	domeData.gui.setVisible(false);
	
	panels.push_back(&domeData.gui);
	
	
	effectDomeLines.setDomeData(&domeData);
	effectPipeOrganLines.setPipeOrganData(&pipeOrganData);
	
	
	// can potentially use : ofSetupScreenPerspective();
	
}


//--------------------------------------------------------------
void ofApp::update(){
	
	float deltaTime = ofGetLastFrameTime(); 
	ofSoundUpdate();
	laserManager.update();
	if(music.getIsPlaying()) soundPositionMS = music.getPositionMS();

	sync.update(soundPositionMS);
	laserBeamEffect.update();
	
	screenAnimation.update();
	
	effectDomeLines.update(deltaTime);
	effectPipeOrganLines.update(deltaTime); 
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	
	int numBands = 500;
	float vol = 0;
	
	
	float * val = ofSoundGetSpectrum(numBands);
	
	for(int i = 0;i<numBands; i++) {
		vol+=val[i];
		
	}

	vol/=(float)numBands / 20.0f;
	//cout << vol << endl;
	updatePeakFrequency(val, numBands);
	//ofSetupScreenPerspective(1280, 960,ofGetMouseY());
	
	uiFbo.begin();
	ofSetupScreenPerspective(1280,960,50);

	ofSetColor(0);
	ofFill(); 
	ofRect(0,0,screenWidth, screenHeight);
	ofNoFill();
	ofSetColor(255);
	
	if(!previewProjector) {
		ofSetColor(200);
		guideImage.draw(0,0,screenWidth, screenHeight);
		ofSetColor(255);
		ofRect(projectorPosition.x-1, projectorPosition.y-1, projectorPosition.width+2, projectorPosition.height+2);
		projectorFbo.draw(projectorPosition);
		
		pipeOrganData.draw();
		//
		
		domeData.draw();
		
		
	} else {
		ofSetColor(255);
		ofRect(screenWidth/2 - projectorFbo.getWidth()/2 -1, screenHeight/2 - projectorFbo.getHeight()/2-1, projectorFbo.getWidth()+2, projectorFbo.getHeight()+2);

		projectorFbo.draw(screenWidth/2 - projectorFbo.getWidth()/2, screenHeight/2 - projectorFbo.getHeight()/2);
		
	}

	
	
	ofDrawBitmapString(ofToString(round(ofGetFrameRate())), 0,10);
	
	numBands = 100;
	int barWidth = (1024/numBands);
	ofFill();
	for(int i = 0; i<numBands; i++) {
		
		float size = val[i] * 100;
		//ofRect(i*barWidth, 768 - size, barWidth-1, size );
		ofRect(i*barWidth, 0, barWidth-1, size );
		
	}
	ofSetColor(255,0,0);

	ofRect((numBands+1)*barWidth, 0, barWidth-1, vol*100 );
	ofSetColor(255);
	
	
	ofNoFill();
	
	float time = soundPositionMS/1000.0f;

	ofDrawBitmapString(ofToString(time), 0,25);

	//drawPipeOrgan(val, numBands);

	uiFbo.end();

	//----------------- FBO BEGIN --------------------------------
	projectorFbo.begin();
	ofPushStyle();

	ofFill();
	ofSetColor(0);
	ofRect(0,0,1024,768);
	ofSetColor(255);
	
	ofPushMatrix();
	ofTranslate(512,384);
	
	screenAnimation.draw(sync, vol);
	
	if(sync.currentBarFloat<3) {
		
		
		float progress = ofMap(sync.currentBarFloat, 0, 3, 0,1);
		
		ofPushMatrix();
		ofPushStyle();
		ofScale(0.5,0.5);
		
		ofSetColor(255);
		if(progress<0.2) ofSetColor(ofMap(progress, 0, 0.2, 0, 255));
		else if(progress>0.8) ofSetColor(ofMap(progress, 0.8, 1, 255, 0));
		
		
        
	
		ofPopStyle();
		ofPopMatrix();
	
	
	}
	
//	if(sync.currentBar<8) {
//		cube1.draw(val[30]*10 );
//		cube2.draw(val[20]*10 );
//		cube3.draw(val[10]*10 );
//	}
//	
	
	ofPopMatrix(); 
	
	ofPopStyle();
	projectorFbo.end();

	//----------------- FBO END --------------------------------

		
	ofPopMatrix();
	
	uiFbo.begin();
	ofSetupScreenPerspective(1280,960,50);

	
	// EFFECTS ---------------------------------------------
	
	laserBeamEffect.draw(laserManager,vol);
	effectDomeLines.draw(sync, vol, laserManager);
	effectPipeOrganLines.draw(sync, vol, laserManager, currentPeakFrequency);
	
	
	laserManager.draw();
	laserManager.renderLaserPreview = !previewProjector; 
	if(!previewProjector) {
		laserManager.renderLaserPath(ofRectangle(0,0,screenWidth, screenHeight), false);
		//laserManager.renderPreview();
	}
	
	ofDrawBitmapString(sync.getString(), 1000,10);
	sync.draw(1100,10);
	
	uiFbo.end();
	uiFbo.draw(0,0);
	for(int i = 0; i<panels.size(); i++) {
		panels[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if(key == 'f') ofToggleFullscreen();
	if(key == '\t') {
		
		int activePanelIndex = -1; 
		for(int i =0; i<panels.size(); i++) {
			if(panels[i]->getVisible()) activePanelIndex = i;
			panels[i]->setVisible(false);
			
		}
		if(activePanelIndex ==-1) {
			panels[0]->setVisible(true);
		} else if(activePanelIndex<panels.size()-1) {
			panels[activePanelIndex+1]->setVisible(true);
		}
			
	}
	if(key == 'w') laserManager.showWarpPoints = !laserManager.showWarpPoints;
	if(key == ' ') previewProjector = !previewProjector;
	if(key == OF_KEY_DOWN) {
		music.setPosition(0);
		music.play();
	}
	if(key == OF_KEY_LEFT) {
		soundPositionMS = 69000;
		music.setPositionMS(soundPositionMS);
	}
		
	
	if(key == 'p') {
		if(music.getIsPlaying()) {
			
			music.stop();
		} else {

			music.play();
			music.setPositionMS(soundPositionMS);
		}
	
	}
	
    

	if(key == 'a') cube1.visible = true;
	if(key == 's') cube2.visible = true;
	if(key == 'd') cube3.visible = true;

	
}


void ofApp :: updatePeakFrequency(float * val, int numBands){

	
	//pipeOrganData.draw();

	//int numPipes = 20;
	//ofRectangle rect(506,631,270,190);

	int bottom = 30;
	int top = 70;
	float threshold = 0.1;
	
	float loudestLevel = threshold;
	int loudestIndex = 0;
	
	
	for(int i = bottom; i<numBands && i<top; i++) {
	
		if(val[i]>loudestLevel) {
			loudestIndex = i;
			loudestLevel = val[i];
		} else {
			// feeble attempt at countering the low end weighting of FFT.
			loudestLevel *=0.95;
		}
	}
	
	if(loudestIndex>0) {
		
		currentPeakFrequency = ofMap(loudestIndex, bottom, top, 0, 1);
		
		//loudestIndex = floor(ofMap(loudestIndex, bottom, top, 0, pipeOrganData.pipes.size()));
		//if(loudestIndex>=pipeOrganData.pipes.size()) loudestIndex = pipeOrganData.pipes.size()-1;
		
		//currentPipeIndex += (loudestIndex-currentPipeIndex) * 0.5;
		
		//if(currentPipeIndex<loudestIndex) currentPipeIndex++;
		//else if(currentPipeIndex>loudestIndex) currentPipeIndex--;
		
		//ofLine(pipeOrganData.pipes[(int)currentPipeIndex].top, pipeOrganData.pipes[(int)currentPipeIndex].bottom);
	} else {
		currentPeakFrequency = -1;
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if(key == 'a') cube1.visible = false;
	if(key == 's') cube2.visible = false;
	if(key == 'd') cube3.visible = false;
	
	
}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int numChannels){
	
		
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
	pipeOrganData.mouseDragged(x,y); 
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	cout << "MOUSE : " << x << " " << y << endl;
	pipeOrganData.mousePressed(x,y); 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	pipeOrganData.mouseReleased(x,y);

}


//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::exit() {
	laserGui.save();
	pipeOrganData.save();
	domeData.save();
	laserManager.warp.saveSettings();

}