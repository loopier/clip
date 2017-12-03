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
#include "BasePlayer.h"

namespace loopier {
    // TODO: Remove namespace 'cv'
    namespace cv{
        
        /// !!!:    Clumsy!  Won't compile if getPixels() and getTexture() don't
        //          return pixels or texture from a pointer
        typedef shared_ptr<ofImage> ImagePtr;

        class CvPlayer: public BasePlayer {

        public:
            CvPlayer();
            virtual ~CvPlayer();

            void setup();
            void update(ofEventArgs& e); // automatic update
            void update();
            void draw(ofEventArgs& e);  // automatic draw
            void draw();
            void draw(float x, float y, float w, float h);
            void exit();

            float getWidth() const;
            float getHeight() const;
            
            bool        loadResource(string resourcename);
            ofTexture & getTexture();
            ofPixels  & getPixels();
            
            void setInputPlayer(PlayerPtr player); //

            void toggleVisibility();
            void show();
            void hide();
            
            void setMinArea(float newArea);
            void setMaxArea(float newArea);
            void setThreshold(float newThreshold);
            void setFindHoles(bool findHoles);

        private:
            PlayerPtr   inputPlayer; // image to be processed
            ofImage     outputImage;
            ofFbo       maskFbo;    // just the blobs
            
            bool    bVisible;
            
            ofxCv::ContourFinder contourFinder;
            bool    bDrawContours;
            float   threshold;
            float   minArea;
            float   maxArea;
            float   bHoles;
            
        };

        typedef shared_ptr<CvPlayer> CvPlayerPtr;


        void setup();
        void setInputClip(string clipname);

        void setMinArea(float newArea);
        void setMaxArea(float newArea);
        void setThreshold(float newThreshold);
        void setFindHoles(bool findHoles);


        // TODO: Add visibility commands
    }
}

#endif
