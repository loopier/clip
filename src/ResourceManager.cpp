//
//  ResourceManager.cpp
//  clip
//
//  Created by roger on 21/06/2018.
//
//

#include "ResourceManager.h"


loopier::ResourceManager* loopier::ResourceManager::instance = 0;
loopier::ResourceManager * loopier::ResourceManager::getInstance()
{
    if(!instance) {
        instance = new ResourceManager();
        ofLogVerbose() << __PRETTY_FUNCTION__ << ": First instance\n";
        return instance;
    }
    else {
        ofLogVerbose() << __PRETTY_FUNCTION__ << ": previous instance\n";
        return instance;
    }
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::setResourcePath(const string path)
{
    filesPath = path + "resources/";
    
    ofDirectory dir(filesPath);
    if (!dir.exists()) {
        ofSystemAlertDialog(dir.getAbsolutePath() + " doesn't exist.");
        ofExit();
    }
    ofLogVerbose() << "Resource files path: " << filesPath;
}

//---------------------------------------------------------------------------
string & loopier::ResourceManager::getResourcePath()
{
    return filesPath;
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::loadResource(const string & resourcename)
{
    if (ofDirectory(filesPath+"frames/"+resourcename).exists()) {
        loadFrameList(resourcename);
    } else if (ofFile(filesPath+"movies/"+resourcename+".mov").exists()) {
        loadMovie(resourcename);
    }
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::loadResources(const vector<string> resourcenames)
{
    // load all if nothing is specified
    
    if (resourcenames.size() <= 0) {
        loadAllResources();
        return;
    }
    
    for (auto &name: resourcenames) {
        loadResource(name);
    }
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::loadAllResources()
{
    // load frame lists
    ofDirectory dir(filesPath+"frames/");
    vector<ofFile> files = dir.getFiles();
    for (auto &file : files) {
        loadFrameList(file.getBaseName());
    }
    
    // load movies
    dir.open(filesPath+"movies/");
    files = dir.getFiles();
    for (auto &file : files) {
        loadMovie(file.getBaseName());
    }
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::clearResourceList()
{
    frames.clear();
    movies.clear();
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::loadFrameList(const string & name)
{
    ofDirectory dir(filesPath+"frames/"+name);
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.allowExt("gif");
    
    vector<ofFile> files = dir.getFiles();
    
    // skip empty folders
    if (files.size() <= 0) {
        ofLogWarning() << "'" << name << "' folder is empty.  Skipping";
        return;
    }
    
    loopier::FrameListPtr framelist(new loopier::FrameList);     // actual list of frames
    
    for (int i = 0; i < files.size(); i++) {
        ofImage img;
        img.load(files[i].getAbsolutePath());
        framelist->push_back(img);
    }
    
    frames[name] = framelist;
    
    ofLogVerbose() << "Loaded " << framelist->size() << " frames from " << name;
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::loadMovie(const string & name)
{
    ofLogVerbose() << "Loading movie files from: " << filesPath;
    
    ofFile file(filesPath+"movies/"+name+".mov");
    if(!file.exists()) {
        ofLogWarning() << "File not found: " << file.getBaseName();
        return;
    }
    
    loopier::MoviePtr movie(new loopier::Movie);
    movie->load(file.getAbsolutePath());
    movies[file.getBaseName()] = movie;
    ofLogVerbose() << "Loaded " << file.getAbsolutePath();
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::listAllResources()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    ofLogNotice() << "Number of frame lists loaded: " << frames.size();
//    for (const auto &item : frames) {
//        ofLogNotice() << "\t" << item.first;
//    }
//    ofLogNotice() << "Number of movies loaded: " << movies.size();
//    for (const auto &item : movies) {
//        ofLogNotice() << "\t" << item.first;
//    }
//    ofLogNotice() << "Number of cameras players loaded: " << cameraplayers.size();
//    for (const auto &item : cameraplayers) {
//        ofLogNotice() << "\t" << item.first << ": " << item.second->getName();
//    }
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::listCameras()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    ofLogNotice() << "Number of cameras players loaded: " << cameraplayers.size();
//    for (const auto &item : cameraplayers) {
//        ofLogNotice() << "\t" << item.first << ": " << item.second->getName();
//    }
}

//---------------------------------------------------------------------------
vector<string> loopier::ResourceManager::getResourceNames()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
    vector<string> names;
//    for (const auto &item : frames) {   names.push_back(item.first); }
//    for (const auto &item : movies) {   names.push_back(item.first); }
//    for (const auto &item : cameraplayers) {  names.push_back(item.first); }
    return names;
}

//---------------------------------------------------------------------------
vector<string> loopier::ResourceManager::getCameraNames()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
    vector<string> names;
//    for (const auto &item : cameraplayers) {   names.push_back(item.first); }
    return names;
}

//---------------------------------------------------------------------------
bool loopier::ResourceManager::exists(string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if (frames.count(resourcename) ||
//        movies.count(resourcename) ||
//        cameraplayers.count(resourcename)) return true;
//    else return false;
}

//---------------------------------------------------------------------------
void loopier::ResourceManager::setSyphonServerName(const string clipname, const string syphonservername, const string syphonserverapp)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if (!clipManager->exists(clipname)) return;
//    getPlayerAsSyphonPlayer(clipname)->setServerName(syphonservername, syphonserverapp);
    
}