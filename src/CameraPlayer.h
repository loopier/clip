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
    
    typedef ofVideoGrabber         Camera;
    typedef shared_ptr<Camera>     CameraPtr;
    typedef map<string, CameraPtr> CameraMap;
    
    extern CameraMap   cameras; // global list of all cameras
    
    class CameraPlayer: public BasePlayer{
        
    public:
        CameraPlayer();
        virtual ~CameraPlayer();
        
        void    setup();
        void    update();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        bool    loadResource(string resourcename);
        
        float       getWidth() const;
        float       getHeight() const;
        ofTexture &  getTexture() const;
        
        Camera  getCamera() const;
    private:
        CameraPtr  camera;
    };
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    // *                                                                       *
    // *    PUBLIC INTERFACE NON-MEMBER FUNCTIONS                              *
    // *                                                                       *
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    
    bool setupCameras();
    void listCameras();
    CameraPtr   getCameraByName(string name);
}

#endif