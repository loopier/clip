//
//  CameraPlayer.cpp
//  clip
//
//  Created by roger on 29/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CameraPlayer.h"

loopier::CameraMap loopier::cameras;

//---------------------------------------------------------
loopier::CameraPlayer::CameraPlayer()
{
    
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
}

//---------------------------------------------------------
void loopier::CameraPlayer::draw(float x, float y, float w, float h)
{
    if (!camera)    return;
    camera->draw(x, y, w, h);
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::exit()
{
    
}

//---------------------------------------------------------
bool loopier::CameraPlayer::loadResource(string resourcename)
{
    camera = loopier::cameras.find(resourcename)->second;
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
bool loopier::setupCameras()
{
    ofVideoGrabber vidGrabber;
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for (int i = 0; i < devices.size(); i++) {
        CameraPtr cam(new Camera(vidGrabber));
        cam->setDeviceID(i);
        cam->initGrabber(ofGetWidth(), ofGetHeight());
        loopier::cameras["camera"+ofToString(i)] = cam;
    }
    
    return loopier::cameras.size();
}

//
void loopier::listCameras()
{
    string msg = "Number of cameras:\t" + ofToString(loopier::cameras.size());
    loopier::CameraMap::iterator it;
    for (it = loopier::cameras.begin(); it != loopier::cameras.end(); ++it) {
        msg += "\n\t" + it->first;
    }
    
    ofLogNotice() << msg;
}


