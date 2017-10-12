//
//  Recorder.h
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _Recorder
#define _Recorder


#include "ofMain.h"
#include "ofxCv.h"
//#include "ofxGui.h"

namespace loopier {
    
    class Recorder{
        
    public:
        Recorder();
        virtual ~Recorder();
        
        void setup();
        void update();
        void draw();
        void exit();
        
    private:
        ofVideoGrabber cam;
        ofxCv::ContourFinder contourFinder;
        
        float   minArea, maxArea, threshold;
        bool    holes;
        
//        ofxPanel gui;
//        ofParameter<float> minArea, maxArea, threshold;
//        ofParameter<bool> holes;
    };
    
    extern Recorder recorder;
    
    void newRecorder();
    void updateRecorder();
    void drawRecorder();
}


#endif