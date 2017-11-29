//
//  Clip.cpp
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "Clip.h"
#include "ConsoleUI.h"
#include "utils.h"

//---------------------------------------------------------
loopier::Clip::Clip(){
    
}

//---------------------------------------------------------------------------
loopier::Clip::Clip(string& clipname, string& resourcename)
: name(clipname)
, x(0)
, y(0)
, width(640)
, height(400)
, scale(1.0)
, scaleX(1.0)
, scaleY(1.0)
, anchorPercentX(0.5)
, anchorPercentY(0.5)
, color(ofColor(255))
, alpha(1.0)
, bFullscreen(false)
, bVisible(true)
, bDrawName(false)
, loopState(LoopType::normal)
{
    setResource(resourcename);
}

//---------------------------------------------------------
loopier::Clip::~Clip(){
    
}

//---------------------------------------------------------------------------
void loopier::Clip::setup()
{
    sequenceOrder.push_back(0);
    player->setLoopState(loopState);
    
//    reset();
}

//---------------------------------------------------------------------------
void loopier::Clip::update()
{
//    if (bPlaySequence) updateSequence();
    player->update();
}

//---------------------------------------------------------------------------
void loopier::Clip::draw()
{
    if (!bVisible) return;
    
    ofSetColor(color);
    
    if (bFullscreen) {
        int fx = ofGetWidth() / 2;
        int fy = ofGetHeight() / 2;
        int fw = ofGetWidth() * ofSign(scaleX);
        int fh = ofGetHeight() * ofSign(scaleY);
        player->draw(fx, fy, fw, fh);
    } else {
        player->draw(x, y, width, height);
        if (bDrawName)  ofDrawBitmapString(name, x, y);
    }
}

//---------------------------------------------------------------------------
void loopier::Clip::reset()
{
    width = player->getWidth();
    height = player->getHeight();
    anchorPercentX = 0.5;
    anchorPercentY = 0.5;
    player->setAnchorPercent(anchorPercentX, anchorPercentY);
    x = ofGetWidth() / 2;
    y = ofGetHeight() / 2;
    scale = 1.0;
    scaleX = scale;
    scaleY = scale;
    color = ofColor(255);
    alpha = 1.0;
}


//---------------------------------------------------------------------------
void loopier::Clip::setResource(string & resourcename)
{
    if (loopier::movies.count(resourcename)) {
        player = make_shared<MoviePlayer>();
        ofLogVerbose() << "'" << name << "'" << " will play the movie: " << resourcename << "'";
    } else if (loopier::frameLists.count(resourcename)) {
        player = make_shared<FramePlayer>();
        ofLogVerbose() << "'" << name << "'" << " will play the frames: " << resourcename << "'";
    }
    
    player->loadResource(resourcename);
    width = player->getWidth();
    height = player->getHeight();
}

//---------------------------------------------------------------------------
void loopier::Clip::setName(const string &newName)
{
    ofLogVerbose() << name << " changing name to: " << scale;
    name = newName;
}

//---------------------------------------------------------------------------
string loopier::Clip::getName() const
{
    return name;
}

//---------------------------------------------------------------------------
void loopier::Clip::play()
{
    player->play();
//    movie->isPlaying()? movie->setPaused(true) : movie->play();
//    
//    ofLogVerbose() << (movie->isPlaying()? "play: " : "pause: ") << name ;
}

//---------------------------------------------------------------------------
void loopier::Clip::stop()
{
    player->stop();
}

//---------------------------------------------------------------------------
void loopier::Clip::pause(bool bPause)
{
    player->setPaused(bPause);
    
    ofLogVerbose() << "pause: " << name ;
}

//---------------------------------------------------------------------------
void loopier::Clip::setLoopState(const loopier::LoopType state)
{
    loopState = state;
    player->setLoopState(loopState);
    if (player->isPaused()) player->play();
}

//---------------------------------------------------------------------------
void loopier::Clip::setSpeed(const float newSpeed)
{
    player->setSpeed(newSpeed);
}

//---------------------------------------------------------------------------
void loopier::Clip::setScale(const float newScale)
{
    
    scale = newScale;
    
    setScaleX(newScale);
    setScaleY(newScale);
    
    width = player->getWidth() * scaleX;
    height = player->getHeight() * scaleY;
    
    ofLogVerbose() << name << " scale: " << scale;
}

//---------------------------------------------------------------------------
void loopier::Clip::setScaleX(const float newScale)
{
    scaleX = newScale * ofSign(scaleX);
    width = player->getWidth() * scaleX;
}

//---------------------------------------------------------------------------
void loopier::Clip::setScaleY(const float newScale)
{
    scaleY = newScale * ofSign(scaleY);
    height = player->getHeight() * scaleY;
}

//---------------------------------------------------------------------------
float loopier::Clip::getScale() const
{
    return scale;
}

//---------------------------------------------------------------------------
void loopier::Clip::setPosition(const float newX, const float newY)
{
    x = newX * ofGetWidth();
    y = newY * ofGetHeight();
    
    ofLogVerbose() << "Clip::" << __FUNCTION__ << "\t" << name << " \tx: " << x << " - y: " << y;
}

//---------------------------------------------------------------------------
void loopier::Clip::setPosition(const ofPoint& newPosition)
{
    setPosition(newPosition.x, newPosition.y);
}

//---------------------------------------------------------------------------
ofPoint loopier::Clip::getPosition() const
{
    return ofPoint(x,y);
}

//---------------------------------------------------------------------------
void loopier::Clip::toggleFullscreen()
{
    bFullscreen = !bFullscreen;
    ofLogVerbose() << "'" << name << "' fullscreen: "<< (bFullscreen? "on" : "off");
}

//---------------------------------------------------------------------------
void loopier::Clip::toggleVisibility()
{
    bVisible = !bVisible;
    ofLogVerbose() << "'" << name << "' visibility: "<< (bVisible? "on" : "off");
}

//---------------------------------------------------------------------------
void loopier::Clip::show()
{
    bVisible = true;
    ofLogVerbose() << "'" << name << "' visibility: on";
}

//---------------------------------------------------------------------------
void loopier::Clip::hide()
{
    bVisible = false;
    ofLogVerbose() << "'" << name << "' visibility: off";
}

//---------------------------------------------------------------------------
void loopier::Clip::setColor(const ofColor & newColor)
{
    color = newColor;
    color.a = alpha * 255;
    ofLogVerbose() << __PRETTY_FUNCTION__ << color;
}

//---------------------------------------------------------------------------
void loopier::Clip::setAlpha(const float newAlpha)
{
    alpha = newAlpha;
    color.a;
}

//---------------------------------------------------------------------------
void loopier::Clip::toggleName()
{
    bDrawName = !bDrawName;
}

//---------------------------------------------------------------------------
void loopier::Clip::showName()
{
    bDrawName = false;
}

//---------------------------------------------------------------------------
void loopier::Clip::hideName()
{
    bDrawName = false;
}

//---------------------------------------------------------------------------
//      TRANSFORMS
//---------------------------------------------------------------------------
void loopier::Clip::flipV()
{
    setScaleY(scaleY * ofSign(scaleY) * (-1));
}

//---------------------------------------------------------------------------
void loopier::Clip::flipH()
{
    setScaleX(scaleX * ofSign(scaleX) * (-1));
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *                                                                       *
// *    NON-MEMBER PUBLIC INTERFACE FUNCTIONS                              *
// *                                                                       *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


loopier::ClipMap        loopier::clips;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    MANAGE RESOURCES                                                   *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool loopier::initResources(string path)
{
    loopier::loadResourceFiles(path);
    loopier::setupCameras();
}

int loopier::loadResourceFiles(string path)
{
    if (path == "") path = "/Users/roger/Library/Application Support/Clip/resources/";
    
    ofLogVerbose() << "Loading resource files from: " << path;
    
    loopier::loadMovies(path);
    loopier::loadFrameLists(path);
}

bool loopier::loadMovies(string path)
{
    ofLogVerbose() << "Loading movie files from: " << path;
    
    ofDirectory dir(path+"movies");
    dir.allowExt("mov");
    vector<ofFile> files = dir.getFiles();
    
    for (int i = 0; i < files.size(); i++) {
        MoviePtr movie(new Movie);
        movie->load(files[i].getAbsolutePath());
        loopier::movies[files[i].getBaseName()] = movie;
    }
    
    ofLogVerbose() << "Loaded " << loopier::movies.size() << " movie files";
    
    return true;
}

bool loopier::loadFrameLists(string path)
{
    ofLogVerbose() << "Loading frame image files from: " << path;
    
    ofDirectory dir(path+"frames");
    
    vector<ofFile> subdirs = dir.getFiles();
    
    for (int x = 0; x < subdirs.size(); x++) {
        ofDirectory subdir = ofDirectory(subdirs[x]);
        if (!subdir.isDirectory()) continue;
        subdir.allowExt("png");
        subdir.allowExt("jpg");
        subdir.allowExt("gif");
        
        string name = subdirs[x].getBaseName(); // folder name used in map
        vector<ofFile> files = subdir.getFiles(); // images in folder
        
        // skip empty folders
        if (files.size() <= 0) {
            ofLogWarning() << "'" << name << "' folder is empty.  Skipping";
            continue;
        }
        
        FrameListPtr frames(new FrameList);     // actual list of frames
        
        for (int i = 0; i < files.size(); i++) {
            ofImage img;
            img.load(files[i].getAbsolutePath());
            frames->push_back(img);
        }
        ofLogVerbose() << "Loaded " << frames->size() << " frames from " << name;
        loopier::frameLists[name] = frames;
    }
    
    return false;
}

bool loopier::setupCameras()
{
    return loopier::CameraPlayer::setupVideoCameras();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    RESOURCE LIST UTILS                                                *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void loopier::listResourceNames()
{
    ofLogNotice() << "Available Resources: ";
    loopier::listMovieNames();
    loopier::listFrameListNames();
    loopier::listVideoCameras();
}

void loopier::listMovieNames()
{
    string msg = "Number of movies:\t" + ofToString(loopier::movies.size());
    loopier::MovieMap::iterator it;
    for (it = loopier::movies.begin(); it != loopier::movies.end(); ++it) {
        msg += "\n\t" + it->first;
    }
    
    ofLogNotice() << msg;
}

void loopier::listFrameListNames()
{
    string msg = "Number of frame lists:\t" + ofToString(loopier::frameLists.size());
    loopier::FrameListMap::iterator it;
    for (it = loopier::frameLists.begin(); it != loopier::frameLists.end(); ++it) {
        msg += "\n\t" + it->first;
    }
    
    ofLogNotice() << msg;
}

void loopier::listVideoCameras()
{
    loopier::CameraPlayer::listVideoCameras();
}



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    MANAGE CLIPS                                                       *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::newClip(string clipname)
{
    return loopier::newClip(clipname, "default");
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::newClip(string clipname, string filename)
{
    loopier::ClipPtr clip(new loopier::Clip(clipname, filename));
    clip->setup();
    clips[clip->getName()] = clip;
    return clip;
}
//---------------------------------------------------------------------------
void loopier::removeClip(const string& clipname)
{
    loopier::clips.erase(clipname);
}

//---------------------------------------------------------------------------
void loopier::clearClips()
{
    loopier::clips.clear();
}

//---------------------------------------------------------------------------
//  UPDATE and DRAW CLIPS

//---------------------------------------------------------------------------
void loopier::updateClips()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).update();
    }
}

//---------------------------------------------------------------------------
void loopier::drawClips()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).draw();
    }
}



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    CLIP LIST UTILS                                                    *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//---------------------------------------------------------------------------

void loopier::listClipNames()
{
    string msg = "Number of clips:\t" + ofToString(clips.size());
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        msg += "\n\t" + it->first;
    }
    
    ofLogNotice() << msg;
}

//---------------------------------------------------------------------------
void loopier::listClips()
{
    string msg = "Number of clips:\t" + ofToString(clips.size());
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
//        (*it->second).listMovies();
    }
}

//---------------------------------------------------------------------------
bool loopier::clipExists(const string clipname)
{
    bool b = clips.count(clipname);
    
    if (!b) {
        string msg = "\tTrying to acces a clip named '" + clipname + "'.\n";
        msg +=  "\t\t\tIt doesn't exist.  Skipping action.";
        ofLogError() << msg;
        ConsoleUI::printError(msg);
    }
    
    return clips.count(clipname);
}


//---------------------------------------------------------------------------
//  SHOW CLIP NAMES
//---------------------------------------------------------------------------
void loopier::toggleClipNames()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).toggleName();
    }
}

//---------------------------------------------------------------------------
void loopier::showClipNames()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).showName();
    }
}

//---------------------------------------------------------------------------
void loopier::hideClipNames()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).hideName();
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    MANAGE SINGLE CLIP                                                 *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//---------------------------------------------------------------------------
//  PLAY CLIPS

//---------------------------------------------------------------------------
void loopier::playClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->play();
}

//---------------------------------------------------------------------------
void loopier::stopClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->stop();
}

//---------------------------------------------------------------------------
void loopier::pauseClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->pause();
}

//---------------------------------------------------------------------------
void loopier::setClipSpeed(const string clipname, const float speed)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setSpeed(speed);
}

//---------------------------------------------------------------------------
void loopier::setClipLoopState(const string clipname, const loopier::LoopType state)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setLoopState(state);
}

//---------------------------------------------------------------------------
//  RESET
//---------------------------------------------------------------------------
void loopier::resetClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->reset();
}

//---------------------------------------------------------------------------
//  MOVE CLIP
//---------------------------------------------------------------------------
void loopier::moveClipTo(const string clipname, const float x, const float y)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setPosition(x, y);
}

//---------------------------------------------------------------------------
//  SCALE CLIP
//---------------------------------------------------------------------------
void loopier::scaleClip(const string clipname, const float scale)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setScale(scale);
}

//---------------------------------------------------------------------------
void loopier::setClipWidth(const string clipname, const float width)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setScaleX(width);
}

//---------------------------------------------------------------------------
void loopier::setClipHeight(const string clipname, const float height)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setScaleY(height);
}

//---------------------------------------------------------------------------
void loopier::scaleUpClip(const string clipname, const float amount)
{
    if(!loopier::clipExists(clipname)) return;
    
    ClipPtr clip = loopier::clips[clipname];
    clip->setScale( clip->getScale() + amount );
}

//---------------------------------------------------------------------------
void loopier::scaleDownClip(const string clipname, const float amount)
{
    if(!loopier::clipExists(clipname)) return;
    
    ClipPtr clip = loopier::clips[clipname];
    clip->setScale( clip->getScale() - amount );
}

//---------------------------------------------------------------------------
void loopier::resetClipScale(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setScale(1.0);
}

//---------------------------------------------------------------------------
void loopier::setClipVFlip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->flipV();
}

//---------------------------------------------------------------------------
void loopier::setClipHFlip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->flipH();
}

//---------------------------------------------------------------------------
//  FULSCREEN
//---------------------------------------------------------------------------
void loopier::toggleFullscreenClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->toggleFullscreen();
}

//---------------------------------------------------------------------------
//  VISIBILITY
//---------------------------------------------------------------------------
void loopier::toggleClipVisibility(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->toggleVisibility();
}

//---------------------------------------------------------------------------
void loopier::showClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->show();
}

//---------------------------------------------------------------------------
void loopier::hideClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->hide();
}

//---------------------------------------------------------------------------
//  COLOR
//---------------------------------------------------------------------------
void loopier::setClipColor(const string clipname, const string& color)
{
    if(!loopier::clipExists(clipname)) return;
    
    vector<string> tokens = ofSplitString(color, ",", true, true);
    
    ofColor c;
    
    if (tokens.size() == 1) {
        c = ofColor(ofToFloat(tokens[0]) * 255);
    } else if (tokens.size() == 2) {
        c = ofColor(ofToFloat(tokens[0]) * 255);
        loopier::clips[clipname]->setAlpha(ofToFloat(tokens[1]));
    } else {
        c.r = ofToFloat(tokens[0]) * 255;
        c.g = ofToFloat(tokens[1]) * 255;
        c.b = ofToFloat(tokens[2]) * 255;
    }
    if (tokens.size() == 4) {
        loopier::clips[clipname]->setAlpha(ofToFloat(tokens[3]));
    }
    
    ofLogVerbose() << __PRETTY_FUNCTION__ << "\t" << c;
    
    loopier::clips[clipname]->setColor(c);
}

void loopier::setClipColor(const string clipname, const ofColor & color)
{
    loopier::clips[clipname]->setColor(color);
}

void loopier::setClipColor(const string clipname, const float& grayscale)
{
    if(!loopier::clipExists(clipname)) return;
    
    loopier::clips[clipname]->setColor(ofColor(grayscale * 255));
}

//---------------------------------------------------------------------------
void loopier::setClipAlpha(const string clipname, const float alpha)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setAlpha(alpha);
}

