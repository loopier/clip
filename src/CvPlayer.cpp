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
    loopier::cv::CvPlayerPtr cvplayer;
    // other instances local to this file
    ofxCv::ContourFinder contourFinder;
}

loopier::cv::CvPlayer::CvPlayer()
: bVisible(true)
, bDrawContours(true)
{
    inputImage = make_shared<ofImage>();
    outputImage = make_shared<ofImage>();
    inputImage->allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    outputImage->allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    maskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
}

loopier::cv::CvPlayer::~CvPlayer()
{

}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setup(){

    //    maskFbo.allocate(cam.getWidth(), cam.getHeight());
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::update(){
    if (!bVisible)       return;
    if (!inputPlayer)   return;
    
    // TODO: draw contourFinder.minAreaRect like in https://github.com/kylemcdonald/ofxCv/blob/master/example-contours-advanced/src/ofApp.cpp
    inputImage->setFromPixels(inputPlayer->getPixels());
    contourFinder.findContours(*inputImage);

    //    contourFinder.setFindHoles(holes);

    // Create a mask with the blobs    
    vector<ofPolyline> polys = contourFinder.getPolylines();
    maskFbo.begin();
    ofClear(255,255,255,0);
    ofSetColor(255, 255, 255);
    for (int i = 0; i < polys.size(); i++) {
        ofPolyline poly = polys.at(i);
        ofBeginShape();
        for( int i = 0; i < poly.getVertices().size(); i++) {
            ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
        }
        ofEndShape();
    }
    maskFbo.end();
    
    ofPixels pixels;
    maskFbo.readToPixels(pixels);
    outputImage->setFromPixels(pixels);
    
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::draw(float x, float y, float w, float h)
{
    if (!bVisible)   return;
    outputImage->draw(x, y, w, h);
    if (bDrawContours)  contourFinder.draw();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::draw()
{
    draw(anchor.x, anchor.y, getWidth(), getHeight());
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::exit(){

}

//---------------------------------------------------------
float loopier::cv::CvPlayer::getWidth() const
{
    return outputImage->getWidth();
}

//---------------------------------------------------------
float loopier::cv::CvPlayer::getHeight() const
{
    return outputImage->getHeight();
}

//---------------------------------------------------------
bool loopier::cv::CvPlayer::loadResource(string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
ofTexture & loopier::cv::CvPlayer::getTexture() const
{
    return outputImage->getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::cv::CvPlayer::getPixels() const
{
    return outputImage->getPixels();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setInputPlayer(PlayerPtr player)
{
    inputPlayer = player;
    outputImage->setFromPixels(player->getPixels());
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::toggleVisibility()
{
    bVisible = !bVisible;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::show()
{
    bVisible = true;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::hide()
{
    bVisible = false;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------
void loopier::cv::setup()
{
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(200);
    contourFinder.setThreshold(128);
    contourFinder.setFindHoles(true);
    // create an instance of a player local to this file, to be used by other global functions of this file
    cvplayer = make_shared<CvPlayer>();
    cvplayer->setup();
    // create a new clip to hold the cv player
    ClipPtr clip = loopier::newClip("cv");
    clip->setPlayer(cvplayer);
    // create a camera clip to pass it as input to Cv
    ClipPtr cameraclip = loopier::newClip(loopier::cameras.begin()->first, loopier::cameras.begin()->first);
    loopier::cv::setInputClip(loopier::cameras.begin()->first);
}

//---------------------------------------------------------
void loopier::cv::setInputClip(string clipname)
{
    if (!loopier::clipExists(clipname)) return;
    ClipPtr clip = loopier::getClipByName(clipname);
    cvplayer->setInputPlayer( clip->getPlayer() );
    clip->hide();
    
}


//---------------------------------------------------------
void loopier::cv::setMinArea(float newArea)
{
    contourFinder.setMinAreaRadius(newArea);
}

//---------------------------------------------------------
void loopier::cv::setMaxArea(float newArea)
{
    contourFinder.setMaxAreaRadius(newArea);
}

//---------------------------------------------------------
void loopier::cv::setThreshold(float newThreshold)
{
    contourFinder.setThreshold(newThreshold);
}

//---------------------------------------------------------
void loopier::cv::setHoles(bool bHoles)
{
    contourFinder.setFindHoles(bHoles);
}
