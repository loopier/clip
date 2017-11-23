//
//  FramePlayer.h
//  clip
//
//  Created by roger on 23/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _FramePlayer
#define _FramePlayer


#include "ofMain.h"

namespace loopier {
    
    typedef ofLoopType LoopType;
    typedef vector<ofImage> FrameList;

class FramePlayer{
	
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    //needs implementing
    bool				load(string name);
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
    void 				setLoopState(ofLoopType state);
    void   				setSpeed(float speed);
    void				setFrame(int frame);  // frame 0 = first frame...
    
    int					getCurrentFrame() const;
    int					getTotalNumFrames() const;
    ofLoopType			getLoopState() const;
    
    void				firstFrame();
    void				nextFrame();
    void				previousFrame();
    
private:
    string      path; //< Path to folder
    FrameList   frames;
    float       speed; //< Playing speed
};

}
#endif