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

namespace loopier {
    namespace cv {
    
//    class Cv{
//        
//    public:
//        Cv();
//        virtual ~Cv();
//        
//        void setup();
//        void update();
//        void draw();
//        void exit();
//        
//        void setMinArea(float newArea);
//        void setMaxArea(float newArea);
//        void setThreshold(float newThreshold);
//        void setHoles(bool bHoles);
//        
//        void toggleVisibility();
//        void show();
//        void hide();
//        
//        // Sets image that will be processed
//        void setImage(ofImage & img);
//    private:
//        ofImage image; // Image to process
////        ofxCvGrayscaleImage  grayscaleImage;
//        ofxCv::ContourFinder contourFinder;
//        ofFbo   maskFbo;
//        ofPath  blobPath;
//        
//        float   minArea, maxArea, threshold;
//        bool    holes;
//        bool    visible;
//        
//        void update(ofEventArgs& e);
//        void draw(ofEventArgs& e);
//    };
    
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    // *                                                                       *
    // *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
    // *                                                                       *
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    
//    void update();
//    void draw();
    
    void setMinArea(float newArea);
    void setMaxArea(float newArea);
    void setThreshold(float newThreshold);
    void setHoles(bool bHoles);
}
}


#endif