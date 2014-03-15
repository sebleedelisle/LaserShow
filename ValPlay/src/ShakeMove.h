#ifndef _SHAKE_MOVE
#define _SHAKE_MOVE

#include "ofMain.h"
#include "CurveSquare.h"

class ShakeMove {
    
public:
    
    void init(CurveSquare s, float rot, float its);
    void draw();
    void update();
    
    
    // variables
    
    bool active;
    float targetRot;
    float currentRot;
    float speed;
    float diff;
    float iterations;
    
    ofVec3f pos;
    CurveSquare square;
    CurveSquare internalSquare;
    
    ShakeMove();
    ShakeMove(CurveSquare s);
    //how do I make this take any shape? a based shape class?
    
    
private:
    
};

#endif