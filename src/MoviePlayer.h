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
    
    extern MovieMap     moviemap;     // list of all available movie files
    
    class MoviePlayer: public BasePlayer{
        
    public:
        MoviePlayer();
        MoviePlayer(MoviePtr mov);
        virtual ~MoviePlayer();
        
        void    setup();
        void    update();
        void    draw();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        /// \brief  Copies frames from global map
//        bool    loadResource(string resourcename);
        /// \brief  Loads movie to be played
        void    load(string path);
        
        void    play();
        void    stop();
        
        float       getWidth() const;
        float       getHeight() const;
        ofTexture & getTexture();
        ofPixels &  getPixels();
        ofImage &   getImage();
        
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
        ofImage  image; // current frame
    };
    
    typedef shared_ptr<MoviePlayer> MoviePlayerPtr;
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    // *                                                                       *
    // *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
    // *                                                                       *
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    
    bool    loadMoviesDeprecated(string path);
    void    listMovieNames();
    
}

#endif