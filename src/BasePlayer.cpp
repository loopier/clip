//
//  BasePlayer.cpp
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "BasePlayer.h"

loopier::PlayerMap  loopier::playermap;

loopier::BasePlayer::BasePlayer()
: name("default")
, path("/Users/roger/Library/Application Support/Clip/resources/players/")
, speed(1.0)
//, frameRate(ofGetFrameRate())
, position(0.0)
, currentFrame(0)
, loopState(loopier::LoopType::normal)
, playDirection(loopier::PlayDirection::normal)
, bLoaded(false)
, bPlay(true)
, anchor(0.0,0.0)
{
    
}

loopier::BasePlayer::~BasePlayer()
{
    
}

//---------------------------------------------------------
void    loopier::BasePlayer::setup()
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
}

////---------------------------------------------------------
//void    loopier::BasePlayer::update()
//{
//    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
//}
//
////---------------------------------------------------------
//void    loopier::BasePlayer::draw()
//{
//    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
//}

//---------------------------------------------------------
void    loopier::BasePlayer::exit()
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
}

//---------------------------------------------------------
//void    loopier::BasePlayer::setPath(string newPath)
//{
//    path = newPath;
//}



//---------------------------------------------------------
void    loopier::BasePlayer::setName(string newName)
{
    name = newName;
}

//---------------------------------------------------------
string  loopier::BasePlayer::getName() const
{
    return name;
}

//---------------------------------------------------------
void    loopier::BasePlayer::play()
{
    ofLogNotice() << "Started playing '" << name << "'";
    bPlay = true;
}

//---------------------------------------------------------
void    loopier::BasePlayer::stop()
{
    ofLogNotice() << "Stop playing '" << name << "'";
    bPlay = false;
}

//---------------------------------------------------------
void    loopier::BasePlayer::pause()
{
    ofLogNotice() << "Pause '" << name << "'";
    bPlay = false;
}

//---------------------------------------------------------
void   loopier::BasePlayer::setWidth(float w)
{
    width = w;
}

//---------------------------------------------------------
void   loopier::BasePlayer::setHeight(float h)
{
    height = h;
}

//---------------------------------------------------------
float   loopier::BasePlayer::getWidth() const
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
    return 1.0;
}

//---------------------------------------------------------
float   loopier::BasePlayer::getHeight() const
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
    return 1.0;
}

//---------------------------------------------------------
bool    loopier::BasePlayer::isPaused() const
{
    return !bPlay;
}

//---------------------------------------------------------
bool    loopier::BasePlayer::isLoaded() const
{
    return bLoaded;
}

//---------------------------------------------------------
bool loopier::BasePlayer::isPlaying() const
{
    return bPlay;
}

//---------------------------------------------------------
float   loopier::BasePlayer::getPosition() const
{
    return position;
}

//---------------------------------------------------------
float loopier::BasePlayer::getSpeed() const
{
    return speed;
}

//---------------------------------------------------------
float loopier::BasePlayer::getDuration() const
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
    return 1.0;
}

//---------------------------------------------------------
bool    loopier::BasePlayer::getIsMovieDone() const
{
    return bMovieDone;
}

//---------------------------------------------------------
void    loopier::BasePlayer::setPaused(bool bPause)
{
    bPlay = !bPause;
}

//---------------------------------------------------------
void    loopier::BasePlayer::setPosition(float pct)
{
    position = pct;
}

//---------------------------------------------------------
void    loopier::BasePlayer::setLoopState(LoopType state)
{
    loopState = state;
}

//---------------------------------------------------------
void    loopier::BasePlayer::setPlayDirection(PlayDirection dir)
{
    playDirection = dir;
}

//---------------------------------------------------------
void    loopier::BasePlayer::changePlayDirection()
{
    playDirection == loopier::PlayDirection::normal? loopier::PlayDirection::reverse : loopier::PlayDirection::normal;
}

//---------------------------------------------------------
void    loopier::BasePlayer::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

//---------------------------------------------------------
void    loopier::BasePlayer::setFrameRate(int fps)
{
    frameRate = fps;
}

//---------------------------------------------------------
void    loopier::BasePlayer::setFrame(int frame)
{
    currentFrame = frame;
}

//---------------------------------------------------------
int    loopier::BasePlayer::getCurrentFrame() const
{
    return currentFrame;
}

//---------------------------------------------------------
int    loopier::BasePlayer::getTotalNumFrames() const
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
    return 1;
}

//---------------------------------------------------------
loopier::LoopType   loopier::BasePlayer::getLoopState() const
{
    return loopState;
}

//---------------------------------------------------------
loopier::PlayDirection  loopier::BasePlayer::getPlayDirection() const
{
    return playDirection;
}

//---------------------------------------------------------
int     loopier::BasePlayer::getFrameRate() const
{
    return frameRate;
}

//---------------------------------------------------------
void    loopier::BasePlayer::firstFrame()
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
}

//---------------------------------------------------------
void    loopier::BasePlayer::nextFrame()
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
}

//---------------------------------------------------------
void    loopier::BasePlayer::previousFrame()
{
    ofLogNotice() << __PRETTY_FUNCTION__ << " is not implemented";
}

//---------------------------------------------------------
void    loopier::BasePlayer::setAnchorPercent(float x, float y)
{
    anchor.x = x;
    anchor.y = y;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------
void loopier::addPlayer(PlayerPtr player)
{
    playermap[player->getName()] = player;
    ofLogVerbose() << "Adding player: " << player->getName();
    ofLogNotice() << "Number of players:\t" + ofToString(loopier::playermap.size());
}

//---------------------------------------------------------
void loopier::listPlayers()
{
    string msg = "Number of players:\t" + ofToString(loopier::playermap.size());
    loopier::PlayerMap::iterator it;
    for (it = loopier::playermap.begin(); it != loopier::playermap.end(); ++it) {
        msg += "\n\t" + it->first;
    }
    
    ofLogNotice() << msg;
}

//---------------------------------------------------------
loopier::PlayerPtr  loopier::getPlayerByName(string name)
{
    return loopier::playermap.find(name)->second;
}

