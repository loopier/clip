//
//  CvPlayer.cpp
//  clip
//
//  Created by roger on 30/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CvPlayer.h"
#include "Clip.h"

loopier::CvPlayer::CvPlayer()
: bVisible(true)
, bDrawContours(true)
, threshold(200)
, minArea(10.0)
, maxArea(200)
, bHoles(true)
, maxBlobs(2)
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
    
    outputImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    shapeFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    detectionAreaFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    maskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    shapeFbo.begin();
    ofClear(0);
    shapeFbo.end();
    
    detectionAreaFbo.begin();
    ofClear(0);
    detectionAreaFbo.end();
    
    maskFbo.begin();
    ofClear(255,255,255,0);
    maskFbo.end();
    
    contourFinder.setSimplify(true);
    contourFinder.setSortBySize(true); // TODO: Set max blobs
    
    ofRectangle rect(0,0, ofGetWidth(), ofGetHeight());
    setDetectionArea(rect);
}

//---------------------------------------------------------
void loopier::CvPlayer::update()
{
    if (!inputPlayer)   return;
    
    pixels = inputPlayer->getPixels();
    
    // TODO: draw contourFinder.minAreaRect like in https://github.com/kylemcdonald/ofxCv/blob/master/example-contours-advanced/src/ofApp.cpp
    contourFinder.setMinAreaRadius(minArea);
    contourFinder.setMaxAreaRadius(maxArea);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(pixels);
    contourFinder.setFindHoles(bHoles);
    
    drawBlobs();
}

//---------------------------------------------------------
void loopier::CvPlayer::draw(float x, float y, float w, float h)
{
    if (!bVisible)   return;
}

//---------------------------------------------------------
void loopier::CvPlayer::draw()
{
//    maskFbo.draw(0,0);
//    contourFinder.draw();
//    if (inputPlayer) inputPlayer->draw();
//    ofSetColor(255,0,0);
//    detectionAreaFbo.draw(0,0);
    shapeFbo.draw(0,0, pixels.getWidth(), pixels.getHeight());
    ofDrawCircle(getCentroid().x, getCentroid().y, 20);
}

//
void loopier::CvPlayer::drawBlobs()
{
    // Create a mask with the blobs
    vector<ofPolyline> polys = contourFinder.getPolylines();
    shapeFbo.begin();
    ofClear(255,255,255,0);
    ofNoFill();
    ofSetColor(255);
    for (int i = 0; i < maxBlobs && i < polys.size(); i++) {
        ofPolyline poly = polys.at(i);
        ofBeginShape();
        for( int i = 0; i < poly.getVertices().size(); i++) {
            ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
        }
        ofEndShape();
        
        ofDrawRectangle(contourFinder.getBoundingRect(i).x,
                        contourFinder.getBoundingRect(i).y,
                        contourFinder.getBoundingRect(i).width,
                        contourFinder.getBoundingRect(i).height);
    }
    shapeFbo.end();
    
    shapeFbo.getTexture().setAlphaMask(detectionAreaFbo.getTexture());
}

//---------------------------------------------------------
void loopier::CvPlayer::exit(){

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
ofTexture & loopier::CvPlayer::getTexture()
{
    // Create a mask with the blobs
    vector<ofPolyline> polys = contourFinder.getPolylines();
    shapeFbo.begin();
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
    shapeFbo.end();
    
    shapeFbo.getTexture().setAlphaMask(detectionAreaFbo.getTexture());
    
    maskFbo.begin();
    ofClear(255,255,255,0);
    shapeFbo.draw(0,0);
    maskFbo.end();
    return maskFbo.getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::CvPlayer::getPixels()
{
    maskFbo.readToPixels(pixels);
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

//---------------------------------------------------------
ofPoint loopier::CvPlayer::getCentroid()
{
    if(contourFinder.getPolylines().size() < 1) return;
    ofPoint centroid(contourFinder.getCenter(0).x, contourFinder.getCenter(0).y);
    return centroid;
}

////---------------------------------------------------------
void loopier::CvPlayer::setInputPlayer(PlayerPtr aPlayer)
{
    BasePlayer::setInputPlayer(aPlayer);
//    setWidth(aPlayer->getWidth());
//    setHeight(aPlayer->getHeight());
//    shapeFbo.allocate(getWidth(), getHeight(), GL_RGBA);
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
void loopier::CvPlayer::setMaxBlobs(int numBlobs)
{
    maxBlobs = numBlobs;
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