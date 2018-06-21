//
//  Types.h
//  clip
//
//  Created by roger on 26/11/2017.
//
//

#ifndef Types_h
#define Types_h

namespace loopier {
    
    /// \brief Direction of the play head when playing
    enum class PlayDirection {
        normal   = 1,    ///< forward
        reverse  = -1    ///< backwards
    };
    
    //    typedef ofLoopType LoopType;
    enum class LoopType {
        none        = OF_LOOP_NONE, // Freezes at last frame
        palindrome  = OF_LOOP_PALINDROME,
        normal      = OF_LOOP_NORMAL,
        once        = 0x03  // Plays once and then disappears
    };
    
    
    typedef vector<ofImage>             FrameList;
    typedef shared_ptr<FrameList>       FrameListPtr;
    typedef map<string, FrameListPtr>   FrameListMap;
    
    typedef ofVideoPlayer           Movie;
    typedef shared_ptr<Movie>       MoviePtr;
    typedef map<string, MoviePtr>   MovieMap;
}

#endif /* Types_h */
