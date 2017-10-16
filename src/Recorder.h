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
        
        void setMinArea(float newArea);
        void setMaxArea(float newArea);
        void setThreshold(float newThreshold);
        void setHoles(bool bHoles);
        
        void toggleVisibility();
        void show();
        void hide();
        
    private:
        ofVideoGrabber cam;
        ofxCv::ContourFinder contourFinder;
        ofFbo   maskFbo;
        ofPath  blobPath;
        
        float   minArea, maxArea, threshold;
        bool    holes;
        bool    visible;
        
//        ofxPanel gui;
//        ofParameter<float> minArea, maxArea, threshold;
//        ofParameter<bool> holes;
    };
    
    extern Recorder recorder;
    
    void newRecorder();
    void updateRecorder();
    void drawRecorder();
    
    void setRecorderMinArea(float newArea);
    void setRecorderMaxArea(float newArea);
    void setRecorderThreshold(float newThreshold);
    void setRecorderHoles(bool bHoles);
    
    void toggleRecorderVisibility();
    void showRecorder();
    void hideRecorder();
}


#endif