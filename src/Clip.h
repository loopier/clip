//
//  Clip.hpp
//  clip
//
//  Created by roger on 10/08/2017.
//
//

#ifndef Clip_hpp
#define Clip_hpp

#include "ofMain.h"

namespace loopier
{
    class Clip
    {
    public:
        /// \param name     String  Name of clip instance
        /// \param filename String  Name of movie file with extension or not
        ///                         It's not alwas the same as 'name,' because
        ///                         there can be several instances using the same file
        /// \param path     String  Path to the movies (general) folder
        Clip(string& clipname, string& filename, string& path);
        virtual ~Clip();
        
        void setup(bool bPlay=true);
        void update();
        void draw();
        /// \brief  Resets clip to the default state
        void reset();
        
        void setName(const string& newName);
        string getName() const;
        
        void play();
        void stop();
        void pause(bool bPause=true);
        void toggleLoopState();
        
        void setScale(const float newScale);
        float getScale() const;
        
        void setPosition(const float newX, const float newY);
        void setPosition(const ofPoint& newPos);
        ofPoint getPosition() const;
        
        void toggleFullscreen();
        
        void setAlpha(const float newAlpha);
        
        void toggleName();
        void showName();
        void hideName();
        
    private:
        string  name;
        string  filebasename;
        string  extension;
        string  path; ///< Parent directory containing the clip files
        float   x, y;
        float   width, height;
        float   scale;
        bool    fullscreen;
        float   alpha; ///< Transparency of the clip
        ofVideoPlayer   player;
        
        bool    bDrawName;
        
        Clip(); // Disable default constructor.  All clips must have a name
        
        void updateFullscreen();
        
        // ----- HELPERS -----
    };
    
    //------------------------------------------
    //      INTERFACE FUNCTIONS
    //
    //  Nobody should create an instance of a Clip.
    //  Instead it's better to use the following global
    //  functions to manage the clips.  They can
    //  be called from anywhere with
    //  loopier::nameOfFunction(...)
    //------------------------------------------
    
    typedef shared_ptr<Clip> ClipPtr;
    typedef vector<ClipPtr> ClipList;
    typedef map<string, ClipPtr> ClipMap;
    
    extern ClipMap clips; ///< A list of all available (created) clips
    
    //
    // ----- UDPATE AND DRAW ALL CIPS-----
    void updateClips();
    void drawClips();
    
    // ----- CLIP LIST UTILS-----
    /// \brief  Clear content
    void clearClips();
    /// \brief  Prints the list of clip names to console
    void listClipNames();
    
    // ----- SHOW CLIP NAMES----
    
    /// \brief  Shows names of clips
    void toggleClipNames();
    void showClipNames();
    void hideClipNames();
    
    // ----- MANAGE SINGLE CLIPS -----
    
    /// \brief  Creates a new clip with the given movie file
    /// \param  name    String  Name of the movie file (with or without extension).
    ///                         The application will look in the path for a directory named after 'name'.
    /// \param  path    String  Path to the parent directory of the subdirectory holding the movie file.
    ///                         E.g. If the movie file is named 'mymovie.mov', it should be
    ///                         located in a subfolder named 'mymovie'.  The 'path' variable
    ///                         should be the path to the directory where the subdirectory
    ///                         'mymovie' resides.
    loopier::ClipPtr newClip(string name);
    loopier::ClipPtr newClip(string name, string path);
    void removeClip(const string& name);
    
    // ----- USE ONE CLIP -----
    // play
    void playClip(const string clipname);
    // stop
    void stopClip(const string clipname);
    // pause
    void pauseClip(const string clipname);
    // load movie into clip
    // set speed
    // set duration -- time it takes from frame X to frame N
    // sub clip -- play from frame X to frame N
    // start at frame X
    // end at frame X
    // get total duration in seconds
    // get total number of rames
    // loop -- loop(0..N], mirror
    void toggleClipLoopState(const string clipname);
    // pause at last frame when not looping
    // go to frame
    // set frame rate
    // get frame rate
    // sync all clips
    // sync one clip with another clip
    
    // ----- ARRANGE CLIPS -----
    // to front / set front clip
    // set clip depth
    
    // ----- CLIP ATTRIBUTES -----
    // reset all attributes
    void resetClip(const string clipname);
    // move to
    /// \brief Move clip
    /// \param  x,y   float     Normalized position.  Will be scaled according to window dimensions
    void moveClipTo(const string clipname, const float x, const float y);
    // set anchor point
    // scale -- resize
    void scaleClip(const string clipname, const float scale);
    void scaleUpClip(const string clipname, const float amount=0.1);
    void scaleDownClip(const string clipname, const float amount=0.1);
    void resetClipScale(const string clipname);
    // toggle fullscreen
    void toggleFullscreenClip(ClipPtr clip);
    void toggleFullscreenClip(const string clipname);
    void toggleFullscreenClipAt(const int index);
    // tint
    // transparency
    void setClipAlpha(const string clipname, const float alpha);
    // blendmodes
    // reset attributes -- factory defaults
    
    
}

#endif /* Clip_hpp */
