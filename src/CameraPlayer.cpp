//
//  CameraPlayer.cpp
//  clip
//
//  Created by roger on 29/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CameraPlayer.h"

loopier::CameraMap loopier::cameramap;

//---------------------------------------------------------
loopier::CameraPlayer::CameraPlayer()
{
    
}

//---------------------------------------------------------
loopier::CameraPlayer::CameraPlayer(CameraPtr cam)
{
    setCamera(cam);
    width = camera->getWidth();
    height = camera->getHeight();
}

//---------------------------------------------------------
loopier::CameraPlayer::~CameraPlayer()
{
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::setup()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------
void loopier::CameraPlayer::update()
{
    if (!camera)    return;
    camera->update();
    image.setFromPixels(camera->getPixels());
}

//---------------------------------------------------------
void loopier::CameraPlayer::draw()
{
    if (!camera)    return;
    camera->draw(0,0);
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::draw(float x, float y, float w, float h)
{
    if (!camera)    return;
    camera->draw(x, y);
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::exit()
{
    
}

//---------------------------------------------------------
bool loopier::CameraPlayer::loadResource(string resourcename)
{
    camera = loopier::getCameraByName(resourcename);
}

//---------------------------------------------------------
void loopier::CameraPlayer::setCamera(CameraPtr cam)
{
    camera = cam;
}

//---------------------------------------------------------
float loopier::CameraPlayer::getWidth() const
{
    return camera->getWidth();
}

//---------------------------------------------------------
float loopier::CameraPlayer::getHeight() const
{
    return camera->getHeight();
}

//---------------------------------------------------------
ofTexture & loopier::CameraPlayer::getTexture()
{
    return camera->getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::CameraPlayer::getPixels()
{
    return camera->getPixels();
}

//---------------------------------------------------------
ofImage & loopier::CameraPlayer::getImage()
{
    return image;
}

//---------------------------------------------------------
loopier::Camera loopier::CameraPlayer::getCamera() const
{
    return *camera;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                                       *
// *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
// *                                                                       *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//---------------------------------------------------------
bool loopier::setupCameras()
{
//    ofVideoGrabber vidGrabber;
//    vector<ofVideoDevice> devices = vidGrabber.listDevices();
//    
//    for (int i = 0; i < devices.size(); i++) {
//        CameraPtr cam(new Camera(vidGrabber));
//        cam->setDeviceID(i);
//        cam->initGrabber(ofGetWidth(), ofGetHeight());
//        loopier::cameras["camera"+ofToString(i)] = cam;
//    }
//    
//    return loopier::cameras.size();
}

//---------------------------------------------------------
void loopier::listCameras()
{
//    string msg = "Number of cameras:\t" + ofToString(loopier::cameras.size());
//    loopier::CameraMap::iterator it;
//    for (it = loopier::cameras.begin(); it != loopier::cameras.end(); ++it) {
//        msg += "\n\t" + it->first;
//    }
//    
//    ofLogNotice() << msg;
}

//---------------------------------------------------------
loopier::CameraPtr  loopier::getCameraByName(string name)
{
//    return loopier::cameras.find(name)->second;
}


