//
//  waterDrop.hpp
//  wDrop_v170527
//
//  Created by KimJunghoon on 27/05/2017.
//
//

#ifndef waterDrop_hpp
#define waterDrop_hpp

#include "ofMain.h"

class WaterDrop {
    
public:
    void setup();
    void update();
    void draw();
    
    WaterDrop();
    
    ofVec2f getPosition();
    float getRadius();
    int getId();
    
    void setId(int _id);
    
    bool isAlive();
    void setAlive(bool _sAlive);
    
    void setPosition(ofVec2f _position);
    void setRadius(float _radius);
    
    void updateImgIndex();
    int getImgIndex();
    
    deque<ofVec2f> pastPositions;
    deque<float> pastRadius;

    
    
private:
    
    ofVec2f position;
    float radius;
    int id;
    bool sAlive;
    
    int imgIndex;
    
    
};

#endif /* waterDrop_hpp */
