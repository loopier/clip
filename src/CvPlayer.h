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
            ofTexture & getTexture() const;
            ofPixels  & getPixels() const;
            
            void setInputPlayer(PlayerPtr player); //

            void toggleVisibility();
            void show();
            void hide();
            
            void toggleMask();
            void maskOn();
            void maskOff();
            void mask(bool onoff);

        private:
            PlayerPtr   inputPlayer; // image to be processed
            ImagePtr    inputImage; // to be passed to ofxCv methods
            ImagePtr    outputImage; 
            ofFbo       maskFbo;    // just the blobs
            ofImage     renderImage;  // image to be drawn
            ofPath      blobPath;
            
            ofPixels    pixels;
            ofTexture   texture;

            bool    bVisible;
            bool    bMask;
            bool    bDrawContours;
        };

        typedef shared_ptr<CvPlayer> CvPlayerPtr;


        void setup();
        void setInputClip(string clipname);
        void update();
        void draw();
        
        void toggleMask();
        void maskOn();
        void maskOff();
        void mask(bool onoff);

        void setMinArea(float newArea);
        void setMaxArea(float newArea);
        void setThreshold(float newThreshold);
        void setHoles(bool bHoles);


        // TODO: Add visibility commands
    }
}

#endif
