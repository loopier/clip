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
        
        /// !!!:    Clumsy!  Won't compile if getPixels() and getTexture() don't
        //          return pixels or texture from a pointer
        typedef shared_ptr<ofImage> ImagePtr;

        class CvPlayer: public BasePlayer {

        public:
            CvPlayer();  // TODO: -- DIABLE: make private
            CvPlayer(PlayerPtr input);
            virtual ~CvPlayer();

            void setup();
            void update(ofEventArgs& e); // automatic update
            void update();
            void draw(ofEventArgs& e);  // automatic draw
            void draw();
            void draw(float x, float y, float w, float h);
            void exit();
            
            // \brief   Sets the camera device ID
            void setDeviceId(int n);
            void setCamera(ofVideoGrabber & cam);

            float getWidth() const;
            float getHeight() const;
            
//            bool        loadResource(string resourcename);
            ofTexture & getTexture();
            ofPixels  & getPixels();
            ofImage &   getImage();
            vector<ofPolyline> getPolylines();
            
            void setInputPlayer(PlayerPtr player); // REMOVE: -- MOVED TO BASE CLASS

            void toggleVisibility();
            void show();
            void hide();
            
            void setMinArea(float newArea);
            void setMaxArea(float newArea);
            void setThreshold(float newThreshold);
            void setFindHoles(bool findHoles);
            
            void setDetectionArea(const ofRectangle & rect);

        private:
//            ofVideoGrabber  camera; // TODO: get input from other clips -- didn't manage to make it work yet
            
            PlayerPtr   inputPlayer; // image to be processed
            ofImage     outputImage;
            ofFbo       maskFbo;    // just the blobs
            ofFbo       detectionAreaFbo;
            ofRectangle detectionRectangle;
            ofPixels    pixels;
            
            bool    bVisible;
            
            ofxCv::ContourFinder contourFinder;
            bool    bDrawContours;
            float   threshold;
            float   minArea;
            float   maxArea;
            float   bHoles;
            
//            CvPlayer(); // Disable default constructor.  You need to provide an input player
            
        };

        typedef shared_ptr<CvPlayer> CvPlayerPtr;
}

#endif
