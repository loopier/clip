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
loopier::CameraPlayer::CameraPlayer(Camera & cam)
{
    camera = cam;
    image.allocate(camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR);
}

//---------------------------------------------------------
loopier::CameraPlayer::CameraPlayer(const int deviceId)
{
    camera.setDeviceID(deviceId);
    camera.setVerbose(true);
    camera.initGrabber(ofGetWidth(), ofGetHeight());
    image.allocate(camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR);
}

//---------------------------------------------------------
loopier::CameraPlayer::CameraPlayer(const float camerawidth, const float cameraheight, const int deviceId)
{
    camera.setDeviceID(deviceId);
    camera.setVerbose(true);
    camera.initGrabber(camerawidth, cameraheight);
    image.allocate(camerawidth, cameraheight, OF_IMAGE_COLOR);
    ofLogVerbose() << "id: " << deviceId << "\tw: " << camera.getWidth() << "\th: " << camera.getHeight();
}

//---------------------------------------------------------
loopier::CameraPlayer::~CameraPlayer()
{
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::setup(const float camerawidth, const float cameraheight, const int deviceId)
{
    //    camera.close();
    camera.setDeviceID(deviceId);
    camera.initGrabber(camerawidth, cameraheight);
}

//---------------------------------------------------------
void loopier::CameraPlayer::update()
{
    camera.update();
    if (camera.isFrameNew()) {
        image.setFromPixels(camera.getPixels().getData(), camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR);
    }
}

//---------------------------------------------------------
void loopier::CameraPlayer::draw()
{
    camera.draw(0,0);
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::draw(float x, float y, float w, float h)
{
    camera.draw(x, y);
    
}

//---------------------------------------------------------
void loopier::CameraPlayer::exit()
{
    
}

//---------------------------------------------------------
float loopier::CameraPlayer::getWidth() const
{
    return camera.getWidth();
}

//---------------------------------------------------------
float loopier::CameraPlayer::getHeight() const
{
    return camera.getHeight();
}

//---------------------------------------------------------
ofTexture & loopier::CameraPlayer::getTexture()
{
    return camera.getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::CameraPlayer::getPixels()
{
    return camera.getPixels();
}

//---------------------------------------------------------
ofImage & loopier::CameraPlayer::getImage()
{
    return image;
}

