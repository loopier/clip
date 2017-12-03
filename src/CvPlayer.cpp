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
//    ofxCv::ContourFinder contourFinder;
}

loopier::cv::CvPlayer::CvPlayer()
: bVisible(true)
, bDrawContours(true)
, threshold(200)
, minArea(10.0)
, maxArea(200)
, bHoles(true)
{
    
}

loopier::cv::CvPlayer::~CvPlayer()
{

}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setup()
{
    outputImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    maskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    outputImage.load("mama.png");
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::update(){
//    if (!bVisible)       return;
//    if (!inputPlayer)   return;
    
    // TODO: draw contourFinder.minAreaRect like in https://github.com/kylemcdonald/ofxCv/blob/master/example-contours-advanced/src/ofApp.cpp
    
    contourFinder.setMinAreaRadius(minArea);
    contourFinder.setMaxAreaRadius(maxArea);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(inputPlayer->getPixels());
    contourFinder.setFindHoles(bHoles);

    outputImage.setFromPixels(inputPlayer->getPixels());

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
void loopier::cv::CvPlayer::draw(float x, float y, float w, float h)
{
    if (!bVisible)   return;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::draw()
{
    outputImage.draw(0,0);
    contourFinder.draw();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::exit(){

}

//---------------------------------------------------------
float loopier::cv::CvPlayer::getWidth() const
{
    return outputImage.getWidth();
}

//---------------------------------------------------------
float loopier::cv::CvPlayer::getHeight() const
{
    return outputImage.getHeight();
}

//---------------------------------------------------------
bool loopier::cv::CvPlayer::loadResource(string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
ofTexture & loopier::cv::CvPlayer::getTexture()
{
    return outputImage.getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::cv::CvPlayer::getPixels()
{
    return outputImage.getPixels();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setInputPlayer(PlayerPtr player)
{
    inputPlayer = player;
//    outputImage.setFromPixels(player->getPixels());
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

//---------------------------------------------------------
void loopier::cv::CvPlayer::setMinArea(float newArea)
{
    minArea = newArea;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setMaxArea(float newArea)
{
    maxArea = newArea;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setFindHoles(bool findHoles)
{
    bHoles = findHoles;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------
void loopier::cv::setup()
{
    // create an instance of a player local to this file, to be used by other global functions of this file
//    cvplayer = make_shared<CvPlayer>();
//    cvplayer->setup();
//    // create a new clip to hold the cv player
//    ClipPtr clip = loopier::newClip("cv");
//    clip->setPlayer(cvplayer);
//    // create a camera clip to pass it as input to Cv
//    ClipPtr cameraclip = loopier::newClip(loopier::cameras.begin()->first, loopier::cameras.begin()->first);
//    loopier::cv::setInputClip(loopier::cameras.begin()->first);
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
    cvplayer->setMinArea(newArea);
}

//---------------------------------------------------------
void loopier::cv::setMaxArea(float newArea)
{
    cvplayer->setMaxArea(newArea);
}

//---------------------------------------------------------
void loopier::cv::setThreshold(float newThreshold)
{
    cvplayer->setThreshold(newThreshold);
}

//---------------------------------------------------------
void loopier::cv::setFindHoles(bool findHoles)
{
    cvplayer->setFindHoles(findHoles);
}
