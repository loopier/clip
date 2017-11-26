//
//  BasePlayer.h
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//
//  Base class for all classes that can be played

#ifndef _BasePlayer
#define _BasePlayer


#include "ofMain.h"

namespace loopier {
    
    /// \brief Direction of the play head when playing
    enum class PlayDirection {
        normal   = 1,    ///< forward
        reverse  = -1    ///< backwards
    };
    
//    typedef ofLoopType LoopType;
    enum class LoopType {
        none        = OF_LOOP_NONE, // Freezes at last frame
        palindrome  = OF_LOOP_PALINDROME,
        normal      = OF_LOOP_NORMAL,
        once        = 0x03  // Plays once and then disappears
    };
    
    class BasePlayer{
        
    public:
        
        virtual     void                setup();
        virtual     void                update() = 0;
        virtual     void                draw() = 0;
        virtual     void                exit();
        
        
        virtual     void                setPath(string newPath);
        virtual     bool				load(string newName = "-");
        virtual     void                setName(string newName);
        virtual     string              getName() const;
        
        virtual     void				play();
        virtual     void				stop();
        
        virtual     float 				getWidth() const;
        virtual     float 				getHeight() const;
        
        virtual     bool				isPaused() const;
        virtual     bool				isLoaded() const;
        virtual     bool				isPlaying() const;
        //    bool				isInitialized() const{ return isLoaded(); }
        
        //should implement!
        virtual     float 				getPosition() const;
        virtual     float 				getSpeed() const;
        virtual     float 				getDuration() const;
        virtual     bool				getIsMovieDone() const;
        
        virtual     void 				setPaused(bool bPause);
        virtual     void 				setPosition(float pct);
        virtual     void 				setLoopState(LoopType state);
        virtual     void                setPlayDirection(PlayDirection dir);
        virtual     void                changePlayDirection();
        virtual     void   				setSpeed(float newSpeed);
        virtual     void                setFrameRate(int fps);
        virtual     void				setFrame(int frame);  // frame 0 = first frame...
        
        virtual     int					getCurrentFrame() const;
        virtual     int					getTotalNumFrames() const;
        virtual     LoopType			getLoopState() const;
        virtual     PlayDirection       getPlayDirection() const;
        virtual     int                 getFrameRate() const;
        
        virtual     void				firstFrame();
        virtual     void				nextFrame();
        virtual     void				previousFrame();
    protected:
        BasePlayer();
        
        string      name;
        string      path; // Path to folder
        float       speed; // Playing speed
        float       frameRate;
        float       position; // 0..1 (position in movie)
        int         currentFrame;
        LoopType    loopState;
        PlayDirection   playDirection;
        
        bool    bLoaded;
        bool    bPlay;
        bool    bMovieDone;
        
        ofPoint anchor; // Drawing 'center'
    };
    
    typedef shared_ptr<BasePlayer> BasePlayerPtr;
}

#endif