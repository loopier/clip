//
//  ClipController.h
//  clip
//
//  Created by roger on 03/12/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//
//  A collection of functions to manage clips.  This is the control center for managing everything

#ifndef _ClipController
#define _ClipController


#include "ofMain.h"
#include "Clip.h"

namespace loopier {
    namespace app {
        // \brief   Sets everything up
        void        init();
    }
    
    namespace resource {
        // \brief   Lists all available resources
        void    setPath(string path);
        string& getPath();
        void    listAll();
        // \brief   Checks if a resource exists
        bool    exists(string resourcename);
    }
    
    namespace clip {
        // \brief   Creates a clip named after a resource -- or an empty FramePlayer clip
        void    newClip(string clipname);
        // \brief   Creates a clip with the given resource
        void    newClip(string clipname, string resourcename);
        
        // \brief   Adds a frame to a (Frame)clip
        void    addFrame(ofImage & img);
        
        //  \brief  Saves clip's images (frames) to a folder named after the clip
        //  \param  clipname    String      Name of the clip to be saved.  Will be used to
        //                                  find the directory or to create it (defaults to '+tmp'
        //                                  so it sticks to the top of the resources/frames directory
        void    saveImages(string clipname = "+tmp");
        
        // \brief   Prints all clip names to console
        void listAll();
    }
}

#endif