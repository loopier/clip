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
    
    typedef ofVideoPlayer           Movie;
    typedef shared_ptr<Movie>       MoviePtr;
    typedef map<string, MoviePtr>   MovieMap;
    
    class MoviePlayer: public BasePlayer{
        
    public:
        MoviePlayer();
        virtual ~MoviePlayer();
        
        void setup();
        void update();
        void draw();
        void exit();
        
        /// \brief  Copies frames from global map
        bool				load(string name);
        
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
        MoviePtr movie;
    };
}

#endif