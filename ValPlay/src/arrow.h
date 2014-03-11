#ifndef _ARROW // if this class hasn't been defined, the program can define it
#define _ARROW // by using this if statement you prevent the class to be called more
// than once which would confuse the compiler

#include "ofMain.h"

class arrow {
    
public:
    
    void update();
    void draw();
    
    // variables
    float x;
    float y;
    ofPolyline arrowPoly;
    
    arrow(); // constructor - used to initialize an object, if no properties are passed
   
    
private:
    
};

#endif