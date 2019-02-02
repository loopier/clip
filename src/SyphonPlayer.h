//
//  SyphonPlayer.h
//  clip
//
//  Created by roger on 13/12/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifdef TARGET_OSX
#ifndef _SyphonPlayer
#define _SyphonPlayer


#include "ofMain.h"
#include "ofxSyphon.h"
#include "BasePlayer.h"

namespace loopier {
    class SyphonPlayer : public BasePlayer {
        
    public:
        SyphonPlayer();
        virtual ~SyphonPlayer();
        
        void setup();
        void update();
        void draw();
        void exit();
        
        ofTexture & getTexture();
        ofPixels &  getPixels();
        ofImage &   getImage();
        
        void    setServerName(const string servername, const string appname);
        
    private:
        ofxSyphonClient client; // input
    };
    
    typedef shared_ptr<SyphonPlayer> SyphonPlayerPtr;
}

#endif
#endif // TARGET_OSX