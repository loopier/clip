//
//  Clip.hpp
//  clip
//
//  Created by roger on 10/08/2017.
//
//  A Clip is a collection of movies.

#ifndef Clip_hpp
#define Clip_hpp

#include "ofMain.h"
#include "Video.h"

namespace loopier
{
    class Clip
    {
    public:
        Clip();
        /// \param name         String  Name of clip instance
        /// \param moviename   String  Name of movie.  See 'addMovie(...)'
        Clip(string& clipname, string& moviename);
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
        void setLoopState(const ofLoopType state);
        void setSpeed(const float newSpeed);
        
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
        
        //------------------------------------------------------------------------------------------
        //      MANAGING MOVIES
        //------------------------------------------------------------------------------------------
        /// \brief  Prints a list of the moviefiles this clip contains
        void        listMovies();
        
        /// \brief  Adds a movie to the list
        /// \param  moviename   String  The name of the movie added.
        ///                             If the movie doesn't exist it gets the default.
        /// \returns    The movie added
        MoviePtr    addMovie(const string & moviename);
        
    private:
        MoviePtr  movie; ///< The movie that is currently used
        MovieList movies;
        
        string  name;
        float   x, y;
        float   width, height;
        float   scale, scaleX, scaleY;
        bool    fullscreen;
        float   alpha; ///< Transparency of the clip
        
        bool    bDrawName;
        
//        Clip(); // Disable default constructor.  All clips must have a name
        
        
        
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
    
    typedef shared_ptr<Clip>        ClipPtr;
    typedef vector<ClipPtr>         ClipList;
    typedef map<string, ClipPtr>    ClipMap;
    
    extern ClipMap clips; ///< A list of all available (created) clips
    
    
    // ----- MANAGE CLIPS-----
    
    /// \brief  Creates a new clip with the given movie file
    /// \param  name    String  Name of the movie file (with or without extension).
    ///                         The application will look in the path for a directory named after 'name'.
    /// \param  path    String  Path to the parent directory of the subdirectory holding the movie file.
    ///                         E.g. If the movie file is named 'mymovie.mov', it should be
    ///                         located in a subfolder named 'mymovie'.  The 'path' variable
    ///                         should be the path to the directory where the subdirectory
    ///                         'mymovie' resides.
    loopier::ClipPtr newClip(string clipname);
    loopier::ClipPtr newClip(string clipname, string path);
    void removeClip(const string& clipname);
    /// \brief  Clear content
    void clearClips();
    
    // ----- UDPATE AND DRAW ALL CLIPS-----
    
    void updateClips();
    void drawClips();
    
    // ----- CLIP LIST UTILS-----
    
    /// \brief  Prints the list of clip names to console
    void listClipNames();
    /// \brief  Prints the list of clips and their contents
    void listClips();
    /// \brief  Checks if a clip with that name exists.  If it doesn't logs a warning.
    /// \param  clipname    String
    /// \returns    True if there's a clip that matches the name
    bool clipExists(const string clipname);
    
    // ----- SHOW CLIP NAMES----
    
    /// \brief  Shows names of clips
    void toggleClipNames();
    void showClipNames();
    void hideClipNames();
    
    // ----- MANAGE SINGLE CLIPS -----
    
    // ----- USE ONE CLIP -----
    /// \brief  Adds a movie to a clip
    void addMovieToClip(const string clipname, const string moviename);
    // play
    void playClip(const string clipname);
    // stop
    void stopClip(const string clipname);
    // pause
    void pauseClip(const string clipname);
    // change movie source
    // set speed
    void setClipSpeed(const string clipname, const float speed);
    // set duration -- back to first frame after N seconds
    // play range -- normalized [0.0-1.0]
    // start at frame|normalized X
    // end at frame|normalized X
    // get total duration in seconds
    // get total number of frames
    /// \brief Set loop state (none | normal | palindrome)
    void setClipLoopState(const string clipname, const ofLoopType state);
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
    void toggleFullscreenClip(const string clipname);
    // tint
    // transparency
    void setClipAlpha(const string clipname, const float alpha);
    // blendmodes
    // reset attributes -- factory defaults
    
    
    // ----- SINGLE CLIP UTILS -----
    void listClipMovies(const string clipname);
}

#endif /* Clip_hpp */
