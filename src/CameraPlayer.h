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
    
    extern CameraMap   cameramap; // global list of all cameras
    
    class CameraPlayer: public BasePlayer{
        
    public:
        CameraPlayer();
        virtual ~CameraPlayer();
        
        void    setup();
        void    update();
        void    draw();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        bool    loadResource(string resourcename);
        void    setCamera(CameraPtr cam);
        
        float       getWidth() const;
        float       getHeight() const;
        ofTexture & getTexture();
        ofPixels &  getPixels();
        
        Camera  getCamera() const;
    private:
        CameraPtr  camera;
    };
    
    typedef shared_ptr<CameraPlayer> CameraPlayerPtr;
    
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