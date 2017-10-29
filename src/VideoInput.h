//
//  VideoInput.h
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _VideoInput
#define _VideoInput


#include "ofMain.h"
#include "ofxCv.h"
//#include "ofxGui.h"

namespace loopier {
    
    class VideoInput{
        
    public:
        VideoInput();
        virtual ~VideoInput();
        
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
    
    extern VideoInput videoInput;
    
    void newVideoInput();
    void updateVideoInput();
    void drawVideoInput();
    
    void setVideoInputMinArea(float newArea);
    void setVideoInputMaxArea(float newArea);
    void setVideoInputThreshold(float newThreshold);
    void setVideoInputHoles(bool bHoles);
    
    void toggleVideoInputVisibility();
    void showVideoInput();
    void hideVideoInput();
}


#endif