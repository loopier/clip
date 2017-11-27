//
//  FramePlayer.h
//  clip
//
//  Created by roger on 23/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//
//  This class plays sequences of images like a movie (like ofVideoPlayer)

#ifndef _FramePlayer
#define _FramePlayer


#include "ofMain.h"
#include "BasePlayer.h"

namespace loopier {
    
    typedef vector<ofImage>             FrameList;
    typedef shared_ptr<FrameList>       FrameListPtr;
    typedef map<string, FrameListPtr>   FrameListMap;
    
    extern FrameListMap frameLists; // list of all available frame image files
    
    class FramePlayer: public BasePlayer{
        
    public:
        FramePlayer();
        virtual ~FramePlayer();
        
        void    setup();
        void    update();
        void    draw();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        /// \brief  Copies frames from global map
        bool    loadResource(string resourcename);
        
        void    play();
        void    stop();
        
        float   getWidth() const;
        float   getHeight() const;
        
        float     getDuration() const;
        
        void    setSpeed(float newSpeed);
        void    setFrameRate(int fps);
        
        int    	getTotalNumFrames() const;
        
        void    firstFrame();
        void    nextFrame();
        void    previousFrame();
        
        /// \brief  Inserts an image at the current frame
        void    addFrame(ofImage img);
    private:
        FrameListPtr   frames;
        float       lastFrameTime;
    };
    
}
#endif