//
//  Clip.h
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _Clip
#define _Clip


#include "ofMain.h"
#include "Types.h"
#include "FramePlayer.h"
#include "MoviePlayer.h"
#include "CameraPlayer.h"
#include "CvPlayer.h"

namespace loopier {
    
    class Clip{
        
    public:
        
        //        Clip(); -- DISABLED (Private)
        Clip (string & clipname, string & resourcename);
        virtual ~Clip();
        
        void setup();
        void update();
        void draw();
        void exit();
        
        /// \brief  Resets clip to the default state
        void reset();
        
        /// \brief  Loads movies or images into the Player
        void setResource(string & resourcename);
        
        void setName(const string& newName);
        string getName() const;
        
        void play();
        void stop();
        void pause(bool bPause=true);
        void setLoopState(const LoopType state);
        void setSpeed(const float newSpeed);
        
        void setScale(const float newScale);
        void setScaleX(const float newScale);
        void setScaleY(const float newScale);
        float getScale() const;
        
        void setPosition(const float newX, const float newY);
        void setPosition(const ofPoint& newPos);
        ofPoint getPosition() const;
        
        void toggleFullscreen();
        void toggleVisibility();
        void show();
        void hide();
        
        void setColor(const ofColor& newColor);
        void setAlpha(const float newAlpha);
        
        void toggleName();
        void showName();
        void hideName();
        
        //------------------------------------------------------------------------------------------
        //  Transforms
        void flipV();
        void flipH();
        
    private:
        PlayerPtr   player;
        
        string  name;
        float   x, y;
        float   width, height;
        float   scale, scaleX, scaleY;
        float   anchorPercentX, anchorPercentY;
        ofColor color; ///< Tint
        float   alpha; ///< Transparency of the clip
        
        bool    bFullscreen;
        bool    bDrawName;
        bool    bVisible;
        
        // transforms
        bool    bFlipV; ///< Flip vertically
        bool    bFlipH; ///< Flip horizontally
        
        LoopType    loopState;    ///< See ofSetLoopState(...)
        bool        bPlaySequence; ///< If true, all movies are played in sequence order.
        int         sequenceIndex; ///< Used to keep track of the sequence order.
        vector<int> sequenceOrder; ///< Each element is a movie index.  They'll be played in order.
        
        Clip(); // Disable default constructor.  All clips must have a name
        
        /// \brief
        
    };
    
    typedef shared_ptr<Clip>        ClipPtr;
    typedef vector<ClipPtr>         ClipList;
    typedef map<string, ClipPtr>    ClipMap;
    
    extern ClipMap      clips;      // global the list of clips available everywhere
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    // *                                                                       *
    // *    NON-MEMBER PUBLIC INTERFACE FUNCTIONS                              *
    // *                                                                       *
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    
    // ----- RESOURCE FILES-----
    
    /// \brief  Load all files into memory
    bool    initResources(string path="");
    int     loadResourceFiles(string path="");
    
    /// \brief  Prints the list of available movies and frame collections
    void    listResourceNames();
    
    
    // ----- MANAGE CLIPS-----
    
    /// \brief  Creates a new clip with the given movie file
    /// \param  name    String  Name of the movie file (with or without extension).
    ///                         The application will look in the path for a directory named after 'name'.
    /// \param  path    String  Path to the parent directory of the subdirectory holding the movie file.
    ///                         E.g. If the movie file is named 'mymovie.mov', it should be
    ///                         located in a subfolder named 'mymovie'.  The 'path' variable
    ///                         should be the path to the directory where the subdirectory
    ///                         'mymovie' resides.
    loopier::ClipPtr newClip(string clipname);
    loopier::ClipPtr newClip(string clipname, string filename);
    void removeClip(const string& clipname);
    /// \brief  Clear content
    void clearClips();
    
    // ----- UDPATE AND DRAW ALL CLIPS-----
    
    void updateClips();
    void drawClips();
    
    // ----- CLIP LIST UTILS-----
    
    /// \brief  Prints the list of clip names to console
    void listClipNames();
    /// \brief  Prints the list of clips and their contents
    void listClips();
    /// \brief  Checks if a clip with that name exists.  If it doesn't logs a warning.
    /// \param  clipname    String
    /// \returns    True if there's a clip that matches the name
    bool clipExists(const string clipname);
    
    // ----- SHOW CLIP NAMES----
    
    /// \brief  Shows names of clips
    void toggleClipNames();
    void showClipNames();
    void hideClipNames();
    
    // ----- MANAGE SINGLE CLIPS -----
    
    // ----- USE ONE CLIP -----
    /// \brief  Adds a movie to a clip
    void addMovieToClip(const string clipname, const string moviename);
    // play
    void playClip(const string clipname);
    // stop
    void stopClip(const string clipname);
    // pause
    void pauseClip(const string clipname);
    // change movie source
    // set speed
    void setClipSpeed(const string clipname, const float speed);
    /// \brief Set loop state (none | normal | palindrome)
    void setClipLoopState(const string clipname, const LoopType state);
    
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
    void setClipColor(const string clipname, const string & color);
    void setClipColor(const string clipname, const ofColor & color);
    // transparency
    void setClipAlpha(const string clipname, const float alpha);
    // reset attributes -- factory defaults
    
    
    
}

#endif