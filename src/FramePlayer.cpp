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
    frameRate = 24;
}


loopier::FramePlayer::FramePlayer(FrameListPtr framelist)
: BasePlayer()
, lastFrameTime(0.0)
{
    if (framelist->size() == 0) {
        width = ofGetWidth();
        height = ofGetHeight();
    } 
    frameRate = 24;
    frames = framelist;
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
    if (!bPlay)                 return;
    if (frames->size() <= 0)    return;
    if (currentFrame > frames->size()) currentFrame = frames->size() - 1;
    if (currentFrame < 0) currentFrame = 0;
    
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
    if (frames->size() <= 0)            return;
    if (currentFrame >= frames->size()) return;
    frames->at(currentFrame).draw(0,0);
    
    ofRectangle blobrect(position, width, height);
    ofRectangle framerect(0, 0,
                          frames->at(currentFrame).getWidth(),
                          frames->at(currentFrame).getHeight());
    
//    ofSetColor(255, 0, 255);
//    ofNoFill();
//    ofDrawRectangle(framerect);
//    ofDrawRectangle(blobrect);
//    ofDrawBitmapString("blob "+ofToString(blobrect.x)+" "+ofToString(blobrect.y), blobrect.x, blobrect.y-5);
//    ofDrawBitmapString("frame "+ofToString(framerect.x)+" "+ofToString(framerect.y), framerect.x, framerect.y-20);
//    ofDrawBitmapString(ofToString(blobrect.getCenter().x)+" "+ofToString(blobrect.getCenter().y), blobrect.getCenter().x+15, blobrect.getCenter().y);
//    ofDrawBitmapString(ofToString(framerect.getCenter().x)+" "+ofToString(framerect.getCenter().y), framerect.getCenter().x+20, framerect.getCenter().y);
//    ofDrawCircle(framerect.getCenter(), 15);
//    ofDrawCircle(blobrect.getCenter(), 10);
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
    if (frames->size() <= 0) return;
    return frames->at(currentFrame).getWidth();
}

//---------------------------------------------------------
float loopier::FramePlayer::getHeight() const
{
    if (frames->size() <= 0) return;
    return frames->at(currentFrame).getHeight();
}

//---------------------------------------------------------
ofTexture & loopier::FramePlayer::getTexture()
{
    if (frames->size() <= 0) return;
    return frames->at(currentFrame).getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::FramePlayer::getPixels()
{
    if (frames->size() <= 0) return;
    return frames->at(currentFrame).getPixels();
}

//---------------------------------------------------------
ofImage & loopier::FramePlayer::getImage()
{
    if (frames->size() <= 0) return;
    return frames->at(currentFrame);
}

//---------------------------------------------------------
loopier::FrameListPtr loopier::FramePlayer::getFrames()
{
    return frames;
}

//---------------------------------------------------------
float loopier::FramePlayer::getDuration() const
{
    return frames->size() * (60 / frameRate);
}


//---------------------------------------------------------
void loopier::FramePlayer::setSpeed(const float newSpeed)
{
    BasePlayer::setSpeed(newSpeed);
    frameRate = speed * ofGetFrameRate();
    ofLogVerbose() << "FPS: " << frameRate << "\tSpeed: " << speed << "\tofFps: " << ofGetFrameRate();
}

//---------------------------------------------------------
void loopier::FramePlayer::setFrameRate(const int fps)
{
    frameRate = fps;
    speed = (60 / frameRate) / ofGetFrameRate();
}

//---------------------------------------------------------
void loopier::FramePlayer::setFrame(const int frame)
{
    currentFrame = frame % frames->size();
    ofLogWarning() << "There are only " << frames->size() << " frames in '" << name << "'.  Wrapping frame to number " << currentFrame;
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
            changePlayDirection();
            currentFrame--;
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
            changePlayDirection();
            currentFrame++;
        } else if (loopState == loopier::LoopType::none) {
            currentFrame++;
            stop();
        } else if (loopState == loopier::LoopType::once) {
            stop();
        }
    }
}

//---------------------------------------------------------
void loopier::FramePlayer::lastFrame()
{
    currentFrame = frames->size() - 1;
}

//---------------------------------------------------------
void loopier::FramePlayer::addFrame(ofImage & img)
{
    frames->push_back(img);
}

//---------------------------------------------------------
void loopier::FramePlayer::addFrame()
{
    addFrame(inputPlayer->getImage());
}

//---------------------------------------------------------
void loopier::FramePlayer::insertFrame(ofImage & img)
{
    vector<ofImage>::iterator pos = frames->begin() + currentFrame;
    frames->insert(pos, img);
    ofLogVerbose() << "Inserted new frame in '" << getName() << "' at: " << currentFrame;
    nextFrame();
}

//---------------------------------------------------------
void loopier::FramePlayer::removeFrame()
{
    if (frames->size() <= 0) return;
    frames->erase(frames->begin() + currentFrame);
//    if (frames->size() == 0) addEmptyFrame();
//    previousFrame();
}

//---------------------------------------------------------
void loopier::FramePlayer::clear()
{
    frames->clear();
//    addEmptyFrame();
//    firstFrame();
}

//---------------------------------------------------------
void loopier::FramePlayer::addEmptyFrame()
{
    ofImage img;
    img.load("images/transparent.png");
    frames->push_back(img);
}