#pragma once

#include "ofMain.h"
#include "curveSquare.h"
#include "ArrowShape.h"
#include "octoplusShape.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        CurveSquare cSq;
        ArrowShape arrow;
        OctoplusShape octo;
    
        vector<CurveSquare> squares;
        vector<ArrowShape> arrows;

        void splitArrows();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
