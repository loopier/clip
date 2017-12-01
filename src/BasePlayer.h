//
//  BasePlayer.h
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//
//  Base class for all classes that can be played like a movie

#ifndef _BasePlayer
#define _BasePlayer


#include "ofMain.h"
#include "Types.h"

namespace loopier {
    
    class BasePlayer{
        
    public:
        
        virtual     void                setup();
        virtual     void                update() = 0;
        virtual     void                draw(float x, float y, float w, float h) = 0;
        virtual     void                exit();
        
        
//        virtual     void                setPath(string newPath);
        /// \brief  Copy from global map
        virtual     bool				loadResource(string resourcename) = 0;
        virtual     void                setName(string newName);
        virtual     string              getName() const;
        
        virtual     void				play();
        virtual     void				stop();
        
        virtual     float 				getWidth() const;
        virtual     float 				getHeight() const;
        virtual     ofTexture &          getTexture() const = 0;
        
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
        
        virtual     void                setAnchorPercent(float x, float y);
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
        
        ofPoint     anchor; // Drawing 'center'
    };
    
    typedef shared_ptr<BasePlayer>      PlayerPtr;
    typedef vector<PlayerPtr>           PlayerList;
    typedef map<string, PlayerPtr>      PlayerMap;
    
    extern  PlayerMap   players;
    
    void        addPlayer(PlayerPtr player);
    void        listPlayers();
    PlayerPtr   getPlayerByName(string name);
}

#endif