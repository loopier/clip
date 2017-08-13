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
    
    typedef ofVideoPlayer               VideoPlayer;
    typedef shared_ptr<VideoPlayer>     VideoPlayerPtr;
    typedef vector<VideoPlayerPtr>      VideoPlayerList;
    typedef map<string, VideoPlayerPtr> VideoPlayerMap;
    
    class Video
    {
    public:
        static void             setMoviesPath(const string & newPath);
        /// \brief  Loads resources from the basepath
        static void             preload();
        static vector<string>   getPlayerNames();
        static void             printNames();
        static bool             playerExists(const string & playername);
        /// \brief  Returns a pointer to a player
        static VideoPlayerPtr   getPlayer(const string & playername);
    private:
        static string           moviespath;
        static VideoPlayerMap   players;
        
        /// \brief  Creates a new video player and adds it to the players list.
        static void newPlayerFromFile(const string & playername, const string & path);
    };
}

#endif /* ResourceManager_hpp */
