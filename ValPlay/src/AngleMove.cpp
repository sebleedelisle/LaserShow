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
    
    for (int i = 0; i < arrows.size(); i++){
    offsetAngle = ( 2*PI )/arrows.size();
    float angle = offsetAngle;
        cout << "angle " << i << angle << endl;
        
    float radius = 150;
    target.set((radius*sin(angle*i)),(radius*cos(angle*i)));
    arrows[i].target = target;
        
      cout << "init target for  " << i << " " << target.x << "," << target.y << endl;
        
    }
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
    
    //arrows[2].pos.x = ofRandom(200);
    //arrows[2].pos.y = ofRandom(500);
    
    
    for (int i = 0; i < arrows.size(); i++){
       
        cout << "i " << i << endl;
        
         cout << "arrow pos at start " << arrows[i].pos.x << "," << arrows[i].pos.y << endl;
        
        target.set(arrows[i].target.x, arrows[i].target.y);
        cout << "starting target " << target.x << "," << target.y << endl;
        
        pos.set(arrows[i].pos.x, arrows[i].pos.y);
        cout << "pos at start " << pos.x << "," << pos.y << endl;
        
        vel.set(arrows[i].vel.x, arrows[i].vel.y);
        cout << "vel at start " << arrows[i].vel.x << "," << arrows[i].vel.y << endl;
        vel*=spring;
        
        cout << "vel after spring " << vel.x << "," << vel.y << endl;
        
        //how much further to target
        ofVec3f diff = target-pos;
        
        cout << "diff " << diff << endl;
        
        diff= diff * speed;
        vel+=(diff);
        
        //save back our values
        arrows[i].pos.x = pos.x;
        arrows[i].pos.y = pos.y;
        
        arrows[i].vel.set(vel);
        
        cout << "arrow at end " << arrows[i].pos.x << endl;
     
  
        
        
    }
    
}




