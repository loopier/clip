//
//  MoviePlayer.cpp
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "MoviePlayer.h"

loopier::MoviePlayer::MoviePlayer()
: BasePlayer()
{
    
}

loopier::MoviePlayer::~MoviePlayer()
{
    
}

//---------------------------------------------------------
void loopier::MoviePlayer::setup(){
    
}

//---------------------------------------------------------
void loopier::MoviePlayer::update(){
    
}

//---------------------------------------------------------
void loopier::MoviePlayer::draw(){
    movie.draw();
}

//---------------------------------------------------------
void loopier::MoviePlayer::exit(){
    
}

//---------------------------------------------------------
bool loopier::MoviePlayer::load(string filename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
void loopier::MoviePlayer::play()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
void loopier::MoviePlayer::stop()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
float loopier::MoviePlayer::getWidth() const
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    return 1.0;
}

//---------------------------------------------------------
float loopier::MoviePlayer::getHeight() const
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    return 1.0;
}

//---------------------------------------------------------
float loopier::MoviePlayer::getDuration() const
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    return 1.0;
}


//---------------------------------------------------------
void loopier::MoviePlayer::setSpeed(float newSpeed)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    speed = newSpeed;
    frameRate = 60 / (speed * ofGetFrameRate());
    ofLogVerbose() << frameRate << "\t" << speed;
}

//---------------------------------------------------------
void loopier::MoviePlayer::setFrameRate(int fps)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    frameRate = fps;
    speed = (60 / frameRate) / ofGetFrameRate();
}


//---------------------------------------------------------
int loopier::MoviePlayer::getTotalNumFrames() const
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    return 1;
}


//---------------------------------------------------------
void loopier::MoviePlayer::firstFrame()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
void loopier::MoviePlayer::nextFrame()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
void loopier::MoviePlayer::previousFrame()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}