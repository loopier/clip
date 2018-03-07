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
        FramePlayer(FrameListPtr framelist);
        virtual ~FramePlayer();
        
        void    setup();
        void    update();
        void    draw();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        void    play();
        void    stop();
        
        float       getWidth() const;
        float       getHeight() const;
        ofTexture & getTexture();;
        ofPixels &  getPixels();
        ofImage &   getImage();
        
        FrameListPtr    getFrames();
        
        float     getDuration() const;
        
        void    setSpeed(float newSpeed);
        void    setFrameRate(int fps);
        
        int    	getTotalNumFrames() const;
        
        void    firstFrame();
        void    nextFrame();
        void    previousFrame();
        
        /// \brief  Sets the player from where to extract images
        void    setRecordingSourcePlayer(PlayerPtr player);
        /// \brief  Adds an image at the end
        void    addFrame(ofImage & img);
        /// \brief  Inserts an image at the current frame
        void    insertFrame(ofImage & img);
        void    removeFrame();
        void    clear();
    private:
        FrameListPtr    frames;
        float           lastFrameTime;
        PlayerPtr       recordingSourcePlayer; // frames are captured from this
    };
    
    typedef shared_ptr<FramePlayer> FramePlayerPtr;
    
}
#endif