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
: bMask(false)
, name(clipname)
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
, depth(0)
, bFullscreen(false)
, bVisible(true)
, bDrawName(false)
, loopState(LoopType::normal)
{
//    setResource(resourcename);
    
    ofAddListener(ofEvents().update, this, &Clip::update);
    // -- DISABLED --   I need to control drawing order (or depth).  I do it manually because
    //                  I don't know how to do it automatic
    //    ofAddListener(ofEvents().draw, this, &Clip::draw);
}

//---------------------------------------------------------
loopier::Clip::~Clip(){
    
}

//---------------------------------------------------------------------------
void loopier::Clip::setup(PlayerPtr aplayer)
{
    sequenceOrder.push_back(0);
    aplayer->setLoopState(loopState);
    outputFbo.allocate(ofGetWidth(), ofGetHeight());
//    width = aplayer->getWidth();
//    height = aplayer->getWidth();
    outputFbo.setAnchorPercent(0.5, 0.5);
    
    setPosition(0.5,0.5);
    setPlayer(aplayer);
//    reset();
}

//---------------------------------------------------------------------------
void loopier::Clip::update()
{
    //    if (bPlaySequence) updateSequence();
    player->update();
    
    outputFbo.begin();
    ofClear(255,255,255,0);
    ofPushMatrix();
    ofTranslate(outputFbo.getWidth()/2 - player->getWidth()/2,
                outputFbo.getHeight()/2 - player->getHeight()/2);
    player->draw();
    ofPopMatrix();
    outputFbo.end();
    
    if (bMask)  {
        outputFbo.getTexture().setAlphaMask(maskPlayer->getTexture());
        
    } else {
        outputFbo.getTexture().disableAlphaMask();
    }
    
    outputFbo.readToPixels(outputPixels);
    
}

//---------------------------------------------------------------------------
void loopier::Clip::draw()
{
    if (!bVisible) return;
    
    ofPushStyle();
    ofSetColor(color);
    
    if (bFullscreen) {
        int fx = ofGetWidth() / 2;
        int fy = ofGetHeight() / 2;
        int fw = ofGetWidth() * ofSign(scaleX);
        int fh = ofGetHeight() * ofSign(scaleY);
        
        outputFbo.draw(fx, fy, fw, fh);
    } else {
        outputFbo.draw(x, y, width, height);
        if (bDrawName)  ofDrawBitmapString(name, x, y);
    }
    ofPopStyle();
}

//---------------------------------------------------------------------------
void loopier::Clip::update(ofEventArgs& e)
{
    update();
}

//---------------------------------------------------------------------------
void loopier::Clip::draw(ofEventArgs& e)
{
    draw();
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
    
    ofLogVerbose() << name << " scale: " << scale;
}

//---------------------------------------------------------------------------
void loopier::Clip::setScaleX(const float newScale)
{
    scaleX = newScale * ofSign(scaleX);
    width = ofGetWidth() * scaleX;
}

//---------------------------------------------------------------------------
void loopier::Clip::setScaleY(const float newScale)
{
    scaleY = newScale * ofSign(scaleY);
    height = ofGetHeight() *  scaleY;
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
    return ofPoint(x / ofGetWidth(),y / ofGetHeight());
}

//---------------------------------------------------------------------------
void loopier::Clip::setWidth(const float w)
{
    width = w;
}

//---------------------------------------------------------------------------
void loopier::Clip::setHeight(const float h)
{
    height = h;
}

//---------------------------------------------------------------------------
float loopier::Clip::getWidth() const
{
    return width;
}

//---------------------------------------------------------------------------
float loopier::Clip::getHeight() const
{
    return height;
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
//    color.a = alpha * 255;
    ofLogVerbose() << __PRETTY_FUNCTION__ << color;
}

//---------------------------------------------------------------------------
void loopier::Clip::setAlpha(const float newAlpha)
{
    alpha = newAlpha;
    color.a = newAlpha;
//    color = ofColor(color.r, color.g, color.b, newAlpha);
}

//---------------------------------------------------------------------------
void loopier::Clip::setMask(loopier::PlayerPtr mask)
{
    maskPlayer = mask;
    maskOn();
}

//---------------------------------------------------------------------------
void loopier::Clip::maskOn()
{
    bMask = true;
}

//---------------------------------------------------------------------------
void loopier::Clip::maskOff()
{
    bMask = false;
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


//---------------------------------------------------------------------------
void loopier::Clip::setPlayer(loopier::PlayerPtr aPlayer)
{
    ofLogVerbose() << __PRETTY_FUNCTION__;
    player = aPlayer;
}


//---------------------------------------------------------------------------
loopier::PlayerPtr loopier::Clip::getPlayer() const
{
    return player;
}


//---------------------------------------------------------------------------
ofTexture & loopier::Clip::getTexture() const
{
    return player->getTexture();
}


//---------------------------------------------------------------------------
ofPixels &  loopier::Clip::getPixels()
{
    return player->getPixels();
}


//---------------------------------------------------------------------------
ofImage & loopier::Clip::getImage() const
{
    return player->getImage();
}


//---------------------------------------------------------------------------
void loopier::Clip::setDepth(int order)
{
    depth = order;
}
//---------------------------------------------------------------------------
int loopier::Clip::getDepth() const
{
    return depth;
}
