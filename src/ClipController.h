//
//  ClipController.h
//  clip
//
//  Created by roger on 03/12/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//
//  A collection of functions to manage clips.  This is the control center for managing everything

#ifndef _ClipController
#define _ClipController


#include "ofMain.h"
#include "Clip.h"
#include "ofxYAML.h"
#include "Recorder.h"

namespace loopier {
    namespace app {
        /// \brief   Sets everything up
        void    init();
        void    update();
        /// \brief    Needed for controlling render order
        void    draw();
        void    mousePressed(int x, int y, int button);
        void    mouseReleased(int x, int y, int button);
        void    mouseDragged(int x, int y, int button);
        /// \brief   Sets mouse rectangle to fullscreen
        void    resetDetectionAreaRectangle();
        /// \brief  Record output
    } // namesapce app
    
    namespace resource {
        /// \brief   Lists all available resources
        void    setPath(string path);
        string& getPath();
        void    listAll();
        /// \brief   Checks if a resource exists
        bool    exists(string resourcename);
        /// \brief   Sets the syphon player of the given clip to listen to the given syphon server
        /// \param   clipname            String      Name of the clip showing the syphon input
        /// \param   syphonservername    String      Name of the syphon server
        /// \param   syphonserverapp     String      Name of the app hosting the syphon server
        void    setSyphonServerName(const string clipname, const string syphonservername, const string syphonserverapp);
    } // namespace resource
    
    namespace clip {
        /// \brief   Creates a clip named after a resource -- or an empty FramePlayer clip
        ClipPtr newClip(string clipname);
        /// \brief   Creates a clip with the given resource
        ClipPtr newClip(string clipname, string resourcename);
        /// \brief   Creates a clip with the given resource at the position of the biggest CV blob
        ClipPtr newClipFromBlob(string clipname, string resourcename="");
        void    removeClip(string clipname);
        
        /// \brief   Adds the clip to the selected clips vector
        void    selectClip(string clipname);
        /// \brief   Sets the order in which the clip will be drawn -- 0 is top; big numbers are at the bottom
        void    setClipDrawOrder(string clipname, int position);
        /// \brief   Sets clip to the front of all other clips
        void    bringClipToFront(string clipname);
        /// \brief   Raises clip in the drawing order
        void    bringClipForward(string clipname);
        /// \brief   Lowers clip in the drawing order
        void    sendClipBackward(string clipname);
        /// \brief   Sends clip below all other clips but above background (call setBackgroundClip if
        ///         you want it to stick at the bottom of everything
        void    sendClipToBack(string clipname);
        /// \brief   Keeps clip as the background
        void    setBackgroundClip(string clipname);
        /// \brief   Sets this clip as public and will be rendered in the public screen
        void    setPublicClip(const string clipname);
        /// \brief   Sets this clip as private and will be rendered only in private screen
        void    setPrivateClip(const string clipname);
        bool    isPublic(const string clipname);
        bool    isPrivate(const string clipname);
        /// \brief  Sets one clip as parent of another clip
        void    setParentClip(const string childclip, const string parentclip);
        void    removeParentClip(const string childclip);
        /// \brief  Sets the offset position of the child in relation to parent's position
        void    setOffsetToParentClip(const string childclip, const float xoffset, const float yoffset);
        
        //  \brief  Saves clip's images (frames) to a folder named after the clip
        //  \param  clipname    String      Name of the clip to be saved.  Will be used to
        //                                  find the directory or to create it (defaults to '+tmp'
        //                                  so it sticks to the top of the resources/frames directory
        void    saveImages(string clipname = "+tmp");
        
        /// \brief   Prints all clip names to console
        void    listAll();
        /// \brief   Prints clip rendering order
        void    listLayers();
        /// \brief   Deletes all clips
        void    clearAll();
        /// \brief   Checks if a clip exists
        bool    exists(string clipname);
        ClipPtr getClip(string clipname);
        
        // ----- SHOW CLIP NAMES----
        
        //// \brief  Shows names of clips
        void toggleNames();
        void showNames();
        void hideNames();
        
        // ----- USE ONE CLIP -----
        //// \brief  Adds a movie to a clip
        void addMovieToClip(const string clipname, const string moviename);
        // play
        void playClip(const string clipname);
        // stop
        void stopClip(const string clipname);
        // pause
        void pauseClip(const string clipname);
        // set speed
        void setClipSpeed(const string clipname, const float speed);
        //// \brief Set loop state (none | normal | palindrome)
        void setClipLoopState(const string clipname, const LoopType state);
        //// \brief  Mask one clip with any player
        void setClipMask(const string clipname, const string maskclipname);
        void enableClipMask(const string clipname);
        void disableClipMask(const string clipname);
        
        // ----- EDIT CLIP CONTENTS -----        //// \brief  Appends sourceclip's current image -masked with cv blobs- to cliprecorder frames
        /// TODO: make some kind of abstraction with the masking part
        void addFrame(const string recorderclip, const string sourceclip);
        //// \brief  Inserts clipplayer's current image to cliprecorder's current frame
        void insertFrame(const string recorderclip, const string sourceclip);
        void removeFrame(const string clipname);
        void clearFrames(const string clipname);
        void saveFrames(const string clipname);
        void loadFrames(const string clipname, const string resourcename);
        /// \brief  Goes to the first frame of the player
        void firstFrame(const string clipname);
        /// \brief  Plays one frame
        void nextFrame(const string clipname);
        /// \brief  Goes back one frame
        void previousFrame(const string clipname);
        /// \brief  Goes to last frame of the movie
        void lastFrame(const string clipname);
        /// \brief  Sets player's head to the given frame
        void goToFrame(const string clipname, const int framenumber);
        /// \brief  Saves clip's current status
        void saveClip(const string clipname);
        /// \brief  Loads a clip
        void loadClip(const string clipname);
        
        // ----- CLIP ATTRIBUTES -----
        // reset all attributes
        void resetClip(const string clipname);
        // move to
        //// \brief Move clip
        //// \param  x,y   float     Normalized position.  Will be scaled according to window dimensions
        void moveClipTo(const string clipname, const float x, const float y);
        //// \brief  Moves clip to the center of the screen
        void centerClip(const string clipname);
        // set anchor point
        // scale -- resize
        void scaleClip(const string clipname, const float scale);
        //// \brief  Change width of Clip
        //// \param  clipname    String
        //// \param  scale       Float   Signed and normalized -- positive or negative float -- 1 is default
        void setClipWidth(const string clipname, const float width);
        void setClipHeight(const string clipname, const float height);
        void scaleClip(const string clipname, const float scale);
        void scaleUpClip(const string clipname, const float amount=0.1);
        void scaleDownClip(const string clipname, const float amount=0.1);
        void resetClipScale(const string clipname);
        void setClipVFlip(const string clipname);
        void setClipHFlip(const string clipname);
        // toggle fullscreen
        void toggleFullscreenClip(const string clipname);
        //// \brief  Toggle clip visibility
        void toggleClipVisibility(const string clipname);
        void showClip(const string clipname);
        void hideClip(const string clipname);
        // tint
        void setClipColor(const string clipname, const float & grayscale);
        void setClipColor(const string clipname, const ofColor & color);
        void setClipColor(const string clipname, const float & grayscale);
        void setClipColor(const string clipname, const float & grayscale, const float & alpha);
        void setClipColor(const string clipname, const float & r, const float & g, const float & b );
        void setClipColor(const string clipname, const float & r, const float & g, const float & b, const float & a );
        // transparency
        void setClipAlpha(const string clipname, const float alpha);
        // reset attributes -- factory defaults
    } // namespace clip
    
    namespace cv {
        void    setDeviceId(const int n); // TODO: REMOVE when setting input clip works
        //// \brief  Sets image to be processed by CV
        void setInputClip(string clipname);
        //// \brief  Sets contourfinder's color
        void setColor(ofColor& color);
        void toggleVisibility();
        void show();
        void hide();
        //// \brief  Returns a B&W texture of the blobs
        ofTexture & getMask();
        ofTexture & getMaskTexture();
        ofPixels & getMaskPixels();
        //// \brief  Sets the minimum size for blobs to be detected
        void setMinArea(float newArea);
        //// \brief  Sets the maximum size for blobs to be detected
        void setMaxArea(float newArea);
        //// \brief  Sets the detection threshold
        void setThreshold(float newThreshold);
        //// \brief  Detect blobs indside blobs
        void setFindHoles(bool findHoles);
        //// \brief  Sets the maximum number of blobs detected
        void setMaxBlobs(int numBlobs);
        //// \brief  Sets an area of detection
        void setDetectionArea(ofRectangle & rect);
        /// \breif  Returns the bounding rect of the largest blob of the current cv input
        ofRectangle getBoundingRect();
        //// \breif  Returns the bounding rect of the given image
        ofRectangle getBoundingRect(ofImage & image);
        //// \breif  Adds the active blob to the selection
        void selectBlob();
        //// \breif  Removes the active blob from the selection
        void deselectBlob();
        //// \breif  Sets first blob as active
        void firstBlob();
        //// \breif  Sets next blob as active
        void nextBlob();
        //// \breif  Sets previous blob as active
        void previousBlob();
        //// \breif  Sets last blob as active
        void lastBlob();
    } // namespace cv
    
    namespace utils {
        
        //// \brief  Uses mask to set transparent pixels to the image
        ofImage getMaskedImage(ofImage & img, ofTexture & mask);
        //// \brief  Uses mask to set transparent pixels to the texture
        ofTexture   getMaskedTexture(ofTexture & texture, ofTexture & mask);
    }
}

#endif