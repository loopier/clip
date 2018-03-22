//
//  Uvc.h
//  clip
//
//  Created by roger on 22/03/2018.
//
//  Manage UVC capable cameras

#ifndef Uvc_h
#define Uvc_h

#include "ofxUVC.h"

namespace loopier {
    class Uvc {
    public:
        Uvc();
        virtual ~Uvc();
        
        void setup();
        void update();
        void draw();
        
        ofxUVC  uvcControl;
        string  cameraName;
        int     camWidth, camHeight;
        float   focus;
        vector<ofxUVCControl>   controls;
    };
}

#endif /* Uvc_hpp */
