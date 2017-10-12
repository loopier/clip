//
//  Recorder.cpp
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "Recorder.h"

using namespace ofxCv;
using namespace cv;

loopier::Recorder::Recorder()
: minArea(10)
, maxArea(200)
, threshold(128)
, holes(false)
, visible(true)
{
    
}

loopier::Recorder::~Recorder()
{
    
}

//---------------------------------------------------------
void loopier::Recorder::setup(){
    cam.listDevices();
    cam.setDeviceID(1);
    cam.setup(ofGetWidth(), ofGetHeight());
    
//    gui.setup();
//    gui.add(minArea.set("Min area", 10, 1, 100));
//    gui.add(maxArea.set("Max area", 200, 1, 500));
//    gui.add(threshold.set("Threshold", 128, 0, 255));
//    gui.add(holes.set("Holes", false));
}

//---------------------------------------------------------
void loopier::Recorder::update(){
    if (!visible)   return;
    
    cam.update();
    
    if(cam.isFrameNew()) {
        contourFinder.setMinAreaRadius(minArea);
        contourFinder.setMaxAreaRadius(maxArea);
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(cam);
        contourFinder.setFindHoles(holes);
    }
}

//---------------------------------------------------------
void loopier::Recorder::draw(){
    if (!visible)   return;
    
    cam.draw(0,0);
    contourFinder.draw();
//    gui.draw();
}

//---------------------------------------------------------
void loopier::Recorder::exit(){
    
}

void loopier::Recorder::setMinArea(float newArea)
{
    minArea = newArea;
}

void loopier::Recorder::setMaxArea(float newArea)
{
    maxArea = newArea;
}

void loopier::Recorder::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

void loopier::Recorder::setHoles(bool bHoles)
{
    holes = bHoles;
}

void loopier::Recorder::toggleVisibility()
{
    visible = !visible;
}

void loopier::Recorder::show()
{
    visible = true;
}

void loopier::Recorder::hide()
{
    visible = false;
}

//      END OF CLASS METHODS
//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
//      PUBLIC INTERFACE FUNCTIONS


// Global recorder
loopier::Recorder loopier::recorder;

void loopier::newRecorder() {
    recorder.setup();
}

void loopier::updateRecorder() {
    recorder.update();
}

void loopier::drawRecorder() {
    recorder.draw();
}

void loopier::setRecorderMinArea(float newArea)
{
    recorder.setMinArea(newArea);
}

void loopier::setRecorderMaxArea(float newArea)
{
    recorder.setMaxArea(newArea);
}

void loopier::setRecorderThreshold(float newThreshold)
{
    recorder.setThreshold(newThreshold);
}

void loopier::setRecorderHoles(bool bHoles)
{
    recorder.setHoles(bHoles);
}

void loopier::toggleRecorderVisibility()
{
    recorder.toggleVisibility();
}

void loopier::showRecorder()
{
    recorder.show();
}

void loopier::hideRecorder()
{
    recorder.hide();
}