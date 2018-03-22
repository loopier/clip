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
    
        class CvPlayer: public BasePlayer {

        public:
            CvPlayer();  // TODO: -- DIsABLE: make private
            CvPlayer(PlayerPtr input);
            virtual ~CvPlayer();

            void setup();
            void update(ofEventArgs& e); // automatic update
            void update();
            void draw(ofEventArgs& e);  // automatic draw
            void draw();
            void draw(float x, float y, float w, float h);
            void drawBlobs();
            void exit();

            float getWidth() const;
            float getHeight() const;
            /// \brief  Returns a B & W image of the blobs
            ofTexture & getTexture();
            /// \brief  Returns a B & W image of the blobs
            ofPixels  & getPixels();
            ofImage &   getImage();
            vector<ofPolyline> getPolylines();
            /// \brief  Returns the center of the bounding box of the biggest blob
            ofPoint getCentroid();
            /// \brief  Returns the bounding rectangle of the biggest blob
            /// \param  blobindex   Int     Index of the blob in the polylines vector
            ofRectangle  getBoundingRect(int blobindex=0);

            void toggleVisibility();
            void show();
            void hide();
            
            void setMinArea(float newArea);
            void setMaxArea(float newArea);
            void setThreshold(float newThreshold);
            void setFindHoles(bool findHoles);
            /// \brief  Sets the maximum number of blobs to be detected
            void setMaxBlobs(int numBlobs);
            
            void setDetectionArea(const ofRectangle & rect);

        private:
            ofImage     outputImage;
            ofFbo       shapeFbo;           // just the blobs
            ofFbo       detectionAreaFbo;   // used to mask the blobs
            ofFbo       maskFbo;            // the blobs in the detection area
            ofRectangle detectionRectangle;
            ofPixels    pixels;
            
            bool    bVisible;
            
            ofxCv::ContourFinder contourFinder;
            bool    bDrawContours;
            float   threshold;
            float   minArea;
            float   maxArea;
            float   bHoles;
            int     maxBlobs;
            
//            CvPlayer(); // Disable default constructor.  You need to provide an input player
            
        };

        typedef shared_ptr<CvPlayer> CvPlayerPtr;
}

#endif
