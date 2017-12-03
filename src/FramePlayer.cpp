//
//  FramePlayer.cpp
//  clip
//
//  Created by roger on 23/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "FramePlayer.h"
#include "ConsoleUI.h"


loopier::FrameListMap   loopier::frameLists;

loopier::FramePlayer::FramePlayer()
: BasePlayer()
, lastFrameTime(0.0)
{
    frameRate = 12;
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
    
    // FIXME: it crashes
    float rateRatio = (60 / getFrameRate()) / ofGetFrameRate();
    
    if (lastFrameTime < rateRatio ) {
        lastFrameTime += ofGetLastFrameTime();
        return;
    }
    
//    ofLogVerbose() << lastFrameTime << "\t" << frameRate << " / " << ofGetFrameRate() << "\t" << rateRatio;
    
    lastFrameTime = 0;
    
    if (playDirection == loopier::PlayDirection::normal)         nextFrame();
    else if (playDirection == loopier::PlayDirection::reverse)   previousFrame();
}

//---------------------------------------------------------
void loopier::FramePlayer::draw()
{
    if (frames->size() <= 0) return;
    
    frames->at(currentFrame).draw(anchor.x, anchor.y);
}

//---------------------------------------------------------
void loopier::FramePlayer::draw(float x, float y, float w, float h)
{
    if (frames->size() <= 0) return;
    
    frames->at(currentFrame).draw(x, y, w, h);
}

//---------------------------------------------------------
void loopier::FramePlayer::exit()
{
       
}

//---------------------------------------------------------
bool loopier::FramePlayer::loadResource(string resourcename)
{
    // copy frames
    frames = make_shared<FrameList>(*loopier::frameLists.find(resourcename)->second);
    
    ofLogVerbose() << __PRETTY_FUNCTION__ << "Needs imlpementation";
    BasePlayer::loadResource(resourcename);
    ofLogVerbose() << "Finished loading '" << resourcename << "' frame image files to '" << name << "' player";
    return bLoaded;
}

//---------------------------------------------------------
void loopier::FramePlayer::play()
{
    bPlay = true;
}

//---------------------------------------------------------
void loopier::FramePlayer::stop()
{
    bPlay = false;
    currentFrame = 0;
}

//---------------------------------------------------------
float loopier::FramePlayer::getWidth() const
{
    return frames->at(0).getWidth();
}

//---------------------------------------------------------
float loopier::FramePlayer::getHeight() const
{
    return frames->at(0).getHeight();
}

//---------------------------------------------------------
ofTexture & loopier::FramePlayer::getTexture()
{
    return frames->at(0).getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::FramePlayer::getPixels()
{
    return frames->at(0).getPixels();
}

//---------------------------------------------------------
float loopier::FramePlayer::getDuration() const
{
    return frames->size() * (60 / frameRate);
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
    return frames->size();
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
    
    if (currentFrame > frames->size() - 1) {
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
            currentFrame = frames->size() - 1;
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
    vector<ofImage>::iterator pos = frames->begin() + currentFrame;
    frames->insert(pos, img);
    ofLogVerbose() << "Inserted new frame in '" << getName() << "' at: " << currentFrame;
    nextFrame();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------
bool loopier::loadFrameListsDeprecated(string path)
{
//    ofLogVerbose() << "Loading frame image files from: " << path;
//    
//    ofDirectory dir(path+"frames");
//    
//    vector<ofFile> subdirs = dir.getFiles();
//    
//    for (int x = 0; x < subdirs.size(); x++) {
//        ofDirectory subdir = ofDirectory(subdirs[x]);
//        if (!subdir.isDirectory()) continue;
//        subdir.allowExt("png");
//        subdir.allowExt("jpg");
//        subdir.allowExt("gif");
//        
//        string name = subdirs[x].getBaseName(); // folder name used in map
//        vector<ofFile> files = subdir.getFiles(); // images in folder
//        
//        // skip empty folders
//        if (files.size() <= 0) {
//            ofLogWarning() << "'" << name << "' folder is empty.  Skipping";
//            continue;
//        }
//        
//        FrameListPtr frames(new FrameList);     // actual list of frames
//        
//        for (int i = 0; i < files.size(); i++) {
//            ofImage img;
//            img.load(files[i].getAbsolutePath());
//            frames->push_back(img);
//        }
//        ofLogVerbose() << "Loaded " << frames->size() << " frames from " << name;
//        loopier::frameLists[name] = frames;
//    }
//    
//    return loopier::frameLists.size();
}

//---------------------------------------------------------
void loopier::listFrameListNames()
{
//    string msg = "Number of frame lists:\t" + ofToString(loopier::frameLists.size());
//    loopier::FrameListMap::iterator it;
//    for (it = loopier::frameLists.begin(); it != loopier::frameLists.end(); ++it) {
//        msg += "\n\t" + it->first;
//    }
//    
//    ofLogNotice() << msg;
}
