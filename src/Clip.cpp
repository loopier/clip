//
//  Clip.cpp
//  clip
//
//  Created by roger on 10/08/2017.
//
//

#include "Clip.h"


loopier::ClipMap loopier::clips; // the list of clips available everywhere

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//      INTERFACE FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------

//------------------------------------------
//  MANAGE CLIPS
//------------------------------------------

loopier::ClipPtr loopier::newClip(string clipname)
{
    return loopier::newClip(clipname, "default");
}

loopier::ClipPtr loopier::newClip(string clipname, string moviename)
{
    loopier::ClipPtr clip(new loopier::Clip(clipname, moviename));
    clip->setup();
    clips[clip->getName()] = clip;
    return clip;
}

void loopier::removeClip(const string& clipname)
{
    loopier::clips.erase(clipname);
}

void loopier::clearClips()
{
    loopier::clips.clear();
}

//------------------------------------------
//  UPDATE and DRAW CLIPS
//------------------------------------------
void loopier::updateClips()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).update();
    }
}

void loopier::drawClips()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).draw();
    }
}

//------------------------------------------
//  CLIP LIST UTILS
//------------------------------------------

void loopier::listClipNames()
{
    string msg = "Number of clips:\t" + ofToString(clips.size());
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        msg += "\n\t" + it->first;
    }
    
    ofLogNotice() << msg;
}

void loopier::listClips()
{
    string msg = "Number of clips:\t" + ofToString(clips.size());
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).listMovies();
    }
    
//    ofLogNotice() << msg;
}

bool loopier::clipExists(const string clipname)
{
    bool b = clips.count(clipname);
    
    if (!b) {
        ofLogError() << "\tTrying to acces a clip named '" << clipname << "'.\n"
        <<  "\t\t\tIt doesn't exist.  Skipping action.";
    }
    
    return clips.count(clipname);
}


//------------------------------------------
//  SHOW CLIP NAMES
//------------------------------------------
void loopier::toggleClipNames()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).toggleName();
    }
}

void loopier::showClipNames()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).showName();
    }
}

void loopier::hideClipNames()
{
    loopier::ClipMap::iterator it;
    for (it = loopier::clips.begin(); it != loopier::clips.end(); ++it) {
        (*it->second).hideName();
    }
}

//------------------------------------------
//  SINGLE CLIP MANAGEMENT
//------------------------------------------


//------------------------------------------
//  PLAY CLIPS
//------------------------------------------
void loopier::addMovieToClip(const string clipname, const string moviename)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->addMovie(moviename);
}

void loopier::playClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->play();
}

void loopier::stopClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->stop();
}

void loopier::pauseClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->pause();
}

void loopier::setClipSpeed(const string clipname, const float speed)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setSpeed(speed);
}

void loopier::setClipLoopState(const string clipname, const ofLoopType state)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setLoopState(state);
}

//------------------------------------------
//  RESET
//------------------------------------------
void loopier::resetClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->reset();
}

//------------------------------------------
//  MOVE CLIP
//------------------------------------------
void loopier::moveClipTo(const string clipname, const float x, const float y)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setPosition(x, y);
}

//------------------------------------------
//  SCALE CLIP
//------------------------------------------
void loopier::scaleClip(const string clipname, const float scale)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setScale(scale);
}

void loopier::scaleUpClip(const string clipname, const float amount)
{
    if(!loopier::clipExists(clipname)) return;
    
    ClipPtr clip = loopier::clips[clipname];
    clip->setScale( clip->getScale() + amount );
}

void loopier::scaleDownClip(const string clipname, const float amount)
{
    if(!loopier::clipExists(clipname)) return;
    
    ClipPtr clip = loopier::clips[clipname];
    clip->setScale( clip->getScale() - amount );
}

void loopier::resetClipScale(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setScale(1.0);
}

void loopier::toggleFullscreenClip(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->toggleFullscreen();
}

//------------------------------------------
//  ALPHA
//------------------------------------------
void loopier::setClipAlpha(const string clipname, const float alpha)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setAlpha(alpha);
}

//------------------------------------------
//  MANAGING CLIP'S MOVIES
//------------------------------------------
void loopier::listClipMovies(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->listMovies();
}

void loopier::setClipMovie(const string clipname, const int index)
{
    if(!loopier::clipExists(clipname)) return;
    
    loopier::clips[clipname]->setMovie(index);
    loopier::clips[clipname]->setPlayMovieSequence(false);
}

void loopier::playClipMovieSequence(const string clipname)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setPlayMovieSequence(true);
}

void loopier::setClipMovieSequenceOrder(const string clipname, const string sequence)
{
    if(!loopier::clipExists(clipname)) return;
    loopier::clips[clipname]->setMovieSequenceOrder(sequence);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//      CLASS METHODS
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//------------------------------------------
//  CONSTRUCTORS
//------------------------------------------
loopier::Clip::Clip()
{
    // --- DISABLED ---
}

loopier::Clip::Clip(string& clipname, string& moviename)
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
, fullscreen(false)
, alpha(1.0)
, bDrawName(false)
, loopState(OF_LOOP_NORMAL)
{
    addMovie(moviename);
}

loopier::Clip::~Clip()
{
    
}

void loopier::Clip::setup(bool bPlay)
{
    sequenceOrder.push_back(0);
    movie = movies[0];
    movie->setLoopState(loopState);
    if (bPlay)   movie->play();
    
    reset();
}

void loopier::Clip::update()
{
    if (bPlaySequence) updateSequence();
    movie->update();
}

void loopier::Clip::draw()
{
    ofSetColor(255,255,255, 255 * alpha);
    
    if (fullscreen) {
        movie->setAnchorPercent(0, 0);
        movie->draw(0, 0, ofGetWidth(), ofGetHeight());
    } else {
        movie->setAnchorPercent(anchorPercentX, anchorPercentY);
        movie->draw(x, y, width, height);
        if (bDrawName)  ofDrawBitmapString(name, x, y);
    }
    
}

void loopier::Clip::reset()
{
    width = movie->getWidth();
    height = movie->getHeight();
    movie->setAnchorPercent(anchorPercentX, anchorPercentY);
    x = ofGetWidth() / 2;
    y = ofGetHeight() / 2;
    scale = 1.0;
    scaleX = scale;
    scaleY = scale;
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
    movie->isPlaying()? movie->setPaused(true) : movie->play();
    
    ofLogVerbose() << (movie->isPlaying()? "play: " : "pause: ") << name ;
}

void loopier::Clip::stop()
{
    movie->stop();
    
    ofLogVerbose() << "stop: " << name ;
}

void loopier::Clip::pause(bool bPause)
{
    movie->setPaused(bPause);
    
    ofLogVerbose() << "pause: " << name ;
}

void loopier::Clip::setLoopState(const ofLoopType state)
{
    loopState = state;
    movie->setLoopState(loopState);
    if (movie->isPaused()) movie->play();
}

void loopier::Clip::setSpeed(const float newSpeed)
{
    movie->setSpeed(newSpeed);
}

void loopier::Clip::setScale(const float newScale)
{
    
    scale = newScale;
    
    if (scale <= 0.1) {
        scale = 0.1;
    }
    
    scaleX = scale;
    scaleY = scale;
    
    width = movie->getWidth() * scaleX;
    height = movie->getHeight() * scaleY;
    
    ofLogVerbose() << name << " scale: " << scale;
}

float loopier::Clip::getScale() const
{
    return scale;
}

void loopier::Clip::setPosition(const float newX, const float newY)
{
    x = newX * ofGetWidth();
    y = newY * ofGetHeight();
    
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
    fullscreen? movie->setAnchorPercent(0, 0) : movie->setAnchorPercent(0.5, 0.5);
    ofLogVerbose() << name << " fullscreen: "<< (fullscreen? "on" : "off");
}

void loopier::Clip::setAlpha(const float newAlpha)
{
    alpha = newAlpha;
}

void loopier::Clip::toggleName()
{
    bDrawName = !bDrawName;
}

void loopier::Clip::showName()
{
    bDrawName = false;
}

void loopier::Clip::hideName()
{
    bDrawName = false;
}

//------------------------------------------------------------------------------------------
//      MANAGING MOVIES
//------------------------------------------------------------------------------------------
void loopier::Clip::listMovies()
{
    string msg = "'" + name + "' has " + ofToString(movies.size()) + " movies:";
    
    for (int i = 0; i < movies.size(); i++)
    {
        msg += "\n\t" + ofToString(i) + "\t" + movies[i]->getMoviePath();
    }
    
    ofLogNotice() << msg;
}

loopier::MoviePtr loopier::Clip::addMovie(const string & moviename)
{
    MoviePtr movie = make_shared<Movie>(loopier::Video::copyMovie(moviename));
    movies.push_back(movie);
    
    ofLogVerbose() << "'" << moviename << "' movie added to clip '" << name << "'";
    
    return movie;
}

void loopier::Clip::setMovie(int index)
{
    movie->stop();
    index = min(index, int(movies.size()-1));
    movie = movies[index];
    movie->play();
    movie->setAnchorPercent(anchorPercentX, anchorPercentY);
    
    ofLogVerbose() << "'" << name << "' set current movie to: " << movie->getMoviePath();
}

void loopier::Clip::setPlayMovieSequence(const bool & bseq)
{
    bPlaySequence = bseq;
    if (bseq)   movie->setLoopState(OF_LOOP_NONE);
    else        movie->setLoopState(loopState);
}

void loopier::Clip::setMovieSequenceOrder(const vector<int>& newSequence)
{
    
    sequenceIndex = 0;
    
    sequenceOrder.clear();
    sequenceOrder = newSequence;
    
    string msg = "Sequence oder for " + name + ": ";
    for(int i=0; i < sequenceOrder.size(); i++) {
        msg += ofToString(sequenceOrder[i]) + " ";
    }
    
    ofLogVerbose() << msg;
}

void loopier::Clip::setMovieSequenceOrder(const string& newSequence)
{
    vector<string>  tokens  = ofSplitString(newSequence, ",", true, true);
    vector<int>     itokens;
    
    for (int i = 0; i < tokens.size(); i++) {
        itokens.push_back(ofToInt(tokens[i]));
    }
    
    setMovieSequenceOrder(itokens);
}

//------------------------------------------------------------------------------------------
//      PRIVATE METHODS
//------------------------------------------------------------------------------------------

void loopier::Clip::updateSequence()
{
    // Just change movie when movieis done
    if (!movie->getIsMovieDone())   return;
    
    // make sure the sequence index is in bounds
    sequenceIndex = (sequenceIndex + 1) % sequenceOrder.size();
    // make sure the movie index is in bounds
    int movieIndex = sequenceOrder[sequenceIndex] % movies.size();
    
    setMovie(movieIndex);
    movie->setLoopState(OF_LOOP_NONE);
    
    ofLogWarning() << "!!! TODO:\t\t" << __PRETTY_FUNCTION__ << ": \t" << sequenceIndex << ": \t" << movieIndex;
    
    
}
