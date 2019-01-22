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
    typedef vector<CameraPtr>       CameraList;
    typedef map<string, CameraPtr> CameraMap;
    
    class CameraPlayer: public BasePlayer{
        
    public:
        CameraPlayer();
        CameraPlayer(Camera & cam);
        CameraPlayer(const int deviceId);
        CameraPlayer(const float camerawidth, const float cameraheight, const int deviceId = 0);
        virtual ~CameraPlayer();
        
        void    setup(const float camerawidth, const float cameraheight, const int deviceId);
        void    update();
        void    draw();
        void    draw(float x, float y, float w, float h);
        void    exit();
        
        float       getWidth() const;
        float       getHeight() const;
        ofTexture & getTexture();
        ofPixels &  getPixels();
        ofImage &   getImage();
        
    private:
        Camera      camera;
        ofImage     image;
    };
    
    typedef shared_ptr<CameraPlayer> CameraPlayerPtr;
}

#endif