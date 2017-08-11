//
//  Clip.cpp
//  clip
//
//  Created by roger on 10/08/2017.
//
//

#include "Clip.h"

//------------------------------------------------------------------------------------------
//      CLASS FUNCTIONS
//------------------------------------------------------------------------------------------

loopier::ClipMap loopier::clips; // the list of clips available everywhere

//------------------------------------------
//  MANAGE CLIPS
//------------------------------------------
loopier::ClipPtr loopier::newClip(string path, string name)
{
    if (name == "") {
        name = "clip-";
        name += ofToString(ofGetYear());
        name += ofToString(ofGetMonth());
        name += ofToString(ofGetDay());
        name += ofToString(ofGetHours());
        name += ofToString(ofGetMinutes());
        name += ofToString(ofGetSeconds());
    }
    
    loopier::ClipPtr clip(new loopier::Clip(name));
    clip->setup(path);
    clips[name] = clip;
    
    ofLogVerbose() << "Created " << name << " from " << path;
    ofLogVerbose() << "Number of clips: " << clips.size();
    return clip;
}

void loopier::addClip(const ClipPtr clip)
{
    loopier::clips[clip->getName()] = clip;
}

void loopier::removeClip(ClipPtr clip)
{
    // !!! TODO
}

void loopier::removeClipAt(const int index)
{
    // !!! TODO
}

//------------------------------------------
//  UPDATE CLIPS
//------------------------------------------
void loopier::updateClips()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).update();
    }
}

//------------------------------------------
//  DRAW CLIPS
//------------------------------------------
void loopier::drawClips()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).draw();
    }
}

//------------------------------------------
//  PLAY CLIPS
//------------------------------------------
void loopier::playClip(const string clipname)
{
    loopier::clips[clipname]->play();
}

void loopier::stopClip(const string clipname)
{
    loopier::clips[clipname]->stop();
}

void loopier::pauseClip(const string clipname)
{
    loopier::clips[clipname]->pause();
}

void loopier::toggleClipLoopState(const string clipname)
{
    loopier::clips[clipname]->toggleLoopState();
}

//------------------------------------------
//  RESET
//------------------------------------------
void loopier::resetClip(const string clipname)
{
    loopier::clips[clipname]->reset();
}

//------------------------------------------
//  MOVE CLIP
//------------------------------------------
void loopier::moveClipTo(const string clipname, const float x, const float y)
{
    loopier::clips[clipname]->setPosition(x, y);
}

//------------------------------------------
//  SCALE CLIP
//------------------------------------------
void loopier::scaleClip(const string clipname, const float scale)
{
    loopier::clips[clipname]->setScale(scale);
}

void loopier::scaleUpClip(const string clipname, const float amount)
{
    ClipPtr clip = loopier::clips[clipname];
    clip->setScale( clip->getScale() + amount );
}

void loopier::scaleDownClip(const string clipname, const float amount)
{
    ClipPtr clip = loopier::clips[clipname];
    clip->setScale( clip->getScale() - amount );
}

void loopier::resetClipScale(const string clipname)
{
    loopier::clips[clipname]->setScale(1.0);
}

//------------------------------------------
//  FULLSCREEN
//------------------------------------------
void loopier::toggleFullscreenClip(ClipPtr clip)
{
    // !!! TODO
}

void loopier::toggleFullscreenClip(const string clipname)
{
    loopier::clips[clipname]->toggleFullscreen();
}

void loopier::toggleFullscreenClipAt(const int index)
{
    // TODO
}


//------------------------------------------------------------------------------------------
//      CLASS METHODS
//------------------------------------------------------------------------------------------

loopier::Clip::Clip()
: name("noname")
, x(0)
, y(0)
, width(640)
, height(400)
, scale(1.0)
, fullscreen(false)
{
    ofLogVerbose() << __FUNCTION__;
    enableNewOscMessageListener();
}

loopier::Clip::Clip(string& clipname)
: name(clipname)
, x(0)
, y(0)
, width(640)
, height(400)
, scale(1.0)
, fullscreen(false)
{
    enableNewOscMessageListener();
}

loopier::Clip::~Clip()
{
    ofLogVerbose() << __FUNCTION__ << ": Unregistering from incoming osc messages notifications";
    ofRemoveListener(osc.newOscMessageEvent, this, &loopier::Clip::processOscMessage);
}

void loopier::Clip::enableNewOscMessageListener()
{
    ofLogVerbose() << "Clip: Registering to incoming osc messages notifications";
    ofAddListener(osc.newOscMessageEvent, this, &loopier::Clip::processOscMessage);
}

void loopier::Clip::setup(string& moviePath,bool bPlay)
{
    player.load(moviePath);
    width = player.getWidth();
    height = player.getHeight();
    
    player.setLoopState(OF_LOOP_NORMAL);
    if (bPlay)   player.play();
    
}

void loopier::Clip::update()
{
    player.update();
}

void loopier::Clip::draw()
{
    float posx = (fullscreen? 0 : x);
    float posy = (fullscreen? 0 : y);
    player.draw(posx, posy, width, height);
}

void loopier::Clip::reset()
{
    width = player.getWidth();
    height = player.getHeight();
    x = ofGetWidth() / 2 - player.getWidth() / 2;
    y = ofGetHeight() / 2 - player.getHeight() / 2;
    scale = 1.0;
}

void loopier::Clip::setName(const string &newName)
{
    ofLogVerbose() << name << " changing name to: " << scale;
    name = newName;
}

string loopier::Clip::getName() const
{
    return name;
}

void loopier::Clip::play()
{
    player.isPlaying()? player.setPaused(true) : player.play();
    
    ofLogVerbose() << (player.isPlaying()? "play: " : "pause: ") << name ;
}

void loopier::Clip::stop()
{
    player.stop();
    
    ofLogVerbose() << "stop: " << name ;
}

void loopier::Clip::pause(bool bPause)
{
    player.setPaused(bPause);
    
    ofLogVerbose() << "pause: " << name ;
}

void loopier::Clip::toggleLoopState()
{
    string state = "";
    if (player.getLoopState() == OF_LOOP_NONE) {
        player.setLoopState(OF_LOOP_NORMAL);
        state = "normal";
    } else if (player.getLoopState() == OF_LOOP_NORMAL) {
        player.setLoopState(OF_LOOP_PALINDROME);
        state = "palindrome";
    } else {
        player.setLoopState(OF_LOOP_NONE);
        state = "none";
    }
    
    ofLogVerbose() << "loop: " << state << " " << player.getLoopState();
}

void loopier::Clip::setScale(const float newScale)
{
    
    scale = newScale;
    
    if (scale <= 0.1) {
        scale = 0.1;
    }
    
    width = player.getWidth() * scale;
    height = player.getHeight() * scale;
    
    ofLogVerbose() << name << " scale: " << scale;
}

float loopier::Clip::getScale() const
{
    return scale;
}

void loopier::Clip::setPosition(const float newX, const float newY)
{
    x = newX;
    y = newY;
    
    ofLogVerbose() << name << " position: " << x << " - " << y;
}

void loopier::Clip::setPosition(const ofPoint& newPosition)
{
    setPosition(newPosition.x, newPosition.y);
}

ofPoint loopier::Clip::getPosition() const
{
    return ofPoint(x,y);
}

void loopier::Clip::toggleFullscreen()
{
    fullscreen = !fullscreen;
    updateFullscreen();
}

void loopier::Clip::updateFullscreen()
{
    if (fullscreen) {
        width = ofGetWidth();
        height = ofGetHeight();
    } else {
        width = player.getWidth() * getScale();
        height = player.getHeight() * getScale();
    }
    
    ofLogVerbose() << name << " fullscreen: "<< (fullscreen? "on" : "off");
}

void loopier::Clip::processOscMessage(ofxOscMessage& inMessage)
{
    ofLogVerbose() <<  "Clip porcessing osc message";
    loopier::printOscMessage(inMessage);
}