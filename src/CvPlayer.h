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
            /// \brief  Returns the average center of the selected blobs
            ofPoint getCentroid();
            /// \brief  Returns the center of the bounding box of the given blob
            ofPoint getBlobCentroid(const int blobindex=0);
            /// \brief  Returns the bounding rectangle of the selected blobs
            ofRectangle getBoundingRect();
            /// \brief  Returns the bounding rectangle of the given blob
            /// \param  blobindex   Int     Index of the blob in the polylines vector
            ofRectangle getBlobBoundingRect(int blobindex=0);
            /// \brief  Returns the bounding rectangle of the largest blob in the given image
            ofRectangle getBoundingRect(ofPixels & pix);

            void toggleVisibility();
            void show();
            void hide();
            
            void setMinArea(float newArea);
            void setMaxArea(float newArea);
            void setThreshold(float newThreshold);
            void setFindHoles(bool findHoles);
            /// \brief  Sets the maximum number of blobs to be detected
            void setMaxBlobs(int numBlobs);
            /// \brief  Removes blobs that are outside the detection area
            void updateBlobs();
            /// \brief  Returns all blobs that are inside the detection area
            vector<ofPolyline> getBlobs();
            
            void    setDetectionArea(const ofRectangle & rect);
            /// \brief  Returns TRUE if the given rectangle is in the selection area
            bool    isInDetectionArea(const ofRectangle & rect);
            
            /// \brief  Set first blob as active
            void    firstBlob();
            /// \brief  Set next blob as active
            void    nextBlob();
            /// \brief  Set previous blob as active
            void    previousBlob();
            /// \brief  Set last blob as active
            void    lastBlob();
            /// \brief  Adds the blob at the given index to the selection
            void    selectBlob(const int index);
            /// \brief  Removes the blob at the given index from the selection
            void    deselectBlob(const int index);
            /// \brief  Selects the current blob
            void    selectCurrentBlob();
            /// \brief  Deselects the current blob
            void    deselectCurrentBlob();
            /// \brief  Selects all blobs
            void    selectAllBlobs();
            /// \brief  Deselects all blobs
            void    deselectAllBlobs();
            
            /// \brief  Returns TRUE if the blob represented by the index is selected
            bool    isBlobSelected(const int index);

        private:
            ofImage     outputImage;
            ofFbo       shapeFbo;           // just the blobs
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
            
            int currentBlob; ///< index of the blob that is selected
            vector<int> selectedBlobs; ///< indexes of selected blobs
            vector<ofPolyline> blobs; ///< blobs that are inside the detection area
            
//            CvPlayer(); // Disable default constructor.  You need to provide an input player
            
        };

        typedef shared_ptr<CvPlayer> CvPlayerPtr;
}

#endif
