//
//  MoviePlayer.cpp
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "MoviePlayer.h"


loopier::MovieMap       loopier::movies;

loopier::MoviePlayer::MoviePlayer()
: BasePlayer()
, movie(new Movie)
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
    if (!movie) return;
    movie->update();
}

//---------------------------------------------------------
void loopier::MoviePlayer::draw(){
    if (!movie) return;
    movie->draw(anchor.x, anchor.y);
}

//---------------------------------------------------------
void loopier::MoviePlayer::draw(float x, float y, float w, float h){
    if (!movie) return;
    movie->draw(x, y, w, h);
}

//---------------------------------------------------------
void loopier::MoviePlayer::exit(){
    
}

//---------------------------------------------------------
bool loopier::MoviePlayer::loadResource(string resourcename)
{
    string path = loopier::movies.find(resourcename)->second->getMoviePath();
    movie->load(path);
    play();
    BasePlayer::loadResource(resourcename);
    ofLogVerbose() << "Finished loading '" << resourcename << "' movie files to '" << name << "' player";
    bLoaded = movie->isLoaded();
    return bLoaded;
}

//---------------------------------------------------------
void loopier::MoviePlayer::play()
{
    movie->play();
}

//---------------------------------------------------------
void loopier::MoviePlayer::stop()
{
    movie->stop();
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
void loopier::MoviePlayer::setLoopState(loopier::LoopType state)
{
    BasePlayer::setLoopState(state);
    movie->setLoopState(ofLoopType(state));
    movie->play();
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