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
    
    extern MovieMap     movies;     // list of all available movie files
    
    class MoviePlayer: public BasePlayer{
        
    public:
        MoviePlayer();
        virtual ~MoviePlayer();
        
        void    setup();
        void    update();
        void    draw();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        /// \brief  Copies frames from global map
        bool    loadResource(string resourcename);
        
        void    play();
        void    stop();
        
        float       getWidth() const;
        float       getHeight() const;
        ofTexture & getTexture() const;
        ofPixels &  getPixels() const;
        
        float   getDuration() const;
        
        void    setLoopState(LoopType state);
        void    setSpeed(float newSpeed);
        void    setFrameRate(int fps);
        
        int     getTotalNumFrames() const;
        
        void    firstFrame();
        void    nextFrame();
        void    previousFrame();
    private:
        MoviePtr movie;
    };
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    // *                                                                       *
    // *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
    // *                                                                       *
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    
    bool    loadMovies(string path);
    void    listMovieNames();
    
}

#endif