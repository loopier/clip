//
//  FramePlayer.cpp
//  clip
//
//  Created by roger on 23/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "FramePlayer.h"


//---------------------------------------------------------
bool loopier::FramePlayer::load(string name)
{
    return true;
}

//---------------------------------------------------------
void loopier::FramePlayer::setup()
{
    ofLogVerbose() << __FUNCTION__;
}

//---------------------------------------------------------
void loopier::FramePlayer::update()
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::draw()
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::exit()
{
       
}


void loopier::FramePlayer::play()
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::stop()
{
       
}

//---------------------------------------------------------
float loopier::FramePlayer::getWidth() const
{
       return 1.0;
}

//---------------------------------------------------------
float loopier::FramePlayer::getHeight() const
{
       return 1.0;
}

//---------------------------------------------------------

bool loopier::FramePlayer::isPaused() const
{
       return true;
}

//---------------------------------------------------------
bool loopier::FramePlayer::isLoaded() const
{
       return true;
    
}

//---------------------------------------------------------
bool loopier::FramePlayer::isPlaying() const
{
       return true;
    
}

//---------------------------------------------------------
float loopier::FramePlayer::getPosition() const
{
       return 1.0;
    
}

//---------------------------------------------------------
float loopier::FramePlayer::getSpeed() const
{
    return 1.0;
}

//---------------------------------------------------------
float loopier::FramePlayer::getDuration() const
{
    return 1.0;
}

//---------------------------------------------------------
bool loopier::FramePlayer::getIsMovieDone() const
{
    return true;
}

//---------------------------------------------------------

void loopier::FramePlayer::setPaused(bool bPause)
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::setPosition(float pct)
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::setLoopState(ofLoopType state)
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::setSpeed(float speed)
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::setFrame(int frame)
{
       
}

//---------------------------------------------------------
int loopier::FramePlayer::getCurrentFrame() const
{
    return 1;
}

//---------------------------------------------------------
int loopier::FramePlayer::getTotalNumFrames() const
{
    return 1;
}

//---------------------------------------------------------
loopier::LoopType loopier::FramePlayer::getLoopState() const
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::firstFrame()
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::nextFrame()
{
       
}

//---------------------------------------------------------
void loopier::FramePlayer::previousFrame()
{
       
}
