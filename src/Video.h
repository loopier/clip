//
//  Video.h
//  clip
//
//  Created by roger on 13/08/2017.
//
//  A class to manage resources.
//
//  It holds a list of names resources and takes care of everything that
//  concerns them, such as preloding files, ...

#ifndef Video_h
#define Video_h

#include "ofMain.h"

namespace loopier {
    
    typedef ofVideoPlayer               Player;
    typedef shared_ptr<VideoPlayer>     PlayerPtr;
    typedef vector<VideoPlayerPtr>      PlayerList;
    typedef map<string, VideoPlayerPtr> PlayerMap;
    
    class Video
    {
    public:
        /// \brief Loads resources from the path
        static void preload(const string & path);
    private:
        string basepath;
        string moviespath;
    };
}

#endif /* ResourceManager_hpp */
