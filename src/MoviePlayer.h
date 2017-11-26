//
//  MoviePlayer.h
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _MoviePlayer
#define _MoviePlayer


#include "ofMain.h"
#include "BasePlayer.h"

namespace loopier {
    
    class MovieClipContent: public ofVideoPlayer, public ClipContent{};
    
    class MoviePlayer: public BasePlayer{
        
    public:
        MoviePlayer();
        virtual ~MoviePlayer();
        
        void setup();
        void update();
        void draw();
        void exit();
        
        // !!! TODO: Copy from global map instead of loading file
        bool				load(string filename);
        
        void				play();
        void				stop();
        
        float 				getWidth() const;
        float 				getHeight() const;
        
        float 				getDuration() const;
        
        void                setSpeed(float newSpeed);
        void                setFrameRate(int fps);
        
        int					getTotalNumFrames() const;
        
        void				firstFrame();
        void				nextFrame();
        void				previousFrame();
    private:
        MovieClipContent movie;
    };
}

#endif