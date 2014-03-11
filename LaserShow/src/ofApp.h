// STILL TO DO :
// Test TDOAs in SonicHitFinder to show where TDOA radii should be - set up on mouse click.
// Add numbers to projections
// Check volume in sound clips - see if there's a volume threshold we can check? 


#pragma once

#include "ofMain.h"
#include "LaserManager.h"
#include "Synchroniser.h"
#include "SoundShape.h"
#include "PipeOrganData.h"
#include "DomeData.h"

class ofApp : public ofBaseApp{

	public:
	void setup();
	void update();
	void draw();
	void audioIn(float * input, int bufferSize, int numChannels);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void gotMessage(ofMessage msg);
	void exit();
	
	void drawPipeOrgan(float * val, int numBands);
	
	PipeOrganData pipeOrganData;
	DomeData domeData; 
	float currentPipeIndex = 0;
	
	int screenWidth, screenHeight;

	ofxPanel gui;

	
	LaserManager laserManager;
	
	ofFbo projectorFbo;
	ofRectangle projectorPosition;
	ofImage guideImage; 
	bool previewProjector; 
	

	ofSoundPlayer music;
	
	Synchroniser sync; 
	

	ofImage smashingTitle;
	
	SoundShape cube1;
	SoundShape cube2;
	SoundShape cube3;
	
	float soundPositionMS;
	


		
};
