//
//  Uvc.cpp
//  clip
//
//  Created by roger on 22/03/2018.
//
//

#include "Uvc.h"

namespace {
    ofxUVC                  uvcControl;
    vector<ofxUVCControl>   controls;
    map<string, loopier::uvc::UvcCam>  cameras;
    float focus = 0.5;
}

void loopier::uvc::init()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    // TODO: Add cameras from config file
    UvcCam cam;
    cam.vendorId = 1133;
    cam.productId = 2093;
    cam.interfaceNum = 2;
    cam.name = "Logitech c920";
    addCamera(cam);
    uvcControl.useCamera(cam.vendorId, cam.productId, cam.interfaceNum);
    uvcControl.setAutoExposure(true);
    controls = uvcControl.getCameraControls();
}

void loopier::uvc::update()
{
    controls = uvcControl.getCameraControls();
}

void loopier::uvc::addCamera(UvcCam & cam)
{
    cameras[cam.name] = cam;
}

void loopier::uvc::addCamera(int aVendorId, int aProductId, int anInterfaceNum, string aName)
{
    UvcCam cam;
    cam.vendorId = aVendorId;
    cam.productId = aProductId;
    cam.interfaceNum = anInterfaceNum;
    cam.name = aName;

    addCamera(cam);
}

void loopier::uvc::setAutoExposure(const bool autoexposure)
{
    uvcControl.setAutoExposure(autoexposure);
}

