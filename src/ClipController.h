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

namespace loopier {
    namespace app {
        // \brief   Sets everything up
        void    init();
        void    update();
        // biref    Needed for controlling render order
        void    draw();
    }
    
    namespace resource {
        // \brief   Lists all available resources
        void    setPath(string path);
        string& getPath();
        void    listAll();
        // \brief   Checks if a resource exists
        bool    exists(string resourcename);
    }
    
    namespace clip {
        // \brief   Creates a clip named after a resource -- or an empty FramePlayer clip
        ClipPtr newClip(string clipname);
        // \brief   Creates a clip with the given resource
        ClipPtr newClip(string clipname, string resourcename);
        void    removeClip(string clipname);
        
        // \brief   Sets the order in which the clip will be drawn -- 0 is top; big numbers are at the bottom
        void    setClipDrawOrder(string clipname, int position);
        // \brief   Sets clip to the front of all other clips
        void    bringClipToFront(string clipname);
        // \brief   Raises clip in the drawing order
        void    bringClipForward(string clipname);
        // \brief   Lowers clip in the drawing order
        void    sendClipBackward(string clipname);
        // \brief   Sends clip below all other clips but above background (call setBackgroundClip if
        ///         you want it to stick at the bottom of everything
        void    sendClipToBack(string clipname);
        // \brief   Keeps clip as the background
        void    setBackgroundClip(string clipname);
        
        
        // \brief   Adds a frame to a (Frame)clip
        void    addFrame(ofImage & img);
        
        // \brief   Sets the given clip as the source for Cv
        void    setCvInput(string clipname);
        void    setCvDeviceId(const int n);
        
        //  \brief  Saves clip's images (frames) to a folder named after the clip
        //  \param  clipname    String      Name of the clip to be saved.  Will be used to
        //                                  find the directory or to create it (defaults to '+tmp'
        //                                  so it sticks to the top of the resources/frames directory
        void    saveImages(string clipname = "+tmp");
        
        // \brief   Prints all clip names to console
        void    listAll();
        // \brief   Prints clip rendering order
        void    listDrawOrder();
        // \brief   Deletes all clips
        void    clearAll();
        // \brief   Checks if a clip exists
        bool    exists(string clipname);
        ClipPtr getClip(string clipname);
        
        // ----- SHOW CLIP NAMES----
        
        /// \brief  Shows names of clips
        void toggleNames();
        void showNames();
        void hideNames();
        
        // ----- USE ONE CLIP -----
        /// \brief  Adds a movie to a clip
        void addMovieToClip(const string clipname, const string moviename);
        // play
        void playClip(const string clipname);
        // stop
        void stopClip(const string clipname);
        // pause
        void pauseClip(const string clipname);
        // set speed
        void setClipSpeed(const string clipname, const float speed);
        /// \brief Set loop state (none | normal | palindrome)
        void setClipLoopState(const string clipname, const LoopType state);
        /// \brief  Mask one clip with any player
        void setClipMask(const string clipname, const string maskclipname);
        void enableClipMask(const string clipname);
        void disableClipMask(const string clipname);
        
        // ----- EDIT CLIP CONTENTS -----
        /// \brief  Appends clipplayer's current image to cliprecorder frames
        void setRecordingSource(const string clipname, const string sourceclip);
        /// \brief  Appends clipplayer's current image to cliprecorder frames
        void addFrame(const string recorderclip, const string sourceclip);
        /// \brief  Inserts clipplayer's current image to cliprecorder's current frame
        void insertFrame(const string recorderclip, const string sourceclip);
        void removeFrame(const string clipname);
        void clearFrames(const string clipname);
        void saveFrames(const string clipname);
        void loadFrames(const string clipname, const string resourcename);
        
        // ----- CLIP ATTRIBUTES -----
        // reset all attributes
        void resetClip(const string clipname);
        // move to
        /// \brief Move clip
        /// \param  x,y   float     Normalized position.  Will be scaled according to window dimensions
        void moveClipTo(const string clipname, const float x, const float y);
        // set anchor point
        // scale -- resize
        void scaleClip(const string clipname, const float scale);
        /// \brief  Change width of Clip
        /// \param  clipname    String
        /// \param  scale       Float   Signed and normalized -- positive or negative float -- 1 is default
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
        /// \brief  Toggle clip visibility
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
    }
}

#endif