//
//  MoviePlayer.cpp
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "MoviePlayer.h"


loopier::MovieMap       loopier::moviemap;

loopier::MoviePlayer::MoviePlayer()
: BasePlayer()
, movie(new Movie)
{
    
}

loopier::MoviePlayer::MoviePlayer(loopier::MoviePtr mov)
: BasePlayer()
, movie(new Movie)
{
    movie->load(mov->getMoviePath());
}

loopier::MoviePlayer::~MoviePlayer()
{
    
}

//---------------------------------------------------------
void loopier::MoviePlayer::setup(){
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
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
    string path = loopier::moviemap.find(resourcename)->second->getMoviePath();
    movie->load(path);
    play();
    BasePlayer::loadResource(resourcename);
    ofLogVerbose() << "Finished loading '" << resourcename << "' movie files to '" << name << "' player";
    bLoaded = movie->isLoaded();
    return bLoaded;
}

//---------------------------------------------------------
void loopier::MoviePlayer::load(string path)
{
    movie->load(path);
    bLoaded = movie->isLoaded();
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
    return movie->getWidth();
}

//---------------------------------------------------------
float loopier::MoviePlayer::getHeight() const
{
    return movie->getHeight();
}

//---------------------------------------------------------
ofTexture & loopier::MoviePlayer::getTexture()
{
    return movie->getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::MoviePlayer::getPixels()
{
    return movie->getPixels();
}

//---------------------------------------------------------
float loopier::MoviePlayer::getDuration() const
{
    return movie->getDuration();
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
    movie->setSpeed(newSpeed);
    speed = newSpeed;
}

//---------------------------------------------------------
void loopier::MoviePlayer::setFrameRate(int fps)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    frameRate = fps;
//    speed = (60 / frameRate) / ofGetFrameRate();
}


//---------------------------------------------------------
int loopier::MoviePlayer::getTotalNumFrames() const
{
    return movie->getTotalNumFrames();
}


//---------------------------------------------------------
void loopier::MoviePlayer::firstFrame()
{
    movie->firstFrame();
}

//---------------------------------------------------------
void loopier::MoviePlayer::nextFrame()
{
    movie->nextFrame();
}

//---------------------------------------------------------
void loopier::MoviePlayer::previousFrame()
{
    movie->previousFrame();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------
bool loopier::loadMoviesDeprecated(string path)
{
//    ofLogVerbose() << "Loading movie files from: " << path;
//    
//    ofDirectory dir(path+"movies");
//    dir.allowExt("mov");
//    vector<ofFile> files = dir.getFiles();
//    
//    for (int i = 0; i < files.size(); i++) {
//        MoviePtr movie(new Movie);
//        movie->load(files[i].getAbsolutePath());
//        loopier::movies[files[i].getBaseName()] = movie;
//    }
//    
//    ofLogVerbose() << "Loaded " << loopier::movies.size() << " movie files";
//    
//    return true;
}

//---------------------------------------------------------
void loopier::listMovieNames()
{
//    string msg = "Number of movies:\t" + ofToString(loopier::movies.size());
//    loopier::MovieMap::iterator it;
//    for (it = loopier::movies.begin(); it != loopier::movies.end(); ++it) {
//        msg += "\n\t" + it->first;
//    }
//    
//    ofLogNotice() << msg;
}