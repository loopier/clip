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
        virtual ~BasePlayer();
        
        virtual     void                setup();
        virtual     void                update() = 0;
        virtual     void                draw() = 0;
        virtual     void                exit();
        
        
//        virtual     void                setPath(string newPath);
        /// \brief  Copy from global map
//        virtual     bool				loadResource(string resourcename) = 0;
        virtual     void                setName(string newName);
        virtual     string              getName() const;
        
        virtual     void				play();
        virtual     void				stop();
        virtual     void                pause();
        
        virtual     void                setWidth(float w);
        virtual     void                setHeight(float h);
        virtual     float 				getWidth() const;
        virtual     float 				getHeight() const;
        virtual     ofTexture &         getTexture() = 0;
        virtual     ofPixels &          getPixels() = 0;
        virtual     ofImage &           getImage() = 0;
        
        virtual     void                setInputPlayer(shared_ptr<BasePlayer> aPlayer);
        
        virtual     bool				isPaused() const;
        virtual     bool				isLoaded() const;
        virtual     bool				isPlaying() const;
        //    bool				isInitialized() const{ return isLoaded(); }
        
        //should implement!
        virtual     ofPoint &           getPosition();
        virtual     void 				setPosition(ofPoint & pos);
        
        virtual     float 				getSpeed() const;
        virtual     float 				getDuration() const;
        virtual     bool				getIsMovieDone() const;
        
        virtual     void 				setPaused(bool bPause);
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
        virtual     float               getFrameRate() const;
        
        virtual     void				firstFrame();
        virtual     void				nextFrame();
        virtual     void				previousFrame();
        
        virtual     void                setResourceDimensions(const float w, const float h);
        virtual     void                setResourceWidth(const float w);
        virtual     void                setResourceHeight(const float h);
        virtual     float               getResourceWidth();
        virtual     float               getResourceHeight();
        
        virtual     void                setAnchorPercent(const float x, const float y);
        virtual     void                setAnchorPercent(const ofPoint & point);
        virtual     ofPoint             getAnchorPercent();
    protected:
        BasePlayer();
        
        ofPoint position;
        float   width, height;
        float   resourceWidth; ///< Reference width for resizing when replacing blobs
        float   resourceHeight; ///< Reference width for resizing when replacing blobs
        ofPoint anchor; ///< Drawing 'center' (normalized)
        
        shared_ptr<BasePlayer>  inputPlayer;
        
        string      name;
        string      path; // Path to folder
        float       speed; // Playing speed
        float       frameRate;
        int         currentFrame;
        LoopType    loopState;
        PlayDirection   playDirection;
        
        bool    bLoaded;
        bool    bPlay;
        bool    bMovieDone;
        
    };
    
    typedef shared_ptr<BasePlayer>      PlayerPtr;
    typedef vector<PlayerPtr>           PlayerList;
    typedef map<string, PlayerPtr>      PlayerMap;
    
    extern  PlayerMap   playermap;
    
    void        addPlayer(PlayerPtr player);
    void        listPlayers();
    PlayerPtr   getPlayerByName(string name);
}

#endif