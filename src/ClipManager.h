//
//  ClipManager.h
//  clip
//
//  Created by roger on 21/06/2018.
//
//

#ifndef ClipManager_h
#define ClipManager_h

#include "ofMain.h"
#include "Types.h"
#include "Clip.h"

namespace loopier {
    class ClipManager {
        /// \brief   Creates a clip named after a resource -- or an empty FramePlayer clip
        ClipPtr newClip(string clipname);
        /// \brief   Creates a clip with the given resource
        ClipPtr newClip(string clipname, string resourcename);
        /// \brief   Creates a clip with the given resource at the position of the biggest CV blob
        ClipPtr newClipFromBlob(string clipname, string resourcename="");
        
        /// \brief  Creates a movie clip
        ClipPtr newMovieClip(string clipname, string resourcename);
        /// \brief  Creates a syphon clip
        ClipPtr newSyphonClip(string clipname, string resourcename);
        /// \brief  Creates a computer vision clip
        ClipPtr newCvClip(string clipname, string resourcename);
        /// \brief  Creates a camera clip
        ClipPtr newCameraClip(string clipname, string resourcename);
        /// \brief  Creates a frame clip
        ClipPtr newFrameClip(string clipname, string resourcename);
        /// \brief  Creates an empty frame clip
        ClipPtr newEmptyFrameClip(string clipname, string resourcename);
        
        void    removeClip(string clipname);
        
        /// \brief   Adds the clip to the selected clips vector
        void    selectClip(string clipname);
        /// \brief   Removes the clip From the selected clips vector
        void    deselectClip(string clipname);
        /// \brief  Selects the next available clip
        void    selectNextClip();
        void    toggleClipSelection(string clipname);
        /// \brief
        void    selectAllClips();
        void    deselectAllClips();
        /// \brief  Returns the list of names of the selected clips
        vector<string> getSelectedClipnames();
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
        void    addClipChild(const string parentclip, const string childclip);
        void    removeClipChild(const string parentclip, const string childclip);
        void    clearClipChildren(const string clip);
        vector<string>    getClipChildrenNames(const string clip);
        
        //  \brief  Saves clip's images (frames) to a folder named after the clip
        //  \param  clipname    String      Name of the clip to be saved.  Will be used to
        //                                  find the directory or to create it (defaults to '+tmp'
        //                                  so it sticks to the top of the resources/frames directory
        void    saveImages(string clipname = "+tmp");
        
        /// \brief   Prints all clip names to console
        void    listAll();
        /// \brief  Returns a list of the names of all clips
        vector<string> getNamesList();
        /// \brief   Prints clip rendering order
        void    listLayers();
        /// \brief   Deletes all clips
        void    clearAll();
        /// \brief   Checks if a clip exists
        bool    exists(string clipname);
        /// \brief  Returns the clip with the given name, or a new clip if it doesn't exist.
        ClipPtr getClip(string clipname);
        /// \brief  Gets the clip at the given position.
        /// \returns    Return the clip whose origin contains this point.
        ClipPtr getClipAt(const float x, const float y);
        /// \returns    Return the names of all clips that enclose this point
        vector<string> getClipsAt(const float x, const float y);
        
        // ----- SHOW CLIP NAMES----
        
        //// \brief  Shows names of clips
        void toggleName(const string clipname);
        void showName(const string clipname);
        void hideName(const string clipname);
        
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
        //// \brief Set play direction (normal | reverse)
        void setClipPlayDirection(const string clipname, const PlayDirection direction);
        void setClipChangePlayDirection(const string clipname);
        //// \brief  Mask one clip with any player
        void setClipMask(const string clipname, const string maskclipname);
        void enableClipMask(const string clipname);
        void disableClipMask(const string clipname);
        //// \brief  Mask one clip with CV holes
        void setClipHolesMask(const string clipname);
        
        // ----- EDIT CLIP CONTENTS -----        //// \brief  Appends sourceclip's current image -masked with cv blobs- to cliprecorder frames
        /// TODO: make some kind of abstraction with the masking part
        void addFrame(const string recorderclip, const string sourceclip);
        //// \brief  Inserts clipplayer's current image to cliprecorder's current frame
        void insertFrame(const string recorderclip, const string sourceclip);
        void removeFrame(const string clipname);
        void clearFrames(const string clipname);
        void saveFrames(const string clipname);
        void loadFrames(const string clipname, const string resourcename);
        /// \brief  Returns a rectangle representing the info stored in the resource's info file
        ofRectangle getResourceOriginalRectangle(const string resourcename);
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
        /// \brief  Loads a library of clips
        void loadClipLibrary(const string libraryname);
        void setClipLibraryPath(const string path);
        void listClipLibraryNames();
        /// \brief  Returns a list of all available clip libraries
        vector<string> getClipLibraryNames();
        
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
    };
}

#endif /* ClipManager_h */
