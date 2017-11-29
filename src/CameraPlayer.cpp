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
    camera = loopier::CameraPlayer::videocameras.find(resourcename)->second;
}

//---------------------------------------------------------
bool loopier::CameraPlayer::setupVideoCameras()
{
    ofVideoGrabber vidGrabber;
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for (int i = 0; i < devices.size(); i++) {
        VideoCameraPtr cam(new VideoCamera(vidGrabber));
        cam->setDeviceID(i);
        cam->initGrabber(ofGetWidth(), ofGetHeight());
        loopier::CameraPlayer::videocameras["camera"+ofToString(i)] = cam;
    }
    
    if (loopier::CameraPlayer::videocameras.size() > 0) loopier::CameraPlayer::bCamerasReady = true;
    return loopier::CameraPlayer::bCamerasReady;
}

//
void loopier::CameraPlayer::listVideoCameras()
{
    string msg = "Number of cameras:\t" + ofToString(loopier::CameraPlayer::videocameras.size());
    loopier::VideoCameraMap::iterator it;
    for (it = loopier::CameraPlayer::videocameras.begin(); it != loopier::CameraPlayer::videocameras.end(); ++it) {
        msg += "\n\t" + it->first;
    }
    
    ofLogNotice() << msg;
}


