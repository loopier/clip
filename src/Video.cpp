//
//  ResourceManager.cpp
//  clip
//
//  Created by roger on 13/08/2017.
//
//

#include "Video.h"


loopier::VideoPlayerMap  loopier::Video::players;
string  loopier::Video::moviespath = "/Users/roger/Library/Application Support/Clip/resources/movies";

void loopier::Video::setMoviesPath(const string & newPath)
{
    moviespath = newPath;
}

void loopier::Video::preload()
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
            newPlayerFromFile(file.getBaseName(), file.getAbsolutePath());
        }
    }
    
    ofLogVerbose() << "Finished loading movie files";
    printNames();
}

void loopier::Video::newPlayerFromFile(const string & playername, const string & path)
{
    VideoPlayerPtr player(new VideoPlayer());
    player->load(path);
    loopier::Video::players[playername] = player;
    ofLogVerbose()  << playername << " : " << ofFile(path).getFileName() << "\tadded to player list " ;
}

vector<string>  loopier::Video::getPlayerNames()
{
    vector<string> names;
    
    loopier::VideoPlayerMap::iterator it;
    for (it = loopier::Video::players.begin(); it != loopier::Video::players.end(); ++it) {
        names.push_back(it->first);
    }
    
    return names;
}

void loopier::Video::printNames()
{
    loopier::VideoPlayerMap::iterator it;
    for (it = loopier::Video::players.begin(); it != loopier::Video::players.end(); ++it) {
        
        ofLogVerbose() << (it->first) << "\t:\t" << ofFile((*it->second).getMoviePath()).getFileName();
    }
    
}

loopier::VideoPlayerPtr    loopier::Video::getPlayer(const string & playername)
{
    if (!playerExists(playername))  return;
    return  players[playername];
}

bool    loopier::Video::playerExists(const string & playername)
{
    bool b = players.count(playername);
    
    if (!b) {
        ofLogWarning() << "\tTrying to acces a player named '" << playername << "'.\n"
        <<  "\t\t\tIt doesn't exist.  Skipping action.";
    }
    
    return b;
}