#ifndef _ANGLE_MOVE
#define _ANGLE_MOVE



#include "ofMain.h"
#include "ArrowShape.h"

class AngleMove {
    
public:
    
    void init(vector<ArrowShape> as);
    void draw();
    void update();
   
    
    // variables
    
    bool active;
    
    ofVec3f pos;
    ofVec3f target;
    ofVec3f vel;
    
     vector<ArrowShape> arrows;
    
    float spring;
    float speed;
    float offsetAngle;
    
    AngleMove();
    AngleMove(vector<ArrowShape> as);

    
private:
    
};

#endif