//
//  Cv.h
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _Cv
#define _Cv


#include "ofMain.h"
#include "ofxCv.h"
//#include "ofxGui.h"

namespace loopier {
    
    class Cv{
        
    public:
        Cv();
        virtual ~Cv();
        
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
    };
    
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    // *                                                                       *
    // *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
    // *                                                                       *
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    
    void updateCv();
    void drawCv();
    
    void setCvMinArea(float newArea);
    void setCvMaxArea(float newArea);
    void setCvThreshold(float newThreshold);
    void setCvHoles(bool bHoles);
    
    void toggleCvVisibility();
    void showCv();
    void hideCv();
}


#endif