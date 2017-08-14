//
//  ResourceManager.cpp
//  clip
//
//  Created by roger on 13/08/2017.
//
//

#include "Video.h"

//---------------------------------------------------------------------------
loopier::MovieMap   loopier::Video::movies;
string              loopier::Video::moviespath = "/Users/roger/Library/Application Support/Clip/resources/movies";

//---------------------------------------------------------------------------
void loopier::Video::setMoviesPath(const string & newPath)
{
    moviespath = newPath;
}

//---------------------------------------------------------------------------
void loopier::Video::preloadMovies()
{
    ofLogVerbose() << "Preloading movie files:";
    
    if (!ofDirectory(moviespath).exists()) {
        ofLogError() << __PRETTY_FUNCTION__ << "\tDirectory not found:\t" << moviespath ;
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
void loopier::Video::newMovieFromFile(const string & moviename, const string & path)
{
    Movie movie;
    movie.load(path);
    loopier::Video::movies[moviename] = movie;
    ofLogVerbose()  << moviename << " : " << ofFile(path).getFileName() << "\tadded to movie list " ;
}

//---------------------------------------------------------------------------
vector<string>  loopier::Video::getMovieNames()
{
    vector<string> names;
    
    loopier::MovieMap::iterator it;
    for (it = loopier::Video::movies.begin(); it != loopier::Video::movies.end(); ++it) {
        names.push_back(it->first);
    }
    
    return names;
}

//---------------------------------------------------------------------------
void loopier::Video::listMovieNames()
{
    if (movies.size() < 1) {
        ofLogError() << "Sorry, no movies available";
        return;
    }
    
    loopier::MovieMap::iterator it;
    for (it = loopier::Video::movies.begin(); it != loopier::Video::movies.end(); ++it) {
        ofLogNotice() << (it->first) << "\t:\t" << ofFile((it->second).getMoviePath()).getFileName();
    }
}

//---------------------------------------------------------------------------
const string loopier::Video::getMoviePath(const string & moviename)
{
    if (!movieExists(moviename))  return;
    return  movies[moviename].getMoviePath();
}

//---------------------------------------------------------------------------
bool loopier::Video::movieExists(const string & moviename)
{
    bool b = movies.count(moviename);
    
    if (!b) {
        ofLogWarning() << "\tTrying to acces a movie named '" << moviename << "'.\n"
        <<  "\t\t\tIt doesn't exist.  Skipping action.";
    }
    
    return b;
}