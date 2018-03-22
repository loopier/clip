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
        void addCamera(int aVendorId, int aProductId, int anInterfaceNum, string aName);
        
    } // namespace uvc
}

#endif /* Uvc_hpp */
