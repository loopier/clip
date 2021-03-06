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
, bSelected(false)
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
//    outputFbo.allocate(player->getWidth(), player->getHeight());
    outputFbo.allocate(ofGetWidth(), ofGetHeight());
    maskFbo.allocate(ofGetWidth(), ofGetHeight());
}

//---------------------------------------------------------------------------
void loopier::Clip::update()
{
    updateChildren();
    absolutePosition.x = position.x - (anchor.x * getWidth());
    absolutePosition.y = position.y - (anchor.y * getHeight());
    
    player->update();
    
    outputFbo.begin();
    ofClear(255,255,255,0);
    player->draw();
    ofPopMatrix();
    outputFbo.end();
    
    if (bMask)  {
        maskFbo.begin();
        ofClear(0);
        ofPushMatrix();
        ofTranslate(absolutePosition.x * (-1), absolutePosition.y * (-1));
        maskPlayer->getTexture().draw(0,0);
        ofPopMatrix();
        maskFbo.end();
        outputFbo.getTexture().setAlphaMask(maskFbo.getTexture());
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
        // I tried to scale the object to match the mask dimensions but it didn't work.
        // See commit #1725f5c046fd95035f3bb97dd3eebdb549c427e4
        outputFbo.draw(absolutePosition, outputFbo.getWidth() * scaleX, outputFbo.getHeight() * scaleY);
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
void loopier::Clip::drawOrigin(const ofColor & c)
{
    ofPushStyle();
    ofSetColor(c);
    ofSetLineWidth(2);
    ofNoFill();
    ofEnableSmoothing();
    ofDrawCircle(getOriginRectangle().getCenter().x, getOriginRectangle().getCenter().y,
                 getOriginRectangle().width / 2, getOriginRectangle().height / 2);
    if (bSelected) {
        ofFill();
        ofSetColor(c.r, c.g, c.b, 100);
    }
    if (getOriginRectangle().inside(ofGetMouseX(), ofGetMouseY())) ofSetColor(255);
    ofDrawCircle(getOriginRectangle().getCenter().x, getOriginRectangle().getCenter().y,
                 getOriginRectangle().width / 2, getOriginRectangle().height / 2);
    ofPopStyle();
}

//---------------------------------------------------------------------------
void loopier::Clip::drawName(const ofColor & c)
{
    if (!bDrawName) return;
    drawOrigin(c);
    ofPushStyle();
    ofSetColor(c);
    ofDrawBitmapString(name, getOriginRectangle().getCenter().x + getOriginRectangle().width/2,
                       getOriginRectangle().getCenter().y -  + getOriginRectangle().height/2);
    ofPopStyle();
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
    return position + player->getPosition();
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
//    ofRectangle box = player->getBoundingBox();
//    float x = position.x - (anchor.x * player->getWidth());
//    float y = position.y - (anchor.y * player->getHeight());
//    box.setPosition(box.getPosition() + ofPoint(x,y));
//    box.setWidth(box.getWidth());
//    box.setHeight(box.getHeight());
    return box;
}

//---------------------------------------------------------------------------
ofRectangle loopier::Clip::getOriginRectangle() const
{
    int size = 20;
    return ofRectangle(getBoundingBox().getCenter().x - (size / 2),
                       getBoundingBox().getCenter().y - (size / 2),
                       size,
                       size);
}

//---------------------------------------------------------------------------
ofPoint loopier::Clip::getOrigin() const
{
    return getOriginRectangle().getCenter();
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
void loopier::Clip::setMask(loopier::ClipPtr mask)
{
    maskClip = mask;
    setMask(mask->getPlayer());
    maskOn();
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
loopier::ClipPtr loopier::Clip::getMaskClip()
{
    return maskClip;
}



//---------------------------------------------------------------------------
void loopier::Clip::toggleName()
{
    bDrawName = !bDrawName;
}

//---------------------------------------------------------------------------
void loopier::Clip::showName()
{
    bDrawName = true;
}

//---------------------------------------------------------------------------
void loopier::Clip::hideName()
{
    bDrawName = false;
}

//---------------------------------------------------------------------------
void loopier::Clip::select(bool b)
{
    bSelected = b;
}

//---------------------------------------------------------------------------
void loopier::Clip::deselect()
{
    select(false);
}

//---------------------------------------------------------------------------
bool loopier::Clip::isSelected()
{
    return bSelected;
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
void loopier::Clip::setInputClip(ClipPtr aClip)
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
void loopier::Clip::addChild(const ClipPtr clip)
{
    children.push_back(clip);
    clip->setOffset(clip->getPosition() - getPosition());
}

//---------------------------------------------------------------------------
void loopier::Clip::removeChild(const ClipPtr clip)
{
    children.erase(find(children.begin(), children.end(), clip));
}

//---------------------------------------------------------------------------
void loopier::Clip::clearChildren()
{
    children.clear();
}

//---------------------------------------------------------------------------
void loopier::Clip::updateChildren()
{
    for (auto &child: children) {
        child->setPosition(getPosition() + child->getOffset());
    }
}

//---------------------------------------------------------------------------
vector<string> loopier::Clip::getChildrenNames()
{
    vector<string> names;
    for (auto &child: children) {
        names.push_back(child->getName());
    }
    return names;
}
