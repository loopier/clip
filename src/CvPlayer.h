//
//  CvPlayer.h
//  clip
//
//  Created by roger on 30/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _CvPlayer
#define _CvPlayer


#include "ofMain.h"
#include "BasePlayer.h"
#include "ofxCv.h"

namespace loopier {
    namespace cv{
        
        class CvPlayer: public BasePlayer{
            
        public:
            CvPlayer();
            virtual ~CvPlayer();
            
            void setup();
            void update(ofEventArgs& e);
            void update();
            void draw(ofEventArgs& e);
            void draw();
            void draw(float x, float y, float w, float h);
            void exit();
            
            void setMinArea(float newArea);
            void setMaxArea(float newArea);
            void setThreshold(float newThreshold);
            void setHoles(bool bHoles);
            
            void toggleVisibility();
            void show();
            void hide();
            
            void setImage(ofImage & img);
        private:
            
            ofImage sourceImage;
            ofFbo   maskFbo;
            ofPath  blobPath;
            
            float   minArea, maxArea, threshold;
            bool    holes;
            bool    visible;
        };
        
        void setMinArea(float newArea);
        void setMaxArea(float newArea);
        void setThreshold(float newThreshold);
        void setHoles(bool bHoles);
    }
}

#endif