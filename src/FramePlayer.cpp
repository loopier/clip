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
: name("default")
, path("/Users/roger/Library/Application Support/Clip/resources/frames/")
, speed(1.0)
, frameRate(ofGetFrameRate())
, lastFrameTime(0.0)
, position(0.0)
, currentFrame(0)
, loopState(LOOP_NORMAL)
, playDirection(PLAY_DIRECTION_NORMAL)
, bLoaded(false)
, bPlay(true)
, anchor(100,100)
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
    
    if (playDirection == PLAY_DIRECTION_NORMAL)         nextFrame();
    else if (playDirection == PLAY_DIRECTION_REVERSE)   previousFrame();
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
void loopier::FramePlayer::setPath(string newPath)
{
    path = newPath;
}

//---------------------------------------------------------
bool loopier::FramePlayer::load(string newName)
{
    if (newName != "-") name = newName;
    else                name = "default";
    
    string absolutePath = path + name;
    
    ofLogVerbose() << "Preloading frame image files:";
    
    if (!ofDirectory(path).exists()) {
        string msg = "\tDirectory not found:\t" + name;
        ofLogError() << __PRETTY_FUNCTION__ << "\t" << msg;
        loopier::ConsoleUI::printError(msg);
        return;
    }
    
    // iterate subfolders
    ofDirectory dir(absolutePath);
    vector<ofFile> files = dir.getFiles();
    ofFile file;
    ofImage img;
    
    for ( int i = 0; i < files.size(); i++ ) {
        file = files[i];
        
        if (file.isDirectory()) continue;
        
        img.load(file.getAbsolutePath());
        addFrame(img);
        
//        ofLogVerbose() << "Base name: " << file.getBaseName() << "\t\t Path:" << file.getAbsolutePath();
    }
    
    ofLogVerbose() << "Finished loading frame image files";
    return true;
}

//---------------------------------------------------------
void loopier::FramePlayer::setName(string newName)
{
    name = newName;
}

//---------------------------------------------------------
string loopier::FramePlayer::getName() const
{
    return name;
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

bool loopier::FramePlayer::isPaused() const
{
       return !bPlay;
}

//---------------------------------------------------------
bool loopier::FramePlayer::isLoaded() const
{
       return bLoaded;
    
}

//---------------------------------------------------------
bool loopier::FramePlayer::isPlaying() const
{
       return bPlay;
    
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
void loopier::FramePlayer::setLoopState(loopier::LoopType state)
{
    loopState = state;
}

//---------------------------------------------------------
void loopier::FramePlayer::setPlayDirection(loopier::PlayDirection dir)
{
    playDirection = dir;
}

//---------------------------------------------------------
void loopier::FramePlayer::changePlayDirection()
{
    if (playDirection == PLAY_DIRECTION_NORMAL) setPlayDirection(PLAY_DIRECTION_REVERSE);
    else if (playDirection == PLAY_DIRECTION_REVERSE) setPlayDirection(PLAY_DIRECTION_NORMAL);
}

//---------------------------------------------------------
void loopier::FramePlayer::setSpeed(float newSpeed)
{
    speed = newSpeed;
    frameRate = 60 / (speed * ofGetFrameRate());
    ofLogVerbose() << frameRate << "\t" << speed;
}

//---------------------------------------------------------
void loopier::FramePlayer::setFrameRate(float fps)
{
    frameRate = fps;
    speed = (60 / frameRate) / ofGetFrameRate();
}

//---------------------------------------------------------
void loopier::FramePlayer::setFrame(int frame)
{
    currentFrame = frame;
}

//---------------------------------------------------------
int loopier::FramePlayer::getCurrentFrame() const
{
    return currentFrame;
}

//---------------------------------------------------------
int loopier::FramePlayer::getTotalNumFrames() const
{
    return frames.size();
}

//---------------------------------------------------------
loopier::LoopType loopier::FramePlayer::getLoopState() const
{
    return loopState;
}

//---------------------------------------------------------
loopier::PlayDirection loopier::FramePlayer::getPlayDirection() const
{
    return playDirection;
}

//---------------------------------------------------------
float loopier::FramePlayer::getFrameRate() const
{
    return frameRate;
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
        if (loopState == LOOP_NORMAL) {
            firstFrame();
        } else if (loopState == LOOP_PALINDROME) {
            currentFrame--;
            changePlayDirection();
        } else if (loopState == LOOP_NONE) {
            currentFrame--;
            stop();
        } else if (loopState == LOOP_ONCE) {
            stop();
        }
    }
}

//---------------------------------------------------------
void loopier::FramePlayer::previousFrame()
{
    currentFrame--;
    
    if (currentFrame < 0) {
        if (loopState == LOOP_NORMAL) {
            currentFrame = frames.size() - 1;
        } else if (loopState == LOOP_PALINDROME) {
            currentFrame++;
            changePlayDirection();
        } else if (loopState == LOOP_NONE) {
            currentFrame++;
            stop();
        } else if (loopState == LOOP_ONCE) {
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
