#ifndef _OCTO_SHAPE
#define _OCTO_SHAPE


#include "ofMain.h"

class OctoplusShape {
    
public:
    void init(float x, float y, ofColor col);
    void draw(float scale, bool fill);
    void drawPoly(float x, float y);
    
    // variables
    
    bool visible;
    ofPolyline octoShape;
    ofVec3f pos;
    float size;
	ofColor colour;
    float rotation;
    
    OctoplusShape();
    OctoplusShape(float x, float y, ofColor col);
    
private:
    
};

#endif
