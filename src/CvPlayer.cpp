//
//  CvPlayer.cpp
//  clip
//
//  Created by roger on 30/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CvPlayer.h"
#include "Clip.h"

namespace {
    // unique instance of CV
    loopier::CvPlayerPtr cvplayer;
    // other instances local to this file
//    ofxCv::ContourFinder contourFinder;
}

loopier::CvPlayer::CvPlayer()
: bVisible(true)
, bDrawContours(true)
, threshold(200)
, minArea(10.0)
, maxArea(200)
, bHoles(true)
{
    setup();
}

loopier::CvPlayer::CvPlayer(PlayerPtr input)
: inputPlayer(input)
, bVisible(true)
, bDrawContours(true)
, threshold(200)
, minArea(10.0)
, maxArea(200)
, bHoles(true)
{
    inputPlayer = input;
    setup();
}

loopier::CvPlayer::~CvPlayer()
{

}

//---------------------------------------------------------
void loopier::CvPlayer::setup()
{
    setDeviceId(0);
    
    outputImage.allocate(camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR_ALPHA);
    maskFbo.allocate(camera.getWidth(), camera.getHeight(), GL_RGBA);
}

//---------------------------------------------------------
void loopier::CvPlayer::update(){
//    if (!bVisible)       return;
//    if (!inputPlayer)   return;
    camera.update();
    if (!camera.isFrameNew()) return;
    
    ofLogVerbose() << __PRETTY_FUNCTION__;
    
    // TODO: draw contourFinder.minAreaRect like in https://github.com/kylemcdonald/ofxCv/blob/master/example-contours-advanced/src/ofApp.cpp
    
    contourFinder.setMinAreaRadius(minArea);
    contourFinder.setMaxAreaRadius(maxArea);
    contourFinder.setThreshold(threshold);
//    contourFinder.findContours(inputPlayer->getPixels());
    contourFinder.findContours(camera.getPixels());
    contourFinder.setFindHoles(bHoles);

    //    outputImage.setFromPixels(inputPlayer->getPixels());
    outputImage.setFromPixels(camera.getPixels());

    // Create a mask with the blobs
    vector<ofPolyline> polys = contourFinder.getPolylines();
    maskFbo.begin();
    ofClear(255,255,255,0);
    ofFill();
    ofSetColor(255);
    for (int i = 0; i < polys.size(); i++) {
        ofPolyline poly = polys.at(i);
        ofBeginShape();
        for( int i = 0; i < poly.getVertices().size(); i++) {
            ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
        }
        ofEndShape();
    }
    maskFbo.end();
    
    outputImage.getTexture().setAlphaMask(maskFbo.getTexture());
}

//---------------------------------------------------------
void loopier::CvPlayer::draw(float x, float y, float w, float h)
{
    if (!bVisible)   return;
}

//---------------------------------------------------------
void loopier::CvPlayer::draw()
{
//    outputImage.draw(0,0);
//    maskFbo.draw(0,0);
//    inputPlayer->draw();
    ofSetColor(255);
    ofDrawRectangle(100,100,200,200);
    camera.draw(0,0);
    contourFinder.draw();
}

//---------------------------------------------------------
void loopier::CvPlayer::exit(){

}

//---------------------------------------------------------
void loopier::CvPlayer::setDeviceId(int n)
{
    // reset camera
//    camera.close();
    camera.setDeviceID(n);
    camera.setDesiredFrameRate(60);
    camera.initGrabber(ofGetWidth(), ofGetHeight());
}

//---------------------------------------------------------
float loopier::CvPlayer::getWidth() const
{
    return outputImage.getWidth();
}

//---------------------------------------------------------
float loopier::CvPlayer::getHeight() const
{
    return outputImage.getHeight();
}

//---------------------------------------------------------
bool loopier::CvPlayer::loadResource(string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
ofTexture & loopier::CvPlayer::getTexture()
{
    return outputImage.getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::CvPlayer::getPixels()
{
    return outputImage.getPixels();
}

//---------------------------------------------------------
void loopier::CvPlayer::setInputPlayer(PlayerPtr player)
{
    inputPlayer = player;
//    outputImage.setFromPixels(player->getPixels());
}

//---------------------------------------------------------
void loopier::CvPlayer::toggleVisibility()
{
    bVisible = !bVisible;
}

//---------------------------------------------------------
void loopier::CvPlayer::show()
{
    bVisible = true;
}

//---------------------------------------------------------
void loopier::CvPlayer::hide()
{
    bVisible = false;
}

//---------------------------------------------------------
void loopier::CvPlayer::setMinArea(float newArea)
{
    minArea = newArea;
}

//---------------------------------------------------------
void loopier::CvPlayer::setMaxArea(float newArea)
{
    maxArea = newArea;
}

//---------------------------------------------------------
void loopier::CvPlayer::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

//---------------------------------------------------------
void loopier::CvPlayer::setFindHoles(bool findHoles)
{
    bHoles = findHoles;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------
void loopier::setup()
{
    // create an instance of a player local to this file, to be used by other global functions of this file
//    cvplayer = make_shared<CvPlayer>();
//    cvplayer->setup();
//    // create a new clip to hold the cv player
//    ClipPtr clip = loopier::newClip("cv");
//    clip->setPlayer(cvplayer);
//    // create a camera clip to pass it as input to Cv
//    ClipPtr cameraclip = loopier::newClip(loopier::cameras.begin()->first, loopier::cameras.begin()->first);
//    loopier::setInputClip(loopier::cameras.begin()->first);
}

//---------------------------------------------------------
void loopier::setInputClip(string clipname)
{
//    if (!loopier::clipExists(clipname)) return;
//    ClipPtr clip = loopier::getClipByName(clipname);
//    cvplayer->setInputPlayer( clip->getPlayer() );
//    clip->hide();
    
}


//---------------------------------------------------------
void loopier::setMinArea(float newArea)
{
    cvplayer->setMinArea(newArea);
}

//---------------------------------------------------------
void loopier::setMaxArea(float newArea)
{
    cvplayer->setMaxArea(newArea);
}

//---------------------------------------------------------
void loopier::setThreshold(float newThreshold)
{
    cvplayer->setThreshold(newThreshold);
}

//---------------------------------------------------------
void loopier::setFindHoles(bool findHoles)
{
    cvplayer->setFindHoles(findHoles);
}
