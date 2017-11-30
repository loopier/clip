//
//  CvPlayer.cpp
//  clip
//
//  Created by roger on 30/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CvPlayer.h"

namespace {
    // other instances local to this file
    ofxCv::ContourFinder contourFinder;
}

loopier::cv::CvPlayer::CvPlayer()
: visible(true)
{
    ofAddListener(ofEvents().update, this, & loopier::cv::CvPlayer::update);
    ofAddListener(ofEvents().draw, this, & loopier::cv::CvPlayer::draw);

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
    if (!visible)   return;
    
    // contourFinder is defined in a (unnamed)namespace in this file to use it locally
    //    contourFinder.setMinAreaRadius(minArea);
    //    contourFinder.setMaxAreaRadius(maxArea);
    //    contourFinder.setThreshold(threshold);
    
    // TODO: draw contourFinder.minAreaRect like in https://github.com/kylemcdonald/ofxCv/blob/master/example-contours-advanced/src/ofApp.cpp
    if (!sourceCamera->isFrameNew()) return;
    contourFinder.findContours(*sourceCamera); // object pointed by CameraPtr = Camera = ofVideoGrabber
    
    
    //    contourFinder.setFindHoles(holes);
    
    
    vector<ofPolyline> polys = contourFinder.getPolylines();
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
    draw();
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::draw(){
    if (!visible)   return;
    
    contourFinder.draw();
    //    maskFbo.draw(0,0);
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::exit(){
    
}

//---------------------------------------------------------
bool loopier::cv::CvPlayer::loadResource(string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::setSourceCamera(CameraPtr srcCam)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs to be implemented";
    sourceCamera = srcCam;
    cam = *srcCam;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::toggleVisibility()
{
    visible = !visible;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::show()
{
    visible = true;
}

//---------------------------------------------------------
void loopier::cv::CvPlayer::hide()
{
    visible = false;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace {
    loopier::cv::CvPlayerPtr cvplayer;
}

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
void loopier::cv::setSourceCamera(string resourcename)
{
    cvplayer->setSourceCamera(loopier::getCameraByName(resourcename));
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
