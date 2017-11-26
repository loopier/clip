//
//  Movie.h
//  clip
//
//  Created by roger on 13/08/2017.
//
//  A class to manage resources.
//
//  It holds a list of names resources and takes care of everything that
//  concerns them, such as preloding files, etc.
//
//  -------------------------------------------------------
//  IMPORTANT !!!!
//
//  BE AWARE, DEVELOPER!!!
//
//  Although the typedefs may look simmilar to those of clip Clip there is
//  a DIFFERENCE!!  Namely:
//
//  typedef map<string, Movie>  MovieMap
//
//  It's a map of string and OBJECT -- NOT POINTER --!!!!
//  It will be used as a static variable.
//  This is because we want the movies in the map to be unique.  Otherwise, modifying
//      one from one instance of a clip would modify all the equal movies of all the other
//      instances of clips that have it.
//  We want each clip to have unique movies so it can fool with them independently from
//      other clips are doing.
//  -------------------------------------------------------

#ifndef Movie_h
#define Movie_h

#include "ofMain.h"

namespace loopier {

    typedef ofVideoPlayer       MoviePlayer;
    typedef shared_ptr<MoviePlayer>   MoviePtr;
    typedef vector<MoviePtr>    MovieList;
    typedef map<string, MoviePlayer>  MovieMap;

    

    class Movie
    {
    public:
        static void             setMoviesPath(const string & newPath);
        /// \brief  Loads resources from the basepath
        static void             preloadMovies();
        static vector<string>   getMovieNames();
        /// \brief  Prints available players to console
        static void             listMovieNames();
        static bool             movieExists(const string & moviename);
        static const string     getMoviePath(const string & moviename);
    private:
        static string   moviespath;
        static MovieMap movies;

        /// \brief  Creates a new video player and adds it to the players list.
        static void newMovieFromFile(const string & moviename, const string & path);
    };
}

#endif /* ResourceManager_hpp */
