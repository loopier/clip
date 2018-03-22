//
//  Uvc.cpp
//  clip
//
//  Created by roger on 22/03/2018.
//
//

#include "Uvc.h"

namespace {
    ofxUVCControl   uvcControl;
    vector<loopier::uvc::UvcCam>  cameras;
}

void loopier::uvc::init()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

void loopier::uvc::addCamera(int aVendorId, int aProductId, int anInterfaceNum, string aName)
{
    UvcCam cam;
    cam.vendorId = aVendorId;
    cam.productId = aProductId;
    cam.interfaceNum = anInterfaceNum;
    cam.name = aName;
    
    cameras.push_back(cam);
}

