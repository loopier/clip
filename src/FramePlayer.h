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

namespace loopier {
    
    /// \brief Direction of the play head when playing
    enum PlayDirection {
        PLAY_DIRECTION_NORMAL   = 1,    ///< forward
        PLAY_DIRECTION_REVERSE  = -1    ///< backwards
    };
    
    enum LoopType {
        LOOP_NONE=0x01, // Freezes at last frame
        LOOP_PALINDROME=0x02,
        LOOP_NORMAL=0x03,
        LOOP_ONCE=0x04  // Plays once and then disappears
    };
    typedef vector<ofImage> FrameList;

class FramePlayer{
	
public:
    FramePlayer();
    virtual ~FramePlayer();
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void                setPath(string newPath);
    bool				load(string newName = "-");
    void                setName(string newName);
    string              getName() const;
//    void				loadAsync(string name);
    
    void				play();
    void				stop();
//    ofTexture *			getTexturePtr(){return nullptr;}; // if your videoplayer needs to implement seperate texture and pixel returns for performance, implement this function to return a texture instead of a pixel array. see iPhoneVideoGrabber for reference
    
    float 				getWidth() const;
    float 				getHeight() const;
    
    bool				isPaused() const;
    bool				isLoaded() const;
    bool				isPlaying() const;
//    bool				isInitialized() const{ return isLoaded(); }
    
    //should implement!
    float 				getPosition() const;
    float 				getSpeed() const;
    float 				getDuration() const;
    bool				getIsMovieDone() const;
    
    void 				setPaused(bool bPause);
    void 				setPosition(float pct);
//    void 				setVolume(float volume); // 0..1
    void 				setLoopState(LoopType state);
    void                setPlayDirection(PlayDirection dir);
    void                changePlayDirection();
    void   				setSpeed(float newSpeed);
    void                setFrameRate(float fps);
    void				setFrame(int frame);  // frame 0 = first frame...
    
    int					getCurrentFrame() const;
    int					getTotalNumFrames() const;
    LoopType			getLoopState() const;
    PlayDirection       getPlayDirection() const;
    float               getFrameRate() const;
    
    void				firstFrame();
    void				nextFrame();
    void				previousFrame();
    
    /// \brief  Inserts an image at the current frame
    void                addFrame(ofImage img);
private:
    string      name;
    string      path; // Path to folder
    FrameList   frames;
    float       speed; // Playing speed
    float       frameRate;
    float       lastFrameTime;
    float       position; // 0..1 (position in movie)
    int         currentFrame;
    LoopType    loopState;
    PlayDirection   playDirection;
    
    bool    bLoaded;
    bool    bPlay;
    
    ofPoint anchor; // Drawing 'center'
};

}
#endif