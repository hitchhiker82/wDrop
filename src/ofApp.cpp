#include "ofApp.h"
#define WIDTH 1024
#define HEIGHT 768
#define WMAXSIZE 26



//--------------------------------------------------------------
void ofApp::setup(){
    
//    ofSetBackgroundColor(100, 0, 255);
    ofSetBackgroundColor(0);
    
    testImg.allocate(WIDTH, HEIGHT, OF_IMAGE_GRAYSCALE);
    
    wDropImg.load("wDrop.png");
    
    mistImg.resize(WIDTH*HEIGHT);

    idCount = 0;
    
    generate();
    
    
    isTestScene = false;
    isStop = false;
    
    
    for(int i=0; i<5000; i++) {
        running();
        if(ofGetFrameNum()%30==0)
        generate();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if(ofGetKeyPressed('u')){
        generate(ofVec2f(mouseX,mouseY),ofRandom(1,3));
    }
    
    if(!isStop){
    //
    running();
        
    if(ofGetFrameNum()%30==0)
    generate();
      //
    } else {
        testImg.setColor(ofColor(0));
        
        
        for(int i=0; i<mistImg.size(); i++) {
            if(mistImg[i] != NULL) {
                if(mistImg[i]->isAlive())
                    testImg.setColor(i, ofColor(255));
            }
        }
        
        
        
        testImg.update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ofEnableAlphaBlending();
    
//    ofSetColor(80, 0, 245);
    ofSetColor(100, 0, 255);
    
    
//    list<WaterDrop*>::iterator tDrop = wDrops.begin();
    
    ofPushStyle();
    
    for(list<WaterDrop*>::iterator tDrop=wDrops.begin(); tDrop != wDrops.end();){
        
        if((*tDrop)->isAlive()){
//            ofSetColor((*tDrop)->tColor);
            
            if((*tDrop)->pastPositions.size()>1) {
                
                for(int i = 0; i<(*tDrop)->pastPositions.size(); i++) {
                    
                    int alpha = 255/(*tDrop)->pastPositions.size() * (i+1);
                    ofPushStyle();
                    ofSetColor(80, 0, 245, alpha);
                    
                    wDropImg.draw((*tDrop)->pastPositions[i].x - (*tDrop)->pastRadius[i], (*tDrop)->pastPositions[i].y - (*tDrop)->pastRadius[i], (*tDrop)->pastRadius[i]*2, (*tDrop)->pastRadius[i]*2);
                    ofPopStyle();
                    
                }
                
                
            } else
            wDropImg.draw((*tDrop)->getPosition().x - (*tDrop)->getRadius(), (*tDrop)->getPosition().y - (*tDrop)->getRadius(), (*tDrop)->getRadius()*2, (*tDrop)->getRadius()*2);
            
            tDrop++;
        } else {
            (*tDrop)->~WaterDrop();
            (*tDrop) = NULL;
            wDrops.erase(tDrop++); //
        }
    }
    
    
    ofPopStyle();
    
    
    ofPushStyle();
    ofSetColor(255);
    if(isTestScene) testImg.draw(0,0);
    ofPopStyle();
    
    ofSetColor(255);
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);
    
}


//--------------------------------------------------------------
void ofApp::generate(){
    
    WaterDrop *aDrop = new WaterDrop();
    aDrop->setId(idCount);
    idCount++;
    
    wDrops.push_back(aDrop);
//    mistImg[aDrop->getImgIndex()] = aDrop;
    
    checkArea(aDrop);
    
}

void ofApp::generate(ofVec2f _position, float _radius){
    
    WaterDrop *aDrop = new WaterDrop();
    aDrop->setId(idCount);
    idCount++;
    
    aDrop->setPosition(_position);
    aDrop->setRadius(_radius);
    aDrop->updateImgIndex();
    
    wDrops.push_back(aDrop);
//    mistImg[aDrop->getImgIndex()] = aDrop;
    
    checkArea(aDrop);
    
}

//--------------------------------------------------------------
void ofApp::checkArea(WaterDrop *_wDrop){
    
    ofVec2f sPoint = ofVec2f(_wDrop->getPosition().x-_wDrop->getRadius()-WMAXSIZE, _wDrop->getPosition().y-_wDrop->getRadius()-WMAXSIZE);
    ofVec2f ePoint = ofVec2f(_wDrop->getPosition().x+_wDrop->getRadius()+WMAXSIZE, _wDrop->getPosition().y+_wDrop->getRadius()+WMAXSIZE);
    
    
    if(sPoint.x < 0) sPoint.x = 0;
    if(sPoint.y < 0) sPoint.y = 0;
    if(ePoint.x > ofGetWindowWidth()-1) ePoint.x = ofGetWindowWidth()-1;
    if(ePoint.y > ofGetWindowHeight()-1) ePoint.y = ofGetWindowHeight()-1;
    
    WaterDrop cDrop;
    cDrop = *_wDrop;
    
    bool isMerged = false;
    
    for(int i = sPoint.x; i<ePoint.x; i++) {
        for(int j = sPoint.y; j<ePoint.y; j++){
            int aPosition = j*ofGetWindowWidth()+i;
            
            if(mistImg[aPosition] != NULL && mistImg[aPosition]->getId() != _wDrop->getId() && mistImg[aPosition]->isAlive()){
                
                
                float dist = ofDist(_wDrop->getPosition().x, _wDrop->getPosition().y, mistImg[aPosition]->getPosition().x, mistImg[aPosition]->getPosition().y);
                
                
                if(dist < _wDrop->getRadius() + mistImg[aPosition]->getRadius()) {
                
                    mergeDrops(_wDrop, mistImg[aPosition], &cDrop);
                    isMerged = true;
                }
            }
        }
    }
    
    _wDrop->updateImgIndex();
    if(isMerged) checkArea(_wDrop);
    
    mistImg[_wDrop->getImgIndex()] = _wDrop;
}


//--------------------------------------------------------------
void ofApp::mergeDrops(WaterDrop *nDrop, WaterDrop *oDrop, WaterDrop *cDrop){
    
    float nSize = nDrop->getRadius();
    float oSize = oDrop->getRadius();
    float cSize = cDrop->getRadius();
    
    ofVec2f nPosition = nDrop->getPosition();
    ofVec2f oPosition = oDrop->getPosition();
    ofVec2f cPosition = cDrop->getPosition();
    
    
    float rSize = sqrt(pow(nSize,2)+pow(oSize,2));
    
    float sizeRatio = oSize/(cSize+oSize);
    float nx = nPosition.x + ((oPosition.x-cPosition.x)*sizeRatio);
    float ny = nPosition.y + ((oPosition.y-cPosition.y)*sizeRatio);
    
    if(nx > ofGetWindowWidth()-1) nx = ofGetWindowWidth()-1;
    if(ny > ofGetWindowHeight()-1) ny = ofGetWindowHeight()-1;
    if(nx < 0) nx = 0;
    if(ny < 0) ny = 0;
    
    
    if(rSize > WMAXSIZE/2.) rSize = WMAXSIZE/2.;
    
    nDrop->setRadius(rSize);
    nDrop->setPosition(ofVec2f(nx,ny));
    nDrop->updateImgIndex();
    
    oDrop->setAlive(false);
    
}

void ofApp::running() {
    
    
    for(list<WaterDrop*>::iterator tDrop=wDrops.begin(); tDrop != wDrops.end();){
        
        if((*tDrop)->getRadius()>7 && (*tDrop)->isAlive()){
            
            mistImg[(*tDrop)->getImgIndex()] = NULL;
            
            (*tDrop)->pastPositions.push_back((*tDrop)->getPosition());
            (*tDrop)->pastRadius.push_back((*tDrop)->getRadius());
            
            if((*tDrop)->pastPositions.size()>6) {
                (*tDrop)->pastPositions.pop_front();
                (*tDrop)->pastRadius.pop_front();
            }
            
            (*tDrop)->update();
            
            if((*tDrop)->getRadius()>10 && (*tDrop)->getPosition().y<ofGetWindowHeight()-1) {
                float rSize = ofRandom(1.0, 2.5);
                float tSize = (*tDrop)->getRadius();
                generate(ofVec2f((*tDrop)->getPosition().x,(*tDrop)->getPosition().y-(*tDrop)->getRadius()-rSize*2.2),rSize);
                (*tDrop)->setRadius(sqrt(pow(tSize,2) - pow(rSize, 2)));
            }
            
            
            if((*tDrop)->getPosition().y > ofGetWindowHeight()-1 || (*tDrop)->getPosition().x > ofGetWindowWidth()-1 || (*tDrop)->getPosition().x < 0 || (*tDrop)->getPosition().y<0) {
                (*tDrop)->setAlive(false);
            }
            else {
            checkArea((*tDrop));
            (*tDrop)->updateImgIndex();
            mistImg[(*tDrop)->getImgIndex()] = *tDrop;
            }
        }
        tDrop++;
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='g') {
        generate();
    }
    
    if(key=='s') {
        
        isStop = !isStop;
        
    }
    
    if(key=='t') {
        
        isTestScene = !isTestScene;

    }

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


