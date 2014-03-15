#ifndef _CURVE_SQUARE
#define _CURVE_SQUARE


#include "ofMain.h"

class CurveSquare {
    
public:
    
    void init(float x, float y, ofColor col);
    void draw(float scale, bool fill);
    void drawPoly(float x, float y);
       
    // variables
    
    bool visible;
    ofPolyline cSquare;
    ofVec3f pos;
    float size;
    float rotation;
	ofColor colour;
   
    
  
    
    CurveSquare();
    CurveSquare(float x, float y, ofColor col);
    
private:
    
};

#endif
