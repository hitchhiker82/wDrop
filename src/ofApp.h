#pragma once

#include "ofMain.h"
#include "waterDrop.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    
    
        void keyPressed(int key);

		void gotMessage(ofMessage msg);
    
        void generate();
        void generate(ofVec2f _position, float _radius);
        void checkArea(WaterDrop *wDrop);
        void mergeDrops(WaterDrop *nDrop, WaterDrop *oDrop, WaterDrop *cDrop);
    
    void running();
        
        
        
        
        vector<WaterDrop*> mistImg;
        
        list<WaterDrop*> wDrops;
        ofImage wDropImg;
        
        int idCount;
    
    
    bool isStop;
    bool isTestScene;
    ofImage testImg;
    
};
