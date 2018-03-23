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

//---------------------------------------------------------
void loopier::uvc::init()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    // TODO: Add cameras from config file
    UvcCam cam;
    cam.vendorId = 1133;
//    cam.productId = 2093; // C920
//    cam.name = "HD Pro Webcam C920";
//    cam.interfaceNum = 1;
    cam.productId = 2086; // C525
    cam.name = "HD Webcam C525 #2";
    cam.interfaceNum = 2;
    addCamera(cam);
    uvcControl.useCamera(cam.vendorId, cam.productId, cam.interfaceNum);
    uvcControl.setAutoExposure(true);
    controls = uvcControl.getCameraControls();
}

//---------------------------------------------------------
void loopier::uvc::update()
{
    controls = uvcControl.getCameraControls();
}

//---------------------------------------------------------
void loopier::uvc::addCamera(UvcCam & cam)
{
    cameras[cam.name] = cam;
}

//---------------------------------------------------------
void loopier::uvc::addCamera(int aVendorId, int aProductId, int anInterfaceNum, string aName)
{
    UvcCam cam;
    cam.vendorId = aVendorId;
    cam.productId = aProductId;
    cam.interfaceNum = anInterfaceNum;
    cam.name = aName;

    addCamera(cam);
}

//---------------------------------------------------------
void loopier::uvc::setAutoExposure(const bool autoexposure)
{
    uvcControl.setAutoExposure(autoexposure);
}

//---------------------------------------------------------
void loopier::uvc::setExposure(const float exposure)
{
    uvcControl.setExposure(exposure);
}

//---------------------------------------------------------
void loopier::uvc::setAutoFocus(const bool autofocus)
{
    uvcControl.setAutoFocus(autofocus);
}

//---------------------------------------------------------
void loopier::uvc::setFocus(const float focus)
{
    uvcControl.setAbsoluteFocus(focus);
}

//---------------------------------------------------------
void  loopier::uvc::setAutoWhiteBalance(const bool autowhitebalance)
{
    uvcControl.setAutoWhiteBalance(autowhitebalance);
}

//---------------------------------------------------------
void  loopier::uvc::setWhiteBalance(const float whitebalance)
{
    uvcControl.setWhiteBalance(whitebalance);
}

//---------------------------------------------------------
void  loopier::uvc::setGain(const float gain)
{
    uvcControl.setGain(gain);
}

//---------------------------------------------------------
void  loopier::uvc::setBrightness(const float brightness)
{
    uvcControl.setBrightness(brightness);
}

//---------------------------------------------------------
void  loopier::uvc::setContrast(const float contrast)
{
    uvcControl.setContrast(contrast);
}

//---------------------------------------------------------
void  loopier::uvc::setSaturation(const float saturation)
{
    uvcControl.setSaturation(saturation);
}

//---------------------------------------------------------
void  loopier::uvc::setSharpness(const float sharpness)
{
    uvcControl.setSharpness(sharpness);
}
