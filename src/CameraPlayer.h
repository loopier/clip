//
//  CameraPlayer.h
//  clip
//
//  Created by roger on 29/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _CameraPlayer
#define _CameraPlayer


#include "ofMain.h"
#include "BasePlayer.h"

namespace loopier {
    
    typedef ofVideoGrabber              VideoCamera;
    typedef shared_ptr<VideoCamera>     VideoCameraPtr;
    typedef map<string, VideoCameraPtr> VideoCameraMap;
    
    class CameraPlayer: public BasePlayer{
        
    public:
        CameraPlayer();
        virtual ~CameraPlayer();
        
        static void setupVideoCameras();
        
        void    setup();
        void    update();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        bool    loadResource(string resourcename);
        
    private:
        
        static VideoCameraMap   videocameras;
        static bool             bCamerasReady;
    };
    
}

#endif