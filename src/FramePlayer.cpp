//
//  FramePlayer.cpp
//  clip
//
//  Created by roger on 23/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "FramePlayer.h"
#include "ConsoleUI.h"

loopier::FramePlayer::FramePlayer()
: BasePlayer()
, lastFrameTime(0.0)
{
    
}

loopier::FramePlayer::~FramePlayer()
{
    
}

//---------------------------------------------------------
void loopier::FramePlayer::setup()
{
    ofLogVerbose() << __FUNCTION__;
}

//---------------------------------------------------------
void loopier::FramePlayer::update()
{
    if (!bPlay) return;
    
    float rateRatio = (60 / getFrameRate()) / ofGetFrameRate();
    
    if (lastFrameTime < rateRatio ) {
        lastFrameTime += ofGetLastFrameTime();
        return;
    }
    
    ofLogVerbose() << lastFrameTime << "\t" << frameRate << " / " << ofGetFrameRate() << "\t" << rateRatio;
    
    lastFrameTime = 0;
    
    if (playDirection == loopier::PlayDirection::normal)         nextFrame();
    else if (playDirection == loopier::PlayDirection::reverse)   previousFrame();
}

//---------------------------------------------------------
void loopier::FramePlayer::draw()
{
    if (frames.size() <= 0) return;
    
    frames[currentFrame].draw(anchor.x, anchor.y);
}

//---------------------------------------------------------
void loopier::FramePlayer::exit()
{
       
}

//---------------------------------------------------------
bool loopier::FramePlayer::load(string name)
{
    // !!! TODO: Copy from global vector fo contents
//    name = filename;
    
    
    
    ofLogVerbose() << __PRETTY_FUNCTION__ << "Needs imlpementation";
    ofLogVerbose() << "Finished loading frame image files";
    return bLoaded;
}

//---------------------------------------------------------
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
float loopier::FramePlayer::getDuration() const
{
    return 1.0;
}


//---------------------------------------------------------
void loopier::FramePlayer::setSpeed(float newSpeed)
{
    speed = newSpeed;
    frameRate = 60 / (speed * ofGetFrameRate());
    ofLogVerbose() << frameRate << "\t" << speed;
}

//---------------------------------------------------------
void loopier::FramePlayer::setFrameRate(int fps)
{
    frameRate = fps;
    speed = (60 / frameRate) / ofGetFrameRate();
}


//---------------------------------------------------------
int loopier::FramePlayer::getTotalNumFrames() const
{
    return frames.size();
}


//---------------------------------------------------------
void loopier::FramePlayer::firstFrame()
{
    currentFrame = 0;
}

//---------------------------------------------------------
void loopier::FramePlayer::nextFrame()
{
    currentFrame++;
    
    if (currentFrame > frames.size() - 1) {
        if (loopState == loopier::LoopType::normal) {
            firstFrame();
        } else if (loopState == loopier::LoopType::palindrome) {
            currentFrame--;
            changePlayDirection();
        } else if (loopState == loopier::LoopType::none) {
            currentFrame--;
            stop();
        } else if (loopState == loopier::LoopType::once) {
            stop();
        }
    }
}

//---------------------------------------------------------
void loopier::FramePlayer::previousFrame()
{
    currentFrame--;
    
    if (currentFrame < 0) {
        if (loopState == loopier::LoopType::normal) {
            currentFrame = frames.size() - 1;
        } else if (loopState == loopier::LoopType::palindrome) {
            currentFrame++;
            changePlayDirection();
        } else if (loopState == loopier::LoopType::none) {
            currentFrame++;
            stop();
        } else if (loopState == loopier::LoopType::once) {
            stop();
        }
    }
}

//---------------------------------------------------------
void loopier::FramePlayer::addFrame(ofImage img)
{
    vector<ofImage>::iterator pos = frames.begin() + currentFrame;
    frames.insert(pos, img);
    ofLogVerbose() << "Inserted new frame in '" << getName() << "' at: " << currentFrame;
    nextFrame();
}
