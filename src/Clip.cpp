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
, resourceName(resourcename)
, position(0,0)
, absolutePosition(0,0)
, offset(0,0)
, width(ofGetWidth())
, height(ofGetHeight())
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
    ofRemoveListener(ofEvents().update, this, &Clip::update);
}

//---------------------------------------------------------------------------
void loopier::Clip::setup(PlayerPtr aplayer)
{
    sequenceOrder.push_back(0);
    aplayer->setLoopState(loopState);
    
    setPlayer(aplayer);
    setAnchorPercent(0.5, 0.5);
    outputFbo.clear();
    outputFbo.allocate(player->getWidth(), player->getHeight());
    outputFbo.setAnchorPercent(0.5, 0.5);
}

//---------------------------------------------------------------------------
void loopier::Clip::update()
{
    updateParent();
    absolutePosition.x = position.x - (anchor.x * getWidth());
    absolutePosition.y = position.y - (anchor.y * getHeight());
    
    player->update();
    
    if (bMask)  {
        outputFbo.getTexture().setAlphaMask(maskPlayer->getTexture());
        
    } else {
        outputFbo.getTexture().disableAlphaMask();
    }
    
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
        ofPushMatrix();
        ofTranslate(absolutePosition);
        ofScale(scaleX, scaleY);
        player->draw();
        ofPopMatrix();
        ofSetColor(0, 255, 255);
        if (bDrawName)  ofDrawBitmapString(name, anchor.x, anchor.y);
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
//    player->setAnchorPercent(anchorPercentX, anchorPercentY);
    position.x = ofGetWidth() / 2;
    position.y = ofGetHeight() / 2;
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
void loopier::Clip::setResourceName(const string & newName)
{
    ofLogVerbose() << name << " using resource: " << newName;
    resourceName = newName;
}

//---------------------------------------------------------------------------
string loopier::Clip::getResourceName() const
{
    return resourceName;
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
bool loopier::Clip::isPlaying()
{
    return player->isPlaying();
}

//---------------------------------------------------------------------------
void loopier::Clip::setLoopState(const loopier::LoopType state)
{
    loopState = state;
    player->setLoopState(loopState);
    if (player->isPaused()) player->play();
}

//---------------------------------------------------------------------------
loopier::LoopType & loopier::Clip::getLoopState()
{
    return loopState;
}

//---------------------------------------------------------------------------
void loopier::Clip::setPlayDirection(const loopier::PlayDirection direction)
{
    player->setPlayDirection(direction);
    if (player->isPaused()) player->play();
}

//---------------------------------------------------------------------------
loopier::PlayDirection & loopier::Clip::getPlayDirection()
{
    player->getPlayDirection();
}

//---------------------------------------------------------------------------
void loopier::Clip::changePlayDirection()
{
    player->changePlayDirection();
    if (player->isPaused()) player->play();
}

//---------------------------------------------------------------------------
void loopier::Clip::setSpeed(const float newSpeed)
{
    player->setSpeed(newSpeed);
}

//---------------------------------------------------------------------------
float loopier::Clip::getSpeed()
{
    return player->getSpeed();
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
float loopier::Clip::getScaleX() const
{
    return scaleX;
}

//---------------------------------------------------------------------------
float loopier::Clip::getScaleY() const
{
    return scaleY;
}

//---------------------------------------------------------------------------
void loopier::Clip::setAnchorPercent(const float anchorX, const float anchorY)
{
    setAnchor(ofPoint(anchorX, anchorY));
}

//---------------------------------------------------------------------------
void loopier::Clip::setAnchorPercent(const ofPoint & newAnchorPercent)
{
    setAnchorPercent(newAnchorPercent.x, newAnchorPercent.y);
}

//---------------------------------------------------------------------------
void loopier::Clip::setAnchor(const ofPoint & newAnchor)
{
    anchor = newAnchor;
}

//---------------------------------------------------------------------------
ofPoint & loopier::Clip::getAnchor()
{
    return anchor;
}

//---------------------------------------------------------------------------
void loopier::Clip::setPosition(const float x, const float y)
{
    position.x = x;
    position.y = y;
}

//---------------------------------------------------------------------------
void loopier::Clip::setPosition(const ofPoint& newPosition)
{
    setPosition(newPosition.x, newPosition.y);
}

//---------------------------------------------------------------------------
ofPoint loopier::Clip::getPosition() const
{
    return position;
}

//---------------------------------------------------------------------------
ofPoint loopier::Clip::getAbsolutePosition() const
{
    return absolutePosition;
}

//---------------------------------------------------------------------------
void loopier::Clip::setOffset(const ofPoint & point)
{
    setOffset(point.x, point.y);
}

//---------------------------------------------------------------------------
void loopier::Clip::setOffset(const float x, const float y)
{
    offset.x = x;
    offset.y = y;
}

//---------------------------------------------------------------------------
ofPoint & loopier::Clip::getOffset()
{
    return offset;
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
    return player->getWidth() * scaleX;
}

//---------------------------------------------------------------------------
float loopier::Clip::getHeight() const
{
    return player->getHeight() * scaleY;
}

//---------------------------------------------------------------------------
ofRectangle loopier::Clip::getBoundingBox() const
{
    ofRectangle box = player->getBoundingBox();
    box.setPosition(box.getPosition() + getAbsolutePosition());
    box.setWidth(box.getWidth() * getScaleX());
    box.setHeight(box.getHeight() * getScaleY());
    return box;
}

//---------------------------------------------------------------------------
void loopier::Clip::toggleFullscreen()
{
    bFullscreen = !bFullscreen;
    ofLogVerbose() << "'" << name << "' fullscreen: "<< (bFullscreen? "on" : "off");
}

//---------------------------------------------------------------------------
bool loopier::Clip::isFullscreen()
{
    return bFullscreen;
}

//---------------------------------------------------------------------------
void loopier::Clip::toggleVisibility()
{
    bVisible = !bVisible;
    ofLogVerbose() << "'" << name << "' visibility: "<< (bVisible? "on" : "off");
}

//---------------------------------------------------------------------------
bool loopier::Clip::isVisible()
{
    return bVisible;
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
ofColor & loopier::Clip::getColor()
{
    return color;
}

//---------------------------------------------------------------------------
void loopier::Clip::setAlpha(const float newAlpha)
{
    alpha = newAlpha;
    color.a = newAlpha;
//    color = ofColor(color.r, color.g, color.b, newAlpha);
}

//---------------------------------------------------------------------------
float loopier::Clip::getAlpha()
{
    return color.a;
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
bool loopier::Clip::isFlippedV()
{
    return bFlipV;
}

//---------------------------------------------------------------------------
void loopier::Clip::flipH()
{
    setScaleX(scaleX * ofSign(scaleX) * (-1));
}

//---------------------------------------------------------------------------
bool loopier::Clip::isFlippedH()
{
    return bFlipH;
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
ofPoint loopier::Clip::getPlayerRelativePosition() const
{
    return ofPoint(anchor - player->getPosition());;
}


//---------------------------------------------------------------------------
void loopier::Clip::setInputClip(shared_ptr<Clip> aClip)
{
    player->setInputPlayer(aClip->getPlayer());
}


//---------------------------------------------------------------------------
ofTexture & loopier::Clip::getTexture()
{
    return outputFbo.getTexture();
}


//---------------------------------------------------------------------------
ofPixels &  loopier::Clip::getPixels()
{
    outputFbo.readToPixels(outputPixels);
    return outputPixels;
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

//---------------------------------------------------------------------------
void loopier::Clip::setParent(const shared_ptr<Clip> clip)
{
    parent = clip;
    setOffset(getPosition() - parent->getPosition());
}

//---------------------------------------------------------------------------
string loopier::Clip::getParentName()
{
    string parentname;
    if (parent != NULL) return parent->getParentName();
    else                return "";
}

//---------------------------------------------------------------------------
void loopier::Clip::updateParent()
{
    if (!parent) return;
    if (parent->getName() == "") return;
    setPosition(parent->getPosition()+offset);
}

//---------------------------------------------------------------------------
void loopier::Clip::removeParent()
{
    if (!parent) return;
    if (parent->getName() == "") return;
    setPosition(parent->getPosition() + getOffset());
    parent = shared_ptr<Clip>(new Clip);
}
