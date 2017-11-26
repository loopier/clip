//
//  Clip.h
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _Clip
#define _Clip


#include "ofMain.h"
#include "FramePlayer.h"

namespace loopier {
    
    class Clip{
        
    public:
        
//        Clip(); -- DISABLED (Private)
        virtual ~Clip();
        
        void setup();
        void update();
        void draw();
        void exit();
        
    private:
        Clip(); // Disable default constructor.  All clips must have a name
    };
    
}

#endif