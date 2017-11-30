//
//  CvPlayer.cpp
//  clip
//
//  Created by roger on 30/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CvPlayer.h"

namespace {
    // unique instance of Cv tlocal to this file
    ofxCv::ContourFinder contourFinder;
}

loopier::cv::CvPlayer::CvPlayer()
: minArea(10)
, maxArea(200)
, threshold(128)
, holes(false)
, visible(true)
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
    contourFinder.findContours(sourceImage);
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
void loopier::cv::CvPlayer::draw(float x, float y, float w, float h){
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

void loopier::cv::CvPlayer::setMinArea(float newArea)
{
    minArea = newArea;
}

void loopier::cv::CvPlayer::setMaxArea(float newArea)
{
    maxArea = newArea;
}

void loopier::cv::CvPlayer::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

void loopier::cv::CvPlayer::setHoles(bool bHoles)
{
    holes = bHoles;
}

void loopier::cv::CvPlayer::toggleVisibility()
{
    visible = !visible;
}

void loopier::cv::CvPlayer::show()
{
    visible = true;
}

void loopier::cv::CvPlayer::hide()
{
    visible = false;
}

void loopier::cv::CvPlayer::setImage(ofImage & img)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs to be implemented";
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *



void loopier::cv::setMinArea(float newArea)
{
    contourFinder.setMinAreaRadius(newArea);
}

void loopier::cv::setMaxArea(float newArea)
{
    contourFinder.setMaxAreaRadius(newArea);
}

void loopier::cv::setThreshold(float newThreshold)
{
    contourFinder.setThreshold(newThreshold);
}

void loopier::cv::setHoles(bool bHoles)
{
    contourFinder.setFindHoles(bHoles);
}
