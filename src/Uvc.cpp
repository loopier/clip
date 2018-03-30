//
//  Uvc.cpp
//  clip
//
//  Created by roger on 22/03/2018.
//
//

#include "Uvc.h"

namespace {
    ofxYAML                 yaml;
    ofxUVC                  uvcControl;
    vector<ofxUVCControl>   controls;
    map<string, loopier::uvc::UvcCam>  cameras;
    float focus = 0.5;
    
    void loadCameraSettings() {
        yaml.load("camerasettings.yml");
        for (int i = 0; i < yaml["cameras"].size(); i++) {
            loopier::uvc::UvcCam cam;
            cam.name = yaml["cameras"][i]["name"].as<string>();
            cam.vendorId = yaml["cameras"][i]["vendorId"].as<int>();
            cam.productId = yaml["cameras"][i]["productId"].as<int>();
            cam.interfaceNum = yaml["cameras"][i]["interfaceNum"].as<int>();
            loopier::uvc::addCamera(cam);
        }
    }
}

//---------------------------------------------------------
void loopier::uvc::init()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    
    // TODO: Add cameras from config file
//    addCamera(1133, 2093, 1, "HD Pro Webcam C920");
//    addCamera(1133, 2086, 2, "HD Webcam C525 #2");
//    UvcCam cam = cameras["HD Pro Webcam C920"];
    loadCameraSettings();
    
    UvcCam cam = cameras["HD Pro Webcam C920"];
    
    uvcControl.useCamera(cam.vendorId, cam.productId, cam.interfaceNum);
    controls = uvcControl.getCameraControls();
}

//---------------------------------------------------------
void loopier::uvc::update()
{
    // uncomment this if you want control feedback (I guess -- it's in ofxUvc example)
//    controls = uvcControl.getCameraControls();
}

//---------------------------------------------------------
void loopier::uvc::addCamera(UvcCam & cam)
{
    ofLogNotice()   << "Added camera to UVC:\n"
    << "\tName: " << cam.name << endl
    << "\tVendorID: " << cam.vendorId << endl
    << "\tProductID: " << cam.productId << endl
    << "\tInterfaceNum: " << cam.interfaceNum << endl;
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
void loopier::uvc::useCamera(string name)
{
    uvcControl.useCamera(cameras[name].vendorId,
                         cameras[name].productId,
                         cameras[name].interfaceNum);
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
