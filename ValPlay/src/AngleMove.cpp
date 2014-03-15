#include "AngleMove.h"



AngleMove::AngleMove(){
    //nuthin'
    active = false;
}

AngleMove::AngleMove(vector<ArrowShape> as){
    init(as);
    
}

void AngleMove::init(vector<ArrowShape> as) {
    arrows = as;
    active = true;
    
   }


void AngleMove::draw() {

    if (!active){
        return;
    }

    
    //draw the arrows
    for (int j = 0; j < arrows.size(); j++){
        arrows[j].draw(1, false);
    }
    
}

void AngleMove::update() {
    
   
        
        

    
}




