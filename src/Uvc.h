//
//  Uvc.h
//  clip
//
//  Created by roger on 22/03/2018.
//
//  Manage UVC capable cameras

#ifndef Uvc_h
#define Uvc_h

#include "ofMain.h"
#include "ofxUVC.h"

namespace loopier {
    namespace uvc {
        struct UvcCam {
            int     vendorId;
            int     productId;
            int     interfaceNum;
            string  name;
        };
        
        void init();
        void update();
        void addCamera(UvcCam & cam);
        void addCamera(int aVendorId, int aProductId, int anInterfaceNum, string aName);
        
        void setAutoExposure(const bool autoexposure);
        void setExposure(const float exposure);
        void setAutoFocus(const bool autofocus);
        void setFocus(const float focus);
        void setAutoWhiteBalance(const bool autowhitebalance);
        void setWhiteBalance(const float whitebalance);
        void setGain(const float gain);
        void setBrightness(const float brightness);
        void setContrast(const float contrast);
        void setSaturation(const float saturation);
        void setSharpness(const float sharpness);
        
    } // namespace uvc
}

#endif /* Uvc_hpp */
