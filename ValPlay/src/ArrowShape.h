#ifndef _ARROW // if this class hasn't been defined, the program can define it
#define _ARROW // by using this if statement you prevent the class to be called more
// than once which would confuse the compiler

#include "ofMain.h"

class ArrowShape {
    
public:
    
    void init(float x, float y, ofColor col);
    void draw(float scale, bool fill);
    void drawPoly(float x, float y);
    
    // variables
    
    bool visible;
    ofPolyline arrowPoly;
    ofVec3f pos;
    ofVec3f target;
    ofVec3f vel;
    float size;
    float rotation;
	ofColor colour;
    
    
    ArrowShape();
    ArrowShape(float x, float y, ofColor col);
   
    
private:
    
};

#endif