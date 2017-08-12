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
//        Clip();
        Clip(string& clipname);
        virtual ~Clip();
        
        void setup(string& moviePath, bool bPlay=true);
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
        
    private:
        string  name;
        string  basepath; ///< Parent directory containing the clip files
        float   x, y;
        float   width, height;
        float   scale;
        bool    fullscreen;
        float   alpha; ///< Transparency of the clip
        ofVideoPlayer   player;
        
        Clip(); // Disable default constructor.  All clips must have a name
        
        void updateFullscreen();
        
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
    
    // ----- MANAGE CLIPS -----
    /// \brief  Creates a new clip with the movie in the given path and
    ///     adds it to loopier::clips
    loopier::ClipPtr newClip(string path, string name="");
    /// \brief  Adds the given clip to loopier::clips
    void addClip(ClipPtr clip);
    void removeClip(ClipPtr clip);
    void removeClipAt(const int index);
    void updateClips();
    void drawClips();
    
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
