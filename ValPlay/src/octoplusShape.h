#ifndef _OCTO_SHAPE
#define _OCTO_SHAPE


#include "ofMain.h"

class octoplusShape {
    
public:
    // methods, equivalent to specific functions of your class objects
    void update();
    void draw();
    
    // variables
    
    ofPolyline octoShape;
    float x;      // position
    float y;
  
    
    octoplusShape(); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
};

#endif
