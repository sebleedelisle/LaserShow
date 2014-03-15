#pragma once

#include "ofMain.h"
#include "CurveSquare.h"
#include "ArrowShape.h"
#include "OctoplusShape.h"
#include "AngleMove.h"
#include "ShakeMove.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        CurveSquare cSq;
        ArrowShape arrow;
        OctoplusShape octo;
    
        AngleMove anglething;
        ShakeMove shakething;
    
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
