//
//  CvManager.cpp
//  clip
//
//  Created by roger on 30/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CvManager.h"

namespace {
    // unique instance of CV
    loopier::cv::CvManagerPtr cvmanager;
    // other instances local to this file
    ofxCv::ContourFinder contourFinder;
}

loopier::cv::CvManager::CvManager()
: visible(true)
{
    ofAddListener(ofEvents().update, this, & loopier::cv::CvManager::update);
    ofAddListener(ofEvents().draw, this, & loopier::cv::CvManager::draw);

}

loopier::cv::CvManager::~CvManager()
{

}

//---------------------------------------------------------
void loopier::cv::CvManager::setup(){

    //    maskFbo.allocate(cam.getWidth(), cam.getHeight());
}

//---------------------------------------------------------
void loopier::cv::CvManager::update(ofEventArgs& e)
{
    update();
}

//---------------------------------------------------------
void loopier::cv::CvManager::update(){
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
void loopier::cv::CvManager::draw(ofEventArgs& e)
{
    draw();
}

//---------------------------------------------------------
void loopier::cv::CvManager::draw(float x, float y, float w, float h)
{
    draw();
}

//---------------------------------------------------------
void loopier::cv::CvManager::draw(){
    if (!visible)   return;

    contourFinder.draw();
    //    maskFbo.draw(0,0);
}

//---------------------------------------------------------
void loopier::cv::CvManager::exit(){

}

//---------------------------------------------------------
bool loopier::cv::CvManager::loadResource(string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
void loopier::cv::CvManager::setSourceCamera(CameraPtr srcCam)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs to be implemented";
    sourceCamera = srcCam;
    cam = *srcCam;
}

//---------------------------------------------------------
void loopier::cv::CvManager::toggleVisibility()
{
    visible = !visible;
}

//---------------------------------------------------------
void loopier::cv::CvManager::show()
{
    visible = true;
}

//---------------------------------------------------------
void loopier::cv::CvManager::hide()
{
    visible = false;
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
    cvmanager = make_shared<CvManager>();
    cvmanager->setup();
}

//---------------------------------------------------------
void loopier::cv::setSourceCamera(string resourcename)
{
    cvmanager->setSourceCamera(loopier::getCameraByName(resourcename));
}

//---------------------------------------------------------
void loopier::cv::update()
{
    cvmanager->update();
}

//---------------------------------------------------------
void loopier::cv::draw()
{
    cvmanager->draw();
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
