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
//        Clip();
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
        void setScaleX(const float newScale);
        void setScaleY(const float newScale);
        float getScale() const;
        
        void setPosition(const float newX, const float newY);
        void setPosition(const ofPoint& newPos);
        ofPoint getPosition() const;
        
        void toggleFullscreen();
        void toggleVisibility();
        void show();
        void hide();
        
        void setAlpha(const float newAlpha);
        
        void toggleName();
        void showName();
        void hideName();
        
        //------------------------------------------------------------------------------------------
        //  Transforms
        void flipV();
        void flipH();
        
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
        /// \brief  Sets the movie to be displayed
        void        setMovie(int index);
        /// \brief  If True is passed, all movies will be played one after the other. See 'setSequenceOrder(...)'
        void        setPlayMovieSequence(const bool & bseq=true);
        /// \brief  Sets the order in which the movies will be played.
        /// \description    Movies can be played more than once.  Just put their index wherever you want them
        ///                 to be played.  E.g.: {0,1,2,3..} would play them in order; while {1, 0, 0, 3...}
        ///                 would play the second movie, then twice the first one, skip the third and play
        ///                 the forth one... -- REMBEMBER: First movie is index:'0'!!
        /// \param  sequence    Vector<int>     A list of numbers: {0,3,4,1,2,3,4,...}
        void        setMovieSequenceOrder(const vector<int>& newSequence);
        /// \brief  Sets the order in which the movies will be played.
        /// \description    Movies can be played more than once.  Just put their index wherever you want them
        ///                 to be played.  E.g.: "0,1,2,3" would play them in order; while "1, 0, 0, 3"
        ///                 would play the second movie, then twice the first one, skip the third and play
        ///                 the forth one... -- REMBEMBER: First movie is index:'0'!!
        /// \param  sequence    String      A list of numbers: "0,2,0,1,2"
        void        setMovieSequenceOrder(const string& newSequence);
        
    private:
        MoviePtr  movie; ///< The movie that is currently used
        MovieList movies;
        
        string  name;
        float   x, y;
        float   width, height;
        float   scale, scaleX, scaleY;
        float   anchorPercentX, anchorPercentY;
        float   alpha; ///< Transparency of the clip
        
        bool    bFullscreen;
        bool    bDrawName;
        bool    bVisible;
        
        // transforms
        bool    bFlipV; ///< Flip vertically
        bool    bFlipH; ///< Flip horizontally
        
        ofLoopType  loopState;    ///< See ofSetLoopState(...)
        bool        bPlaySequence; ///< If true, all movies are played in sequence order.
        int         sequenceIndex; ///< Used to keep track of the sequence order.
        vector<int> sequenceOrder; ///< Each element is a movie index.  They'll be played in order.
        
        
        Clip(); // Disable default constructor.  All clips must have a name
        
        /// \brief  Moves on to next movie when current is done
        void updateSequence();
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
    /// \brief Set loop state (none | normal | palindrome)
    void setClipLoopState(const string clipname, const ofLoopType state);
    
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
    /// \brief  Change width of Clip
    /// \param  clipname    String
    /// \param  scale       Float   Signed and normalized -- positive or negative float -- 1 is default
    void setClipWidth(const string clipname, const float width);
    void setClipHeight(const string clipname, const float height);
    void scaleClip(const string clipname, const float scale);
    void scaleUpClip(const string clipname, const float amount=0.1);
    void scaleDownClip(const string clipname, const float amount=0.1);
    void resetClipScale(const string clipname);
    void setClipVFlip(const string clipname);
    void setClipHFlip(const string clipname);
    // toggle fullscreen
    void toggleFullscreenClip(const string clipname);
    /// \brief  Toggle clip visibility
    void toggleClipVisibility(const string clipname);
    void showClip(const string clipname);
    void hideClip(const string clipname);
    // tint
    // transparency
    void setClipAlpha(const string clipname, const float alpha);
    // reset attributes -- factory defaults
    
    
    // ----- MANAGING CLIP'S MOVIES  -----
    void listClipMovies(const string clipname);
    /// \brief  Changes the movie being displayed
    /// \param  clipname    String  Name of clip
    /// \param  index       Int     Index of the movie in the clip's movie list
    void setClipMovie(const string clipname, const int index);
    void playClipMovieSequence(const string clipname);
    
    /// \brief  See Clip::setSequenceOrder(...)
    void setClipMovieSequenceOrder(const string clipname, const string sequence);
}

#endif /* Clip_hpp */
