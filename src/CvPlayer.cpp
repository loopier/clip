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
    loopier::CvPlayerPtr cvplayer;
    // other instances local to this file
//    ofxCv::ContourFinder contourFinder;
}

loopier::CvPlayer::CvPlayer()
: bVisible(true)
, bDrawContours(true)
, threshold(200)
, minArea(10.0)
, maxArea(200)
, bHoles(true)
{
    setup();
}

loopier::CvPlayer::CvPlayer(PlayerPtr input)
: bVisible(true)
, bDrawContours(true)
, threshold(200)
, minArea(10.0)
, maxArea(200)
, bHoles(true)
{
//    inputPlayer = input;
    setup();
}

loopier::CvPlayer::~CvPlayer()
{

}

//---------------------------------------------------------
void loopier::CvPlayer::setup()
{
    setDeviceId(0);
    
    outputImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    maskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    detectionAreaFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    maskFbo.begin();
    ofClear(255,255,255,0);
    maskFbo.end();
    
    detectionAreaFbo.begin();
    ofClear(0);
    detectionAreaFbo.end();
    
    contourFinder.setSimplify(true);
//    contourFinder.setInvert(true);
    
    ofRectangle rect(0,0, ofGetWidth(), ofGetHeight());
    setDetectionArea(rect);
}

//---------------------------------------------------------
void loopier::CvPlayer::update(){
//    if (!bVisible)       return;
    if (!inputPlayer)   return;
//    camera.update();
//    if (!camera.isFrameNew()) return;
    
//    ofLogVerbose() << __PRETTY_FUNCTION__;
    
    // TODO: draw contourFinder.minAreaRect like in https://github.com/kylemcdonald/ofxCv/blob/master/example-contours-advanced/src/ofApp.cpp
    
    contourFinder.setMinAreaRadius(minArea);
    contourFinder.setMaxAreaRadius(maxArea);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(inputPlayer->getPixels());
//    contourFinder.findContours(outputImage);
    contourFinder.setFindHoles(bHoles);

//        outputImage.setFromPixels(inputPlayer->getPixels());
//    outputImage.setFromPixels(camera.getPixels());

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
            if (poly.getVertices().at(i).x < detectionRectangle.getLeft()   ||
                poly.getVertices().at(i).x > detectionRectangle.getRight()  ||
                poly.getVertices().at(i).y < detectionRectangle.getTop()    ||
                poly.getVertices().at(i).y > detectionRectangle.getBottom() ) {
                continue;
            }
            ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
        }
        ofEndShape();
    }
    maskFbo.end();
    
//    shapeFbo.getTexture().setAlphaMask(detectionAreaFbo.getTexture());
//    maskFbo.readToPixels(pixels);
//    outputImage.setFromPixels(pixels);
//    outputImage.getTexture().setAlphaMask(maskFbo.getTexture());
}

//---------------------------------------------------------
void loopier::CvPlayer::draw(float x, float y, float w, float h)
{
    if (!bVisible)   return;
}

//---------------------------------------------------------
void loopier::CvPlayer::draw()
{
//    outputImage.draw(0,0);
    maskFbo.draw(0,0);
    contourFinder.draw();
//    inputPlayer->draw();
//    camera.draw(0,0);
//    ofSetColor(255,0,0);
//    detectionAreaFbo.draw(0,0);
}

//---------------------------------------------------------
void loopier::CvPlayer::exit(){

}

//---------------------------------------------------------
void loopier::CvPlayer::setDeviceId(int n)
{
    // reset camera
//    camera.close();
//    camera.setDeviceID(1);
//    camera.setDesiredFrameRate(60);
//    camera.initGrabber(ofGetWidth(), ofGetHeight());
}

//---------------------------------------------------------
void loopier::CvPlayer::setCamera(ofVideoGrabber & cam)
{
//    camera = cam;
}

//---------------------------------------------------------
float loopier::CvPlayer::getWidth() const
{
    return outputImage.getWidth();
}

//---------------------------------------------------------
float loopier::CvPlayer::getHeight() const
{
    return outputImage.getHeight();
}

//---------------------------------------------------------
//bool loopier::CvPlayer::loadResource(string resourcename)
//{
//    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//}

//---------------------------------------------------------
ofTexture & loopier::CvPlayer::getTexture()
{
    return maskFbo.getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::CvPlayer::getPixels()
{
    return pixels;
}

//---------------------------------------------------------
ofImage & loopier::CvPlayer::getImage()
{
    return outputImage;
}

//---------------------------------------------------------
vector<ofPolyline> loopier::CvPlayer::getPolylines()
{
    return contourFinder.getPolylines();
}

////---------------------------------------------------------
// MOVED TO BASECLASS
void loopier::CvPlayer::setInputPlayer(PlayerPtr player)
{
    inputPlayer = player;
//    outputImage.setFromPixels(player->getPixels());
}

//---------------------------------------------------------
void loopier::CvPlayer::toggleVisibility()
{
    bVisible = !bVisible;
}

//---------------------------------------------------------
void loopier::CvPlayer::show()
{
    bVisible = true;
}

//---------------------------------------------------------
void loopier::CvPlayer::hide()
{
    bVisible = false;
}

//---------------------------------------------------------
void loopier::CvPlayer::setMinArea(float newArea)
{
    minArea = newArea;
}

//---------------------------------------------------------
void loopier::CvPlayer::setMaxArea(float newArea)
{
    maxArea = newArea;
}

//---------------------------------------------------------
void loopier::CvPlayer::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

//---------------------------------------------------------
void loopier::CvPlayer::setFindHoles(bool findHoles)
{
    bHoles = findHoles;
}

//---------------------------------------------------------
void loopier::CvPlayer::setDetectionArea(const ofRectangle & rect)
{
    detectionAreaFbo.begin();
    ofClear(255,255,255,0);
    ofFill();
    ofSetColor(255);
    ofBeginShape();
    ofVertex(rect.getLeft(), rect.getTop());
    ofVertex(rect.getRight(), rect.getTop());
    ofVertex(rect.getRight(), rect.getBottom());
    ofVertex(rect.getLeft(), rect.getBottom());
    ofEndShape();
    detectionAreaFbo.end();
    
    detectionRectangle = rect;
}