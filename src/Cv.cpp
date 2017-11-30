//
//  Cv.cpp
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "Cv.h"

loopier::Cv::Cv()
: minArea(10)
, maxArea(200)
, threshold(128)
, holes(false)
, visible(true)
{
    
}

loopier::Cv::~Cv()
{
    
}

//---------------------------------------------------------
void loopier::Cv::setup(){
    cam.listDevices();
    cam.setDeviceID(1);
    cam.setup(ofGetWidth(), ofGetHeight());
    
    maskFbo.allocate(cam.getWidth(), cam.getHeight());
    
//    gui.setup();
//    gui.add(minArea.set("Min area", 10, 1, 100));
//    gui.add(maxArea.set("Max area", 200, 1, 500));
//    gui.add(threshold.set("Threshold", 128, 0, 255));
//    gui.add(holes.set("Holes", false));
}

//---------------------------------------------------------
void loopier::Cv::update(){
    if (!visible)   return;
    
    cam.update();
    
    if(cam.isFrameNew()) {
        contourFinder.setMinAreaRadius(minArea);
        contourFinder.setMaxAreaRadius(maxArea);
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(cam);
        contourFinder.setFindHoles(holes);
        
        
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
        cam.getTexture().setAlphaMask(maskFbo.getTexture());
    }
}

//---------------------------------------------------------
void loopier::Cv::draw(){
    if (!visible)   return;
    
    cam.draw(0,0);
    contourFinder.draw();
//    maskFbo.draw(0,0);
//    gui.draw();
}

//---------------------------------------------------------
void loopier::Cv::exit(){
    
}

void loopier::Cv::setMinArea(float newArea)
{
    minArea = newArea;
}

void loopier::Cv::setMaxArea(float newArea)
{
    maxArea = newArea;
}

void loopier::Cv::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

void loopier::Cv::setHoles(bool bHoles)
{
    holes = bHoles;
}

void loopier::Cv::toggleVisibility()
{
    visible = !visible;
}

void loopier::Cv::show()
{
    visible = true;
}

void loopier::Cv::hide()
{
    visible = false;
}




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void loopier::updateCv() {
    videoInput.update();
}

void loopier::drawVideoInput() {
    videoInput.draw();
}

void loopier::setVideoInputMinArea(float newArea)
{
    videoInput.setMinArea(newArea);
}

void loopier::setVideoInputMaxArea(float newArea)
{
    videoInput.setMaxArea(newArea);
}

void loopier::setVideoInputThreshold(float newThreshold)
{
    videoInput.setThreshold(newThreshold);
}

void loopier::setVideoInputHoles(bool bHoles)
{
    videoInput.setHoles(bHoles);
}

void loopier::toggleVideoInputVisibility()
{
    videoInput.toggleVisibility();
}

void loopier::showVideoInput()
{
    videoInput.show();
}

void loopier::hideVideoInput()
{
    videoInput.hide();
}