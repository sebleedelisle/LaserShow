// STILL TO DO :
// Test TDOAs in SonicHitFinder to show where TDOA radii should be - set up on mouse click.
// Add numbers to projections
// Check volume in sound clips - see if there's a volume threshold we can check? 


#pragma once

#include "ofMain.h"
#include "LaserManager.h"
#include "ParticleSystemManager.h"
#include "Synchroniser.h"
#include "PipeOrganData.h"
#include "DomeData.h"
#include "EffectLaserBeams.h"
#include "AnimationSequence.h"
#include "EffectDomeLines.h"
#include "EffectPipeOrganLines.h"
#include "EffectParticles.h"
#include "ColourSystemGradient.h"


#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#include "GLFW/glfw3native.h"

class ofApp : public ofBaseApp{

	public:
	
	ofApp() : particleSystemManager(*ParticleSystemManager::instance()), laserManager(*LaserManager::instance()) {
	};
	
	void setup();
	void update();
	void draw();
	void audioIn(float * input, int bufferSize, int numChannels);
	void windowResized(int width, int height);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void gotMessage(ofMessage msg);
	void exit();
	
	void drawEffects(); 
	
	void updatePeakFrequency(float * val, int numBands);
	
	void calculateScreenSizes();
	
	void drawSpirograph(ofPoint pos, int numrevolutions, float smallradius, float largeradius, float start, float end, float rotation);
	
	ofRectangle secondScreenRect; 
	
	PipeOrganData pipeOrganData;
	DomeData domeData; 
	//float currentPipeIndex = 0;
	
	float currentPeakFrequency; // unit value
	
	int screenWidth, screenHeight;

	ofxPanel appGui;
	ofxPanel laserGui;
	ofxPanel redGui;
	ofxPanel greenGui;
	ofxPanel blueGui;
	
	vector<ofxPanel*> panels;
	
	ofParameter<bool> laserDomePoints;
	ofParameter<bool> laserOrganPoints;
	ofParameter<bool> showGuideImage;
	ofParameter<bool> showCat; 
	
	
	LaserManager& laserManager;
	ParticleSystemManager& particleSystemManager;
	
	ofFbo projectorFbo;
	ofFbo uiFbo; 
	ofRectangle projectorPosition;
	ofImage guideImage;
	
	EffectLaserBeams effectLaserBeams;
	EffectDomeLines effectDomeLines;
	EffectPipeOrganLines effectPipeOrganLines;
	EffectParticles effectParticles;
	
	bool previewProjector; 
	

	ofSoundPlayer music;
	
	Synchroniser sync;
    

	ofImage smashingTitle;
	ofxSVG smashingCatSvg; 
	
	float soundPositionMS;
	float smoothVol;
	deque<float> volumes; 
	
	AnimationSequence screenAnimation;
	
	ofPolyline poly;
	

		
};
