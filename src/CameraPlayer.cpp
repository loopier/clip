//
//  CameraPlayer.cpp
//  clip
//
//  Created by roger on 29/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "CameraPlayer.h"

bool loopier::CameraPlayer::bCamerasReady = false;
loopier::VideoCameraMap loopier::CameraPlayer::videocameras;

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
    ofLogVerbose() << loopier::CameraPlayer::videocameras.size();
    ofLogVerbose() << loopier::CameraPlayer::bCamerasReady;
}

//---------------------------------------------------------
void loopier::CameraPlayer::update()
{
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::draw(float x, float y, float w, float h)
{
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::exit()
{
    
}

//---------------------------------------------------------
bool loopier::CameraPlayer::loadResource(string resourcename)
{
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::setupVideoCameras()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    ofVideoGrabber vidGrabber;
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for (int i = 0; i < devices.size(); i++) {
        VideoCameraPtr cam(new VideoCamera(vidGrabber));
        cam->setDeviceID(i);
        cam->initGrabber(ofGetWidth(), ofGetHeight());
        loopier::CameraPlayer::videocameras["camera"+ofToString(i)] = cam;
    }
}


