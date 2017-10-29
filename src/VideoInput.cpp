//
//  VideoInput.cpp
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "VideoInput.h"

using namespace ofxCv;
using namespace cv;

loopier::VideoInput::VideoInput()
: minArea(10)
, maxArea(200)
, threshold(128)
, holes(false)
, visible(true)
{
    
}

loopier::VideoInput::~VideoInput()
{
    
}

//---------------------------------------------------------
void loopier::VideoInput::setup(){
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
void loopier::VideoInput::update(){
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
void loopier::VideoInput::draw(){
    if (!visible)   return;
    
    cam.draw(0,0);
    contourFinder.draw();
//    maskFbo.draw(0,0);
//    gui.draw();
}

//---------------------------------------------------------
void loopier::VideoInput::exit(){
    
}

void loopier::VideoInput::setMinArea(float newArea)
{
    minArea = newArea;
}

void loopier::VideoInput::setMaxArea(float newArea)
{
    maxArea = newArea;
}

void loopier::VideoInput::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

void loopier::VideoInput::setHoles(bool bHoles)
{
    holes = bHoles;
}

void loopier::VideoInput::toggleVisibility()
{
    visible = !visible;
}

void loopier::VideoInput::show()
{
    visible = true;
}

void loopier::VideoInput::hide()
{
    visible = false;
}


//      END OF CLASS METHODS
//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
//      PUBLIC INTERFACE FUNCTIONS


// Global VideoInput
loopier::VideoInput loopier::videoInput;

void loopier::newVideoInput() {
    videoInput.setup();
}

void loopier::updateVideoInput() {
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