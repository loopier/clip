//
//  Movie.cpp
//  clip
//
//  Created by roger on 13/08/2017.
//
//

#include "Movie.h"
#include "ConsoleUI.h"

//---------------------------------------------------------------------------
loopier::MovieMap   loopier::Movie::movies;
string              loopier::Movie::moviespath = "/Users/roger/Library/Application Support/Clip/resources/movies";

//---------------------------------------------------------------------------
void loopier::Movie::setMoviesPath(const string & newPath)
{
    moviespath = newPath;
}

//---------------------------------------------------------------------------
void loopier::Movie::preloadMovies()
{
    ofLogVerbose() << "Preloading movie files:";

    if (!ofDirectory(moviespath).exists()) {
        string msg = "\tDirectory not found:\t" + moviespath;
        ofLogError() << __PRETTY_FUNCTION__ << "\t" << msg;
        loopier::ConsoleUI::printError(msg);
        return;
    }

    // iterate subfolders
    ofDirectory dir(moviespath);
    vector<ofFile> subdirs = dir.getFiles();

    for ( int i = 0; i < subdirs.size(); i++ ) {
        // load contents of each subfolder
        ofFile subdir = subdirs[i];

        if (!subdir.isDirectory())  continue; // we just want directories

        vector<ofFile> files = ofDirectory(subdir.getAbsolutePath()).getFiles();

        for (int x = 0; x < files.size(); x++) {
            ofFile file = files[x];
            newMovieFromFile(file.getBaseName(), file.getAbsolutePath());
        }
    }

    ofLogVerbose() << "Finished loading movie files";
    listMovieNames();
}

//---------------------------------------------------------------------------
void loopier::Movie::newMovieFromFile(const string & moviename, const string & path)
{
    MoviePlayer movie;
    movie.load(path);
    loopier::Movie::movies[moviename] = movie;
    ofLogVerbose()  << moviename << " : " << ofFile(path).getFileName() << "\tadded to movie list " ;
}

//---------------------------------------------------------------------------
vector<string>  loopier::Movie::getMovieNames()
{
    vector<string> names;

    loopier::MovieMap::iterator it;
    for (it = loopier::Movie::movies.begin(); it != loopier::Movie::movies.end(); ++it) {
        names.push_back(it->first);
    }

    return names;
}

//---------------------------------------------------------------------------
void loopier::Movie::listMovieNames()
{
    if (movies.size() < 1) {
        string msg = "Sorry, no movies available";
        ofLogError() << msg;
        loopier::ConsoleUI::printError(msg);
        return;
    }

    loopier::MovieMap::iterator it;
    for (it = loopier::Movie::movies.begin(); it != loopier::Movie::movies.end(); ++it) {
        ofLogNotice() << (it->first) << "\t:\t" << ofFile((it->second).getMoviePath()).getFileName();
    }
}

//---------------------------------------------------------------------------
const string loopier::Movie::getMoviePath(const string & moviename)
{
    if (!movieExists(moviename))  return;
    return  movies[moviename].getMoviePath();
}

//---------------------------------------------------------------------------
bool loopier::Movie::movieExists(const string & moviename)
{
    bool b = movies.count(moviename);

    if (!b) {
        ofLogWarning() << "\tTrying to acces a movie named '" << moviename << "'.\n"
        <<  "\t\t\tIt doesn't exist.  Skipping action.";
    }

    return b;
}
