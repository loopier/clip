//
//  Clip.cpp
//  clip
//
//  Created by roger on 10/08/2017.
//
//

#include "Clip.h"


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//      INTERFACE FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------

loopier::ClipMap loopier::clips; // the list of clips available everywhere

//------------------------------------------
//  MANAGE CLIPS
//------------------------------------------
loopier::ClipPtr loopier::newClip(string name)
{
    loopier::newClip(name, ofFilePath::getUserHomeDir()+"/Library/Application Support/Clip/resources/movies/");
}

loopier::ClipPtr loopier::newClip(string name, string path)
{
    string basename = ofFile(name).getBaseName();
    path += basename + "/";
    loopier::ClipPtr clip(new loopier::Clip(name, path));
    clip->setup();
    clips[clip->getName()] = clip;
    
    ofLogNotice() << "Number of clips: " << clips.size();
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

//------------------------------------------
//  ALPHA
//------------------------------------------
void loopier::setClipAlpha(const string clipname, const float alpha)
{
    loopier::clips[clipname]->setAlpha(alpha);
}


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//      CLASS METHODS
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//------------------------------------------
//  CONSTRUCTORS
//------------------------------------------
//loopier::Clip::Clip()
//{
//    // --- DISABLED ---
//}

//loopier::Clip::Clip(string& clipname)
//: name(clipname)
//, extension("mov")
//, basepath(ofFilePath::getUserHomeDir()+"/Library/Application Support/Clip/resources/resources/movies/")
//, x(0)
//, y(0)
//, width(640)
//, height(400)
//, scale(1.0)
//, fullscreen(false)
//, alpha(1.0)
//{
//    removeExtensionFromName();
//}

loopier::Clip::Clip(string& clipname, string& path)
: name(clipname)
, extension(".mov")
, path(path)
, x(0)
, y(0)
, width(640)
, height(400)
, scale(1.0)
, fullscreen(false)
, alpha(1.0)
{
    name = ofFile(clipname).getBaseName();
    extension = ofFile(clipname).getExtension();
}

loopier::Clip::~Clip()
{
    
}

void loopier::Clip::setup(bool bPlay)
{
    string fullpath = path + name + "." + extension;
    ofLogNotice() << "Clip '" << name << "'\t-\tLoading " << fullpath;
    player.load(fullpath);
    reset();
    
    player.setLoopState(OF_LOOP_NORMAL);
    if (bPlay)   player.play();
    
}

void loopier::Clip::update()
{
    player.update();
}

void loopier::Clip::draw()
{
    ofSetColor(255,255,255, 255 * alpha);
    float posx = (fullscreen? 0 : x);
    float posy = (fullscreen? 0 : y);
    player.draw(posx, posy, width, height);
}

void loopier::Clip::reset()
{
    width = player.getWidth();
    height = player.getHeight();
    player.setAnchorPoint(width/2, height/2);
    x = ofGetWidth() / 2;
    y = ofGetHeight() / 2;
    scale = 1.0;
    alpha = 1.0;
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
    
    ofLogVerbose() << "Clip::" << __FUNCTION__ << "\t" << name << " \tx: " << x << " - y: " << y;
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

void loopier::Clip::setAlpha(const float newAlpha)
{
    alpha = newAlpha;
}

//------------------------------------------------------------------------------------------
//      HELPERS
//------------------------------------------------------------------------------------------

