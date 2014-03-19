#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofSetFrameRate(60);

	screenWidth = 1280;
	screenHeight = 960;
	
	guideImage.loadImage("img/LaserableArea2.jpg");
	music.loadSound("../../../Music/Down the Road Edit.aif");
	
	//smashingCatSvg.load("SmashingCat.svg");
	//smashingCatSvg.load("NyanCat.svg");
	svgs.push_back(ofxSVG());
	svgs.back().load("SmashingCat.svg");
	svgs.push_back(ofxSVG());
	
	svgs.back().load("BladeRunner_BR_logo.svg");
	svgs.push_back(ofxSVG());
	
	svgs.back().load("Internet_Explorer_10_logo.svg");
	svgs.push_back(ofxSVG());

	svgs.back().load("tardis.svg");
	svgs.push_back(ofxSVG());
	
	svgs.back().load("large_unicorn.svg");
	svgs.push_back(ofxSVG());

	
	previewProjector = false;
	
	projectorFbo.allocate(1024, 768, GL_RGB, 4);
	uiFbo.allocate(screenWidth, screenHeight, GL_RGB, 2); 

	projectorFbo.begin();
	ofSetColor(0);
	ofRect(0,0,1024,768);
	projectorFbo.end();
	
	ofSetColor(255);
	projectorPosition.set(screenWidth/5*2.14, screenHeight*4/5 * 0.99, screenWidth/5, screenHeight/5);
	
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
	
	laserGui.setup("LaserManager", "laserSettings.xml");
	laserGui.setPosition(ofPoint(screenWidth+220 - panelwidth - 10,10));
	laserGui.setVisible(true);
	laserGui.add(&laserManager.connectButton);
	laserGui.add(laserManager.parameters);
	
	laserGui.load();
	panels.push_back(&laserGui);
	
	appGui.setup("App");
	appGui.setPosition(ofPoint(screenWidth+220 - panelwidth - 10,10));
	appGui.setVisible(false);
	appGui.add(pipeOrganData.editable.set("Pipe Organ editable", false));
	appGui.add(laserDomePoints.set("laser dome points", false));
	appGui.add(laserOrganPoints.set("laser organ points", false));
	appGui.add(showGuideImage.set("show guide image", true));
	//appGui.add(showCat.set("show cat!", false));
	appGui.add(clappyBird.sensitivity.set("flappy sensitivity", 1,0,10)); 
	
	redGui.setup("Laser Red", "laserred.xml");
	redGui.add(laserManager.redParams );
    greenGui.setup("Laser Green", "lasergreen.xml");
	greenGui.add(laserManager.greenParams );
    blueGui.setup("Laser Blue", "laserblue.xml");
	blueGui.add(laserManager.blueParams );
    redGui.load();
	greenGui.load();
	blueGui.load();
	redGui.setPosition(ofPoint(10 ,10));
	greenGui.setPosition(ofPoint(10 +panelwidth + 10,10));
	blueGui.setPosition(ofPoint(10 +panelwidth*2 + 20,10));
	
	
	//appGui.load();
	panels.push_back(&appGui);

	
	clappyBirdActive = false;
	
	soundPositionMS = 0;
	
	sync.tempo = 111;
	sync.startPosition = (60000/111) - 5; // start after 1 beat intro

	
	pipeOrganData.load();
	domeData.init();
	domeData.load();
	
	domeData.gui.setPosition(ofPoint(screenWidth+220 - panelwidth - 10,10));
	domeData.gui.setVisible(false);
	
	panels.push_back(&domeData.gui);
	
	effectDomeLines.setDomeData(&domeData);
	effectPipeOrganLines.setObjects(&pipeOrganData, &particleSystemManager);
	effectParticles.setObjects(&pipeOrganData, &domeData);
	
	
	
	smoothVol = 0;
	
	calculateScreenSizes();
	smoothedInputVolume = 0;
	soundStream.setup(this, 0, 2, 48000, 1024, 1);
	left.resize(1024);
	right.resize(1024);
}


//--------------------------------------------------------------
void ofApp::update(){
	
	float deltaTime = ofClamp(ofGetLastFrameTime(), 0, 0.2);
	ofSoundUpdate();
	laserManager.update();
	if(music.getIsPlaying()) soundPositionMS = music.getPositionMS();

	sync.update(soundPositionMS);
	
	screenAnimation.update();
	
	particleSystemManager.update(deltaTime);
	effectLaserBeams.update(deltaTime);
	effectDomeLines.update(deltaTime);
	effectPipeOrganLines.update(deltaTime);
	
	if(clappyBirdActive) clappyBird.update(smoothedInputVolume, deltaTime);
	else clappyBird.reset();
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
	
	smoothVol += (vol-smoothVol) *0.5;
	volumes.push_front(smoothVol);
	if(volumes.size()>500) volumes.pop_back();
	
	
	uiFbo.begin();
	ofSetupScreenPerspective(1280,960,50);

	ofSetColor(0);
	ofFill(); 
	ofRect(0,0,screenWidth, screenHeight);
	ofNoFill();
	ofSetColor(255);
	
	if(!previewProjector) {
		ofSetColor(200);
		if(showGuideImage) guideImage.draw(0,0,screenWidth, screenHeight);
		ofSetColor(255);
		ofRect(projectorPosition.x-1, projectorPosition.y-1, projectorPosition.width+2, projectorPosition.height+2);
		projectorFbo.draw(projectorPosition);
		
		pipeOrganData.draw();
		
		if((pipeOrganData.editable) && (laserOrganPoints)){
			vector<Pipe>& pipes = pipeOrganData.pipes;
			for(int i = 0; i< pipes.size(); i++) {
				Pipe& pipe = pipes[i];
				if((pipe.topDragging) || (pipe.bottomDragging)) {
					laserManager.addLaserLineEased(pipe.top, pipe.bottom, ofColor::white);
				} else {
					laserManager.addLaserLineEased(pipe.top, pipe.bottom, ofColor::cyan);
				} 
			}
		}
		ofSetupScreenPerspective(1280,960,50);

		domeData.draw();
		
		
		if((domeData.editable) && (laserDomePoints)){
			vector<ofPoint> points = domeData.getLevelPoints();
			
			for(int i = 0; i<points.size(); i++) {
				laserManager.addLaserDot(points[i], ofColor :: white);
				//ofSetColor(255,0,0);
				//ofCircle(points[i], 20);
				
			}
		}

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
	ofRect((numBands+2)*barWidth, 0, barWidth-1, smoothedInputVolume*1000 );
	ofSetColor(255);
	
	
	
	ofNoFill();
	
	float time = soundPositionMS/1000.0f;

	ofDrawBitmapString(ofToString(time), 0,25);
	
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
	
	ofPopMatrix(); 
	
	ofPopStyle();
	projectorFbo.end();

	//----------------- FBO END --------------------------------

		
	ofPopMatrix();
	
	uiFbo.begin();
	ofSetupScreenPerspective(1280,960,50);

	
	// EFFECTS ---------------------------------------------
	
	drawEffects();
	if((currentSVG>=0) && (currentSVG<svgs.size())) {
		laserManager.addLaserSVG(svgs[currentSVG], ofPoint(950,580),ofPoint(0.5,0.5));
		laserManager.addLaserSVG(svgs[currentSVG], ofPoint(390,580),ofPoint(0.5,0.5));
		
	}
	if(clappyBirdActive) clappyBird.draw();
	
	
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
	
	projectorFbo.draw(secondScreenRect); 
	
	// GUI PANELS
	for(int i = 0; i<panels.size(); i++) {
		panels[i]->draw();
	}
	redGui.draw();
	greenGui.draw();
	blueGui.draw();
}

void ofApp :: drawEffects() {
	
	//ofColor col;
	//col.setHsb((ofGetElapsedTimeMillis()/4)%255, 255, 255);
	//laserManager.addLaserText(" ANDY CLARKE!", ofPoint(640,480), 10,col, true);
	
	if((sync.currentBar>=24) && (sync.currentBar<28)) {
		// CHEVRONS
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(4);
	}
	if((sync.currentBar>=28) && (sync.currentBar<30)) {
		drawSpirograph(ofPoint(350,600), 20,50,80,ofMap(sync.currentBarFloat, 29, 30,0,1, true),ofMap(sync.currentBarFloat, 28, 29,0,1, true),
					   ofMap(sync.currentBarFloat, 28, 30, 180,0));
		effectDomeLines.setMode(0);
	}
	if((sync.currentBar>=30) && (sync.currentBar<32)) {
		drawSpirograph(ofPoint(1000,600), 20,80,60,ofMap(sync.currentBarFloat, 31, 32,0,1, true),ofMap(sync.currentBarFloat, 30, 31,0,1, true),
					   ofMap(sync.currentBarFloat, 28, 30, 180,0));
		effectDomeLines.setMode(0);
	}
	// SOLO
	if((sync.currentBar >= 32) && (sync.currentBar < 40)) {
		effectPipeOrganLines.setMode(2);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(0);
	}
	if((sync.currentBar >= 35) && (sync.currentBar < 36)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(0);
		if(sync.barTriggered) effectParticles.makeStarBurst();
	}
	if((sync.currentBar >= 40) && (sync.currentBar < 41)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(0);
	}
	if((sync.currentBarFloat > 41.5) && (sync.currentBar < 42)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(3);
	}// POST SOLO BUILD (DOME RINGS)
	if((sync.currentBar >= 42) && (sync.currentBar < 46)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(1);
	}
	// POST SOLO BUILD (DOME LINES)
	if((sync.currentBar >= 46) && (sync.currentBar < 50)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(2);
	}
	// MELLOW DROP OUT - WHITE LASER BEAMS
	if((sync.currentBar >= 50) && (sync.currentBar < 54)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 1;
		effectDomeLines.setMode(0);
	}
	// COLOURED LASER BEAMS
	if((sync.currentBar >= 54) && (sync.currentBar < 56)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 2;
		effectDomeLines.setMode(0);
	}
	// DROP OUT BEFORE OUTRO
	if((sync.currentBar >= 57) && (sync.currentBar < 59)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(3);
	}
	
	if((sync.currentBar>=59) && (sync.currentBar<74)) {
		if ((sync.barTriggered) && ((sync.currentBar==59)||(sync.currentBar == 63))) effectParticles.makeStarBurst();
			
		effectPipeOrganLines.setMode(3);
		effectLaserBeams.mode = 0;
		if((sync.currentBar>=67) && (sync.currentBar<73))  effectDomeLines.setMode(5);
		else effectDomeLines.setMode(0);
		if(sync.currentBar>=71) effectDomeLines.doSecondCircleRow = true;
	}
	//effectDomeLines.setMode(3;
	if((sync.currentBar >= 74) && (sync.currentBar < 75)) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(3);
		
	}
	if((sync.currentBar == 74) && (sync.currentBeat == 3) && (sync.eighthTriggered)){

		effectParticles.makeStarBurst(0.5);
		effectParticles.makeStarBurst(0.3);
	}
	
	if(sync.currentBar > 75) {
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(0);
		ofColor col;
		col.setHsb((ofGetElapsedTimeMillis()/4)%255, 255, 255);
		laserManager.addLaserText(" THANKS!", ofPoint(640,480), 10,col, true);
		
	}
	
	particleSystemManager.draw();
	effectLaserBeams.draw(laserManager,smoothVol);
	effectDomeLines.draw(sync, smoothVol, laserManager);
	effectPipeOrganLines.draw(sync, smoothVol, laserManager, currentPeakFrequency);


}

void ofApp ::  drawSpirograph(ofPoint pos, int numrevolutions, float smallradius, float largeradius, float start, float end, float rotation) {
	
	poly.clear();
	ColourSystemGradient* grad = new ColourSystemGradient();
	
	int totaldivisions =360;
	//int numrevolutions = 20;
	//float smallradius = 50;
	//float largeradius = 200;
	ofPoint p;
	for(int i = totaldivisions*start; i<=totaldivisions*end; i++) {
		float angle1 = ofMap(i, 0, totaldivisions, 0, 360);
		float angle2 = ofMap(i, 0, totaldivisions, 0, 360*numrevolutions);
		
		float sr = smallradius;
		if((i/10)<volumes.size()) sr*= ofMap(volumes[i/10],0,1,0.8,1.1,true);
		p.set(sr,0,0);
		
		p.rotate(angle2, ofPoint(0,0,1));
		p.x+=largeradius;
		p.rotate(angle1+rotation, ofPoint(0,0,1));
		
		p+=pos;
		//p.z += i;
		
		poly.addVertex(p);
		int hue = ((int)ofMap(i,0,totaldivisions, 0, 255))%255;
		ofColor c;
		
		float brightness = 255;
		float fadedistance = 5; 
		
		if(i<totaldivisions*start+20) {
			brightness = ofMap(i, totaldivisions*start,totaldivisions*start+20, 0,255 );
			
		}

		if(i>totaldivisions*end-20) {
			brightness = ofMap(i, totaldivisions*end,totaldivisions*end-20, 0,255 );
			
		}
		c.setHsb(hue, 255,brightness);
		grad->addColourStop(c, ofMap(i,totaldivisions*start,totaldivisions*end, 0, 1));
		
		
		
	}
	//poly.draw();
	laserManager.addLaserPolyline(poly, grad);
	
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
		
		redGui.setVisible(laserGui.getVisible());
		greenGui.setVisible(laserGui.getVisible());
		blueGui.setVisible(laserGui.getVisible());
			
	}
	if(key == 'w') laserManager.showWarpPoints = !laserManager.showWarpPoints;
	if(key == ' ') previewProjector = !previewProjector;
	if(key == OF_KEY_DOWN) {
		music.setPosition(0);
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(0);

		music.play();
	}
	if(key == OF_KEY_LEFT) {
		soundPositionMS = sync.getMSForBarNumber(sync.currentBar-1);
		music.setPositionMS(soundPositionMS);
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(0);
	} else if(key == OF_KEY_RIGHT) {
		soundPositionMS = sync.getMSForBarNumber(sync.currentBar+1);
		music.setPositionMS(soundPositionMS);
		effectPipeOrganLines.setMode(0);
		effectLaserBeams.mode = 0;
		effectDomeLines.setMode(0);
	}
	if(key =='l') laserManager.showLaserPath = !laserManager.showLaserPath;
		
		
	
	if(key == 'p') {
		if(music.getIsPlaying()) {
			
			music.stop();
		} else {

			music.play();
			music.setPositionMS(soundPositionMS);
			effectPipeOrganLines.setMode(0);
			effectLaserBeams.mode = 0;
			effectDomeLines.setMode(0);
		}
	
	}
	if(key=='c') {
		currentSVG++;
		if(currentSVG>=svgs.size()) currentSVG = -1; 
	}
	if(key=='v') clappyBirdActive = !clappyBirdActive;
    

	if(key == '1') {
		effectLaserBeams.mode = 0;
		effectPipeOrganLines.setMode(0);
		effectDomeLines.setMode(1);
	}
	if(key == '2') {
		effectLaserBeams.mode = 0;
		effectPipeOrganLines.setMode(0);
		effectDomeLines.setMode(2);
	}
	if(key == '3') {
		effectLaserBeams.mode = 1;
		effectPipeOrganLines.setMode(0);
		effectDomeLines.setMode(0);
	}
	if(key == '4') {
		effectLaserBeams.mode = 2;
		effectPipeOrganLines.setMode(0);
		effectDomeLines.setMode(0);
	}
	if(key == '5') {
		effectLaserBeams.mode = 0;
		effectPipeOrganLines.setMode(1);
		effectDomeLines.setMode(0);
	}
	if(key == '6') {
		effectLaserBeams.mode = 0;
		effectPipeOrganLines.setMode(2);
		effectDomeLines.setMode(0);
	}
	if(key == '7') {
	
		effectLaserBeams.mode = 0;
		effectPipeOrganLines.setMode(3);
		effectDomeLines.setMode(0);
	}
	
	if(key == '0') {
		effectLaserBeams.mode = 0;
		effectPipeOrganLines.setMode(0);
		effectDomeLines.setMode(0);
	}
	
	if(key == 's') {
		effectParticles.makeStarBurst(0.5);
	}

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
void ofApp::windowResized(int width, int height){
	
	
	calculateScreenSizes();
}


void ofApp::calculateScreenSizes(){
    int monitorCount;
	
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	
	//cout << "RESIZE" << " " << ofGetWindowMode()<< endl;
   // screens.clear();
    
    int leftMost = 0,
	topMost = 0;
    
	vector<ofRectangle> screens;
	
    for(int i = 0; i < monitorCount; i++){
		
		ofRectangle screen;
		
		int x=0,
		y=0,
		w=0,
		h=0;
		
        glfwGetMonitorPos(monitors[i],&x,&y);
        const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[i]);
		screen.x = x;
		screen.y = y;
        screen.width = desktopMode->width;
        screen.height = desktopMode->height;
        
        screens.push_back(screen);
        cout << i << " " << screen << endl;
		if( leftMost > screen.x ) leftMost = screen.x;
		if( topMost > screen.y ) topMost = screen.y;
		
    }
    
    for(int i = 0; i < monitorCount; i++){
	//	screens[i].x -= leftMost;
	//	screens[i].y -= topMost;
		
    }
    
	//std::sort( screens.begin(), screens.end(), screenSort );
	
	//uiScreenRect = screens.back();
	
	
	if(screens.size()>1) {
		secondScreenRect = screens[1];
	} else {
		secondScreenRect.set(screens[0].getRight(), screens[0].getTop(), 1024,768);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	
	
}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int numChannels){
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
	
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
		
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedInputVolume *= 0.8;
	smoothedInputVolume += 0.5 * curVol;
	smoothedInputVolume = curVol;
	//bufferCounter++;

		
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
	redGui.save();
	greenGui.save();
	blueGui.save();
	
	laserGui.save();
	pipeOrganData.save();
	domeData.save();
	laserManager.warp.saveSettings();

}

