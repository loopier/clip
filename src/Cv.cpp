//
//  Cv.cpp
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "Cv.h"

//namespace {
//    // Helper functions local to this file (unnamed namespace):
//    
//    // unique instance of Cv tlocal to this file
//    loopier::cv::Cv cvInstance;
//}
//
//loopier::cv::Cv::Cv()
//: minArea(10)
//, maxArea(200)
//, threshold(128)
//, holes(false)
//, visible(true)
//{
//    ofAddListener(ofEvents().update, this, & loopier::cv::Cv::update);
//    ofAddListener(ofEvents().draw, this, & loopier::cv::Cv::draw);
//}
//
//loopier::cv::Cv::~Cv()
//{
//    
//}
//
////---------------------------------------------------------
//void loopier::cv::Cv::setup(){
//    
////    maskFbo.allocate(cam.getWidth(), cam.getHeight());
//}
//
////---------------------------------------------------------
//void loopier::cv::Cv::update(){
//    if (!visible)   return;
//    
//    contourFinder.setMinAreaRadius(minArea);
//    contourFinder.setMaxAreaRadius(maxArea);
//    contourFinder.setThreshold(threshold);
//    contourFinder.findContours(image);
//    contourFinder.setFindHoles(holes);
//    
//    
//    vector<ofPolyline> polys = contourFinder.getPolylines();
//    ofSetColor(255, 255, 255);
//    ofFill();
//    maskFbo.begin();
//    ofBackground(0);
//    for (int i = 0; i < polys.size(); i++) {
//        ofPolyline poly = polys.at(i);
//        ofBeginShape();
//        for( int i = 0; i < poly.getVertices().size(); i++) {
//            ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
//        }
//        ofEndShape();
//    }
//    maskFbo.end();
//    //        cam.getTexture().setAlphaMask(maskFbo.getTexture());
//    
//}
//
//void loopier::cv::Cv::update(ofEventArgs& e)
//{
//    update();
//}
//
////---------------------------------------------------------
//void loopier::cv::Cv::draw(){
//    if (!visible)   return;
//    
//    contourFinder.draw();
//    //    maskFbo.draw(0,0);
//    //    gui.draw();
//}
//
//void loopier::cv::Cv::draw(ofEventArgs& e)
//{
//    draw();
//}
//
////---------------------------------------------------------
//void loopier::cv::Cv::exit(){
//    
//}
//
//void loopier::cv::Cv::setMinArea(float newArea)
//{
//    minArea = newArea;
//}
//
//void loopier::cv::Cv::setMaxArea(float newArea)
//{
//    maxArea = newArea;
//}
//
//void loopier::cv::Cv::setThreshold(float newThreshold)
//{
//    threshold = newThreshold;
//}
//
//void loopier::cv::Cv::setHoles(bool bHoles)
//{
//    holes = bHoles;
//}
//
//void loopier::cv::Cv::toggleVisibility()
//{
//    visible = !visible;
//}
//
//void loopier::cv::Cv::show()
//{
//    visible = true;
//}
//
//void loopier::cv::Cv::hide()
//{
//    visible = false;
//}
//
//void loopier::cv::Cv::setImage(ofImage & img)
//{
//    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs to be implemented";
//}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace {
    // unique instance of Cv tlocal to this file
    ofxCv::ContourFinder contourFinder;
}

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