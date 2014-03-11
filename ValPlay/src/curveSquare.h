#ifndef _CURVE_SQUARE
#define _CURVE_SQUARE


#include "ofMain.h"

class curveSquare {
    
public:
    
    void update();
    void draw();
    void outlineShape(int x, int y);
       
    // variables
    
    ofPolyline cSquare;
    int x;
    int y;
  
    
    curveSquare();
    
private:
    
};

#endif
