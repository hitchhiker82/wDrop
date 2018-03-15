//
//  waterDrop.cpp
//  wDrop_v170527
//
//  Created by KimJunghoon on 27/05/2017.
//
//

#include "waterDrop.hpp"

WaterDrop::WaterDrop() {
    position = ofVec2f(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
    radius = ofRandom(2.8,3.);
    sAlive = true;
    updateImgIndex();
}


void WaterDrop::setup() {
    
    
}

void WaterDrop::update() {
    
//    if(radius>10) {
        position.y += (radius-7)*0.3;
//    }
    
    
    
}

void WaterDrop::draw() {
    
//    ofDrawCircle(position.x, position.y, radius);
}

ofVec2f WaterDrop::getPosition() {
    return position;
}

void WaterDrop::setPosition(ofVec2f _position) {
    position = _position;
}

float WaterDrop::getRadius() {
    return radius;
}

void WaterDrop::setRadius(float _radius) {
    radius = _radius;
}

int WaterDrop::getId() {
    return id;
}

void WaterDrop::setId(int _id) {
    id = _id;
}

bool WaterDrop::isAlive() {
    return sAlive;
}

void WaterDrop::setAlive(bool _sAlive = true) {
    sAlive = _sAlive;
}


void WaterDrop::updateImgIndex() {
    imgIndex = (int)position.y*ofGetWindowWidth()+(int)position.x;
}

int WaterDrop::getImgIndex() {
    return imgIndex;
}
