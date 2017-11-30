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
#include "ofxCv.h"
#include "CameraPlayer.h"

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
            
            bool loadResource(string resourcename);
            void setSourceCamera(CameraPtr src);
            
            void toggleVisibility();
            void show();
            void hide();
            
        private:
            CameraPtr sourceCamera;
            ofVideoGrabber cam;
            
            ofFbo   maskFbo;
            ofPath  blobPath;
            
            bool    visible;
        };
        
        typedef shared_ptr<CvPlayer> CvPlayerPtr;
        
        
        void setup();
        void setSourceCamera(string resourcename);
        void update();
        void draw();
        
        void setMinArea(float newArea);
        void setMaxArea(float newArea);
        void setThreshold(float newThreshold);
        void setHoles(bool bHoles);
        
        
        // TODO: Add visibility commands
    }
}

#endif