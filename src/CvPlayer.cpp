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
, bMask(true)
, bDrawContours(true)
{
    ofAddListener(ofEvents().update, this, & loopier::cv::CvPlayer::update);
    ofAddListener(ofEvents().draw, this, & loopier::cv::CvPlayer::draw);
    
    inputImage = make_shared<ofImage>();
    outputImage = make_shared<ofImage>();
    renderImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    maskFbo.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
}

loopier::cv::CvPlayer::~CvPlayer()
{

}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setup(){

    //    maskFbo.allocate(cam.getWidth(), cam.getHeight());
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::update(ofEventArgs& e)
{
    update();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::update(){
    if (!bVisible)       return;
    if (!inputPlayer)   return;

    // contourFinder is defined in a (unnamed)namespace in this file to use it locally
    //    contourFinder.setMinAreaRadius(minArea);
    //    contourFinder.setMaxAreaRadius(maxArea);
    //    contourFinder.setThreshold(threshold);

    
    // TODO: draw contourFinder.minAreaRect like in https://github.com/kylemcdonald/ofxCv/blob/master/example-contours-advanced/src/ofApp.cpp
    inputImage->setFromPixels(inputPlayer->getPixels());
    contourFinder.findContours(*inputImage);

    //    contourFinder.setFindHoles(holes);

    // Create a mask with the blobs    
    vector<ofPolyline> polys = contourFinder.getPolylines();
//    blobPath.clear();
//    for (int i = 0; i < polys.size(); i++) {
//        ofPolyline poly = polys.at(i);
//        blobPath.newSubPath();
//        blobPath.moveTo(poly.getVertices()[0].x, poly.getVertices()[0].y);
//        for( int i = 0; i < poly.getVertices().size(); i++) {
//            blobPath.lineTo(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
//        }
//    }
//    blobPath.close();
//    blobPath.simplify();
//    
//    maskFbo.begin();
//    ofFill();
//    ofSetColor(255);
//    blobPath.draw();
//    maskFbo.end();
    
    ofSetColor(255, 255, 255);
    ofFill();
    maskFbo.begin();
    ofBackground(0);
    for (int i = 0; i < polys.size(); i++) {
        ofPolyline poly = polys.at(i);
        ofBeginShape();
        for( int i = 0; i < poly.getVertices().size(); i++) {
            ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
        }
        ofEndShape();
    }
    maskFbo.end();
    
    renderImage.setFromPixels(inputImage->getPixels());
    renderImage.getTexture().setAlphaMask(maskFbo.getTexture());
    //        cam.getTexture().setAlphaMask(maskFbo.getTexture());
    
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::draw(ofEventArgs& e)
{
    draw();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::draw(float x, float y, float w, float h)
{
    if (!bVisible)   return;
    
    renderImage.draw(x,y, w,h);
    maskFbo.draw(x,y,w,h);
    if (bDrawContours)  contourFinder.draw();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::draw(){
    //    maskFbo.draw(0,0);
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
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    return outputImage->getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::cv::CvPlayer::getPixels() const
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    return outputImage->getPixels();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setInputPlayer(PlayerPtr player)
{
    inputPlayer = player;
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
void loopier::cv::CvPlayer::toggleMask()
{
    bMask = !bMask;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::maskOn()
{
    bMask = true;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::maskOff()
{
    bMask = false;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::mask(bool onoff)
{
    bMask = onoff;
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
    cvplayer = make_shared<CvPlayer>();
    cvplayer->setup();
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
void loopier::cv::update()
{
    cvplayer->update();
}

//---------------------------------------------------------
void loopier::cv::draw()
{
    cvplayer->draw();
}

//---------------------------------------------------------
void loopier::cv::toggleMask()
{
    cvplayer->toggleMask();
}

//---------------------------------------------------------
void loopier::cv::maskOn()
{
    cvplayer->maskOn();
}

//---------------------------------------------------------
void loopier::cv::maskOff()
{
    cvplayer->maskOff();
}

//---------------------------------------------------------
void loopier::cv::mask(bool onoff)
{
    cvplayer->mask(onoff);
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
