//
//  ClipController.cpp
//  clip
//
//  Created by roger on 03/12/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "ClipController.h"

namespace {
    // * * * UNNAMED NAMESPACE              * * * * * * * * * * * * * * * * * * * * * * * *
    // * * * VARIABLES LOCAL TO THIS FILE   * * * * * * * * * * * * * * * * * * * * * * * *
    
    // app settings
    string  applicationSupportPath = "";
    string  resourceFilesPath  = "";
    string  clipLibraryPath = "";
    string  scriptsPath = "";
    string  keymapsPath = "";
    
    // clips
    loopier::ClipMap            clips;      // all clips that have been created
    vector<string>              selectedclips; // all clips that are selected
    loopier::PlayerMap          players;    // all players
    
    map<string, vector<string> > scripts; // map<nameofscript, vectorofcommands>
                                          // second argument must be in script format -- see scripts
    map<string, string>   keymap;
    
    // files
    loopier::MovieMap           movies;     // movies in resources folder
    loopier::FrameListMap       frames;     // frame sequences in resources folder
//    loopier::CameraList         cameras;    // cameras plugged -- handled by camera players
    
    vector<string>  publicLayers;      // used to control drawing order (depth)
    vector<string>  privateLayers;      // rendered only in private screen
#ifdef TARGET_OSX
    ofxSyphonServer publicSyphonServer;
    ofxSyphonServer privateSyphonServer;
#endif
    ofRectangle detectionAreaRectangle; // a rectangle created dragging the mouse -- see mouse-event methods
    
    map<string, loopier::CameraPlayerPtr>   cameraplayers;
    vector<string>                          frameclipslist;
    
    // * * * HELPER FUNCTIONS LOCAL TO THIS FILE * * * * * * * * * * * * * * * * * * * * *
    
    //---------------------------------------------------------------------------
    void initializeCameras()
    {
        ofVideoGrabber vidGrabber;
        vector<ofVideoDevice> devices = vidGrabber.listDevices();
        
        for (int i = 0; i < devices.size(); i++) {
            // create a player from this camera
            string name = devices[i].deviceName;
            float width = ofGetWidth();
            float height = ofGetHeight();
            // !!!: Something's wrong when iSight is the same size as the other cameras and
            //      they are not set to 320x240
            if (devices[i].deviceName == "Built-in iSight") {
                width = 320;
                height = 240;
            }
            
            loopier::CameraPlayerPtr cameraplayer(new loopier::CameraPlayer(width, height, i));
            cameraplayer->setName(name);
            // create a camera with the device name
            //            cameraplayers[name] = cameraplayer;
            // create a duplicate with the name 'camN' for faster typing
            cameraplayers["cam"+ofToString(i)] = cameraplayer;
        }
        
        ofLogVerbose() << "Inizialized " << cameraplayers.size() << " camera players";
    }
    
    //---------------------------------------------------------------------------
    loopier::ClipPtr initializeCv()
    {
        if (cameraplayers.size() <= 0) return;    // needs to provide a camera to the cv player constructor
        
        // FIX: now sets first camera -- should set any camera.  Something like this:
        string cameraname = cameraplayers.begin()->first;
        // get camera from cameraplayers map
        //        loopier::CameraPlayerPtr cameraplayer = cameraplayers[cameraname+"-player"];
        //        // the cv player itself
        //        loopier::CvPlayerPtr cvplayer( new loopier::CvPlayer(cameraplayer) );
        
        //  DOESN'T WORK -- although it was temporary -- cam does not render if played from cvplayer
        //        loopier::CameraPlayerPtr cameraplayer = cameraplayers.begin()->second;
        //        loopier::CvPlayerPtr cvplayer( new loopier::CvPlayer(cameraplayer) );
        
        // !!!: REMOVE -- this is a temporary solution
        loopier::CvPlayerPtr cvplayer(new loopier::CvPlayer());
        
        string clipname = "cv";
        loopier::ClipPtr clip(new loopier::Clip(clipname, cameraname));
        clip->setup(cvplayer);
        clip->setPlayer(cvplayer);
        clips[clipname] = clip;
        ofLogVerbose() << "Created cilp: [cv]\t'" << clipname << "' using '" << cameraname << "'";
        return clip;
        //                resourcename = cameraclip->getName(); // used in log message
    }
    
    bool    isFrameClip(string name)
    {
        bool isit = false;
        vector<string>::iterator it;
        it = std::find(frameclipslist.begin(), frameclipslist.end(), name);
        if (it == frameclipslist.end())   return false;
        else                                return true;
    }
    
    // Returns a CV player from the given clip
    loopier::CvPlayerPtr getPlayerAsCvPlayer(string clipname)
    {
        return dynamic_pointer_cast<loopier::CvPlayer> (clips[clipname]->getPlayer());
    }
    
    // Returns a Frame player from the given clip
    loopier::FramePlayerPtr getPlayerAsFramePlayer(string clipname)
    {
        return dynamic_pointer_cast<loopier::FramePlayer> (clips[clipname]->getPlayer());
    }
    
    // Returns a Frame player from the given clip
    loopier::MoviePlayerPtr getPlayerAsMoviePlayer(string clipname)
    {
        return dynamic_pointer_cast<loopier::MoviePlayer> (clips[clipname]->getPlayer());
    }
    
    // Returns a Frame player from the given clip
    loopier::CameraPlayerPtr getPlayerAsCameraPlayer(string clipname)
    {
        return dynamic_pointer_cast<loopier::CameraPlayer> (clips[clipname]->getPlayer());
    }
#ifdef TARGET_OSX
    // Returns a Syphon player from the given clip
    loopier::SyphonPlayerPtr getPlayerAsSyphonPlayer(string clipname)
    {
        return dynamic_pointer_cast<loopier::SyphonPlayer> (clips[clipname]->getPlayer());
    }
#endif
} // namesapce


//---------------------------------------------------------------------------
void loopier::app::init()
{
    applicationSupportPath = ofFilePath::getUserHomeDir() + "/Library/Application Support/Clip/";
    
    ofDirectory dir(applicationSupportPath);
    if (!dir.exists()) {
        ofSystemAlertDialog(applicationSupportPath + " doesn't exist.");
        ofExit();
    }
    
    resource::setResourcePath(applicationSupportPath);
    clip::setClipLibraryPath(applicationSupportPath+"clips/");
    script::setScriptPath(applicationSupportPath+"scripts/");
    app::setKeymapPath(applicationSupportPath+"keymaps/");
    
    resource::loadResources();
    initializeCameras(); // FIX: find a way to have them all on.
    loopier::resource::listAllResources();
#ifdef TARGET_OSX
    publicSyphonServer.setName("Public Screen");
    privateSyphonServer.setName("Private Screen");
#endif
    
    script::loadScript("startup");
    script::runScript("startup");
}

//---------------------------------------------------------------------------
void loopier::app::update()
{
    for (const auto &item : clips) {
        item.second->update();
    }
}

//---------------------------------------------------------------------------
void loopier::app::draw()
{
    for (const auto &clipname : publicLayers) {
        if (!clip::exists(clipname)) continue;
        clips[clipname]->draw();
    };
#ifdef TARGET_OSX
    publicSyphonServer.publishScreen();
#endif
    for (const auto &clipname : privateLayers) {
        if (!clip::exists(clipname)) continue;
        clips[clipname]->draw();
    };
    
    // draw names only in private output, even if clips ar public
    for (const auto &clipname : publicLayers) {
        if (!clip::exists(clipname)) continue;
        clips[clipname]->drawName();
    };
    
    //            for (const auto &clipname : privateLayers) {
    //                if (!clip::exists(clipname)) continue;
    //                clips[clipname]->drawOrigin();
    //            };
    
    ofPushStyle();
    ofSetColor(127, 127, 0);
    ofNoFill();
    ofSetLineWidth(1);
    ofDrawRectangle(detectionAreaRectangle);
    ofPopStyle();
#ifdef TARGET_OSX
    privateSyphonServer.publishScreen();
#endif
}

//--------------------------------------------------------------
void loopier::app::keyPressed(int key)
{
    string keyvalue;
    // if the value is not stored as a char, it is stored as an ascii code number
    if (keymap.count(ofToString(char(key))))    keyvalue = ofToString(char(key));
    else                                        keyvalue = ofToString(key);
    
    ofLogVerbose() << key << " : " << char(key) << " -> " << ofToString(char(key)) << ":" << ofToString(key);
    
    if (ofIsStringInString(keymap[keyvalue], "/")) {
        script::sendCommand(keymap[keyvalue]);
    } else {
        if (!scripts.count(keymap[keyvalue]))    script::loadScriptFile(keymap[keyvalue]);
        script::runScript(keymap[keyvalue]);
    }
    
}

//--------------------------------------------------------------
void loopier::app::keyReleased(int key)
{
    
}

//---------------------------------------------------------------------------
void loopier::app::mousePressed(int x, int y, int button)
{
    if (ofGetKeyPressed(OF_KEY_ALT)) {
        detectionAreaRectangle.setX(x);
        detectionAreaRectangle.setY(y);
        return;
    }
    
    loopier::ClipPtr clip = clip::getClipAt(x,y);
    if (clip && x == ofGetPreviousMouseX() && y == ofGetPreviousMouseY()) {
        bool selected = clip->isSelected();
        if (!ofGetKeyPressed(OF_KEY_SHIFT)) loopier::clip::deselectAllClips();
        if (selected)   clip::deselectClip(clip->getName());
        else            clip::selectClip(clip->getName());
    }
    
}

//---------------------------------------------------------------------------
void loopier::app::mouseReleased(int x, int y, int button)
{
    
    if (ofGetKeyPressed(OF_KEY_ALT)) {
        detectionAreaRectangle.setWidth(x - detectionAreaRectangle.x);
        detectionAreaRectangle.setHeight(y - detectionAreaRectangle.y);
        
        if (x == detectionAreaRectangle.x ||  y == detectionAreaRectangle.y) {
            resetDetectionAreaRectangle();
        }
        loopier::cv::setDetectionArea(detectionAreaRectangle);
        return;
    }
}

//---------------------------------------------------------------------------
void loopier::app::mouseDragged(int x, int y, int button)
{
    // set detection area
    if (ofGetKeyPressed(OF_KEY_ALT)) {
        detectionAreaRectangle.setWidth(x - detectionAreaRectangle.x);
        detectionAreaRectangle.setHeight(y - detectionAreaRectangle.y);
        loopier::cv::setDetectionArea(detectionAreaRectangle);
        return;
    }
    
    // move clips
    for (auto &clipname : selectedclips) {
        clips[clipname]->setPosition(x, y);
    }
}

void loopier::app::resetDetectionAreaRectangle()
{
    detectionAreaRectangle.set(0,0, ofGetWidth(), ofGetHeight());
}

//---------------------------------------------------------------------------
string loopier::app::getPath()
{
    return applicationSupportPath;
}

//---------------------------------------------------------------------------
void loopier::app::setKeymapPath(const string & path)
{
    keymapsPath = path;
    ofLogVerbose() << "Keymaps files path: " << keymapsPath;
}

//---------------------------------------------------------------------------
string loopier::app::getKeymapPath()
{
    return keymapsPath;
}

//---------------------------------------------------------------------------
void loopier::app::loadKeymap(const string & keymapname)
{
    keymap.clear();
    
    string path = keymapsPath + keymapname + ".yml";
    
    ofLogVerbose() << "Load keymap: " << path;
    
    ofxYAML yaml;
    yaml.load(path);
    ofxYAML::iterator it = yaml.begin();
    for (it; it != yaml.end(); ++it) {
        mapKey(it->first.as<string>(), it->second.as<string>());
    }
}

//---------------------------------------------------------------------------
void loopier::app::mapKey(const string key, const string & commandOrScriptName)
{
    keymap[key] = commandOrScriptName;
    ofLog() << "Map '" << key << "' : " << commandOrScriptName;
}



//---------------------------------------------------------------------------
void loopier::resource::setResourcePath(const string path)
{
    resourceFilesPath = path + "resources/";
    
    ofDirectory dir(resourceFilesPath);
    if (!dir.exists()) {
        ofSystemAlertDialog(dir.getAbsolutePath() + " doesn't exist.");
        ofExit();
    }
    ofLogVerbose() << "Resource files path: " << resourceFilesPath;
}

//---------------------------------------------------------------------------
string & getResourcePath()
{
    return resourceFilesPath;
}

//---------------------------------------------------------------------------
void loopier::resource::loadResource(const string & resourcename)
{
    if (ofDirectory(resourceFilesPath+"frames/"+resourcename).exists()) {
        loadFrameList(resourcename);
    } else if (ofFile(resourceFilesPath+"movies/"+resourcename+".mov").exists()) {
        loadMovie(resourcename);
    }
}

//---------------------------------------------------------------------------
void loopier::resource::loadResources(const vector<string> resourcenames)
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
void loopier::resource::loadAllResources()
{
    // load frame lists
    ofDirectory dir(resourceFilesPath+"frames/");
    vector<ofFile> files = dir.getFiles();
    for (auto &file : files) {
        loadFrameList(file.getBaseName());
    }
    
    // load movies
    dir.open(resourceFilesPath+"movies/");
    files = dir.getFiles();
    for (auto &file : files) {
        loadMovie(file.getBaseName());
    }
}

//---------------------------------------------------------------------------
void loopier::resource::clearResourceList()
{
    frames.clear();
    movies.clear();
}

//---------------------------------------------------------------------------
void loopier::resource::loadFrameList(const string & name)
{
    ofDirectory dir(resourceFilesPath+"frames/"+name);
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
void loopier::resource::loadMovie(const string & name)
{
    ofLogVerbose() << "Loading movie files from: " << resourceFilesPath;
    
    ofFile file(resourceFilesPath+"movies/"+name+".mov");
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
void loopier::resource::listAllResources()
{
    ofLogNotice() << "Number of frame lists loaded: " << frames.size();
    for (const auto &item : frames) {
        ofLogNotice() << "\t" << item.first;
    }
    ofLogNotice() << "Number of movies loaded: " << movies.size();
    for (const auto &item : movies) {
        ofLogNotice() << "\t" << item.first;
    }
    ofLogNotice() << "Number of cameras players loaded: " << cameraplayers.size();
    for (const auto &item : cameraplayers) {
        ofLogNotice() << "\t" << item.first << ": " << item.second->getName();
    }
}

//---------------------------------------------------------------------------
void loopier::resource::listCameras()
{
    ofLogNotice() << "Number of cameras players loaded: " << cameraplayers.size();
    for (const auto &item : cameraplayers) {
        ofLogNotice() << "\t" << item.first << ": " << item.second->getName();
    }
}

//---------------------------------------------------------------------------
vector<string> loopier::resource::getResourceNames()
{
    vector<string> names;
    for (const auto &item : frames) {   names.push_back(item.first); }
    for (const auto &item : movies) {   names.push_back(item.first); }
    for (const auto &item : cameraplayers) {  names.push_back(item.first); }
    return names;
}

//---------------------------------------------------------------------------
vector<string> loopier::resource::getCameraNames()
{
    vector<string> names;
    for (const auto &item : cameraplayers) {   names.push_back(item.first); }
    return names;
}

//---------------------------------------------------------------------------
bool loopier::resource::exists(string resourcename)
{
    if (frames.count(resourcename) ||
        movies.count(resourcename) ||
        cameraplayers.count(resourcename)) return true;
    else return false;
}

//---------------------------------------------------------------------------
void loopier::resource::setSyphonServerName(const string clipname, const string syphonservername, const string syphonserverapp)
{
    if (!clip::exists(clipname)) return;
    getPlayerAsSyphonPlayer(clipname)->setServerName(syphonservername, syphonserverapp);
    
}



//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newClip(string clipname)
{
    return newClip(clipname, clipname);
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newClip(string clipname, string resourcename)
{
    if (resourcename == "") resourcename = clipname;
    
    // if clip exists, replace it instead of creating a new one
    loopier::ClipPtr clip;
    if (exists(clipname)) {
        clip = getClip(clipname);
        clip->setResourceName(resourcename);
    } else {
        clip = make_shared<loopier::Clip>(clipname, resourcename);
        centerClip(clipname);
    }
    
    // !!!: Should change to something more kosher, like classes returning their types
    if (isFrameClip(clipname)) {
        frameclipslist.erase(std::remove(frameclipslist.begin(),
                                         frameclipslist.end(),
                                         clipname));
    }
    
    string cliptype = "";
    
    // look for a resource with this name
    // if it doesn't exist, create a new Transparent FrameClip, so it can be saved later
    
    // TODO: Move every 'if' statement to a dedicated method for every type of clip
    
    // movie
    if ( movies.count(resourcename) > 0) {
        clip = newMovieClip(clipname, resourcename);
        cliptype = "movie";
    }
#ifdef TARGET_OSX
    // syphon
    else if (resourcename == "syphon") {
        clip = newSyphonClip(clipname, resourcename);
        cliptype = "syphon";
    }
#endif
    // cv
    else if (resourcename == "cv") {
        clip = newCvClip(clipname, resourcename);
        cliptype = "cv";
    }
    // camera
    else if ( cameraplayers.count(resourcename) > 0) {
        clip = newCameraClip(clipname, resourcename);
        cliptype = "camera";
    }
    
    // frame list
    else if (frames.count(resourcename) > 0) {
        clip = newFrameClip(clipname, resourcename);
        cliptype = "frame";
    }
    
    // doesn't exist -- create a frame clip with a single transparent frame -- aka frame recorder
    else {
        clip = newEmptyFrameClip(clipname, resourcename);
        cliptype = "frame";
    }
    
    
    clips[clipname] = clip;
    clip->show();
    clip->getPlayer()->setName(resourcename);
    centerClip(clipname);
    if (!isPrivate(clipname)) setPublicClip(clipname);
    bringClipToFront(clipname);
    ofLogVerbose() << "Created cilp: [" << cliptype << "]\t'" << clipname << "' using '" << clip->getResourceName() << "'";
    return clip;
    
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newClipFromBlob(string clipname, string resourcename)
{
    if (!exists("cv")) return;
    
    ClipPtr clip;
    if (exists(clipname)) {
        removeClip(clipname);
    }
    
    if (resourcename.length() == 0) resourcename = clipname;
    clip = newClip(clipname, resourcename);
    
    
    // get info from the blob (size and position)
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    ofRectangle blobRect = cv->getBoundingRect();
    // get info from the original resource
    ofRectangle clipRect = clip->getPlayer()->getBoundingBox();
    
    float   scaleratio = blobRect.getHeight() / clipRect.getHeight();
    
    ofPoint finalposition;
    finalposition.x = blobRect.x + (((clip->getAnchor().x * clip->getWidth()) - clipRect.x) * scaleratio);
    finalposition.y = blobRect.y + (((clip->getAnchor().y * clip->getHeight()) - clipRect.y) * scaleratio);
    
    clip->setPosition(finalposition);
    clip->setScale(scaleratio);
    
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newMovieClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
    loopier::MoviePlayerPtr movieplayer(new MoviePlayer(movies[resourcename]));
    clip->setup(movieplayer);
    return clip;
}
#ifdef TARGET_OSX
//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newSyphonClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
    loopier::SyphonPlayerPtr syphonplayer(new loopier::SyphonPlayer());
    clip->setup(syphonplayer);
    return clip;
}
#endif
//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newCvClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
    loopier::CvPlayerPtr cvplayer(new loopier::CvPlayer());
    clip->setup(cvplayer);
    setPrivateClip(clipname);
    clip->setAnchorPercent(0, 0);
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newCameraClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
    clip->setup(cameraplayers[resourcename]);
    clip->setWidth(ofGetWidth());
    clip->setHeight(ofGetHeight());
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newFrameClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
    loopier::FramePlayerPtr frameplayer(new FramePlayer(frames[resourcename]));
    clip->setup(frameplayer);
    frameclipslist.push_back(clipname);
    string name = resourcename;
    float x = 0;
    float y = 0;
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    // load YAML info from the file
    string filename = resourceFilesPath+"frames/"+resourcename+"/resource.yml";
    if (!ofFile(filename).exists()) return clip;
    ofxYAML yaml;
    yaml.load(filename);
    frameplayer->setName(yaml["name"].as<string>());
    frameplayer->setPosition(yaml["rect"]["x"].as<float>(), yaml["rect"]["y"].as<float>());
    frameplayer->setWidth(yaml["rect"]["width"].as<float>());
    frameplayer->setHeight(yaml["rect"]["height"].as<float>());
    
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::newEmptyFrameClip(string clipname, string resourcename)
{
    // Every new empty clip needs it's own independent list of frames. We need to create a
    // new instance with its own pointer to the object and add it to as a new resource.
    loopier::FrameListPtr framelist = make_shared<FrameList>(*frames["transparent"]);
    frames[clipname] = framelist;
    loopier::ClipPtr clip = newFrameClip(clipname, clipname);
    clearFrames(clipname);
    return clip;
}

//---------------------------------------------------------------------------
void loopier::clip::removeClip(string clipname)
{
    // FIX: removing from map CRASHES APP
    if (!exists(clipname)) return;
    
    vector<string>::iterator it;
    // remove from frameclipslist vector
    it = std::find(frameclipslist.begin(), frameclipslist.end(), clipname);
    if (it != frameclipslist.end()) frameclipslist.erase(it);
    // remove from public layers vector
    it = std::find(publicLayers.begin(), publicLayers.end(), clipname);
    if (it != publicLayers.end()) publicLayers.erase(it);
    // remove from private layers vector
    it = std::find(privateLayers.begin(), privateLayers.end(), clipname);
    if (it != privateLayers.end()) privateLayers.erase(it);
    // remove from private layers vector
    it = std::find(selectedclips.begin(), selectedclips.end(), clipname);
    if (it != selectedclips.end()) selectedclips.erase(it);
    // remove clip
    clips.erase(clipname);
    
    ofLogNotice() << "Clip '" << clipname << "' has been removed.";
}

//---------------------------------------------------------------------------
void loopier::clip::selectClip(string clipname)
{
    if (!exists(clipname)) return;
    // add only if clip is not already in the list
    if (std::find(selectedclips.begin(), selectedclips.end(), clipname) != selectedclips.end()) {
        ofLogError() << "You are trying to select a clip that's already selected";
    } else {
        selectedclips.push_back(clipname);
        clips[clipname]->select();
        ofLogVerbose() << __PRETTY_FUNCTION__ << " " << clipname;
    }
}

//---------------------------------------------------------------------------
void loopier::clip::deselectClip(string clipname)
{
    if (!exists(clipname)) return;
    
    vector<string>::iterator it = std::find(selectedclips.begin(), selectedclips.end(), clipname);
    if (it != selectedclips.end()) {
        selectedclips.erase(it);
        clips[clipname]->deselect();
    }
}

//---------------------------------------------------------------------------
void loopier::clip::selectNextClip()
{
    string nextClipName = "";
    if (selectedclips.size() <= 0) {
        nextClipName = clips.begin()->first;
    } else {
        // get last selected clip
        ClipMap::iterator currentClip = clips.find(selectedclips.back());
        ClipMap::iterator nextClip = next(currentClip, 1);
        if (nextClip == clips.end())    nextClip = clips.begin();
        nextClipName = nextClip->first;
    }
    deselectAllClips();
    selectClip(nextClipName);
}

//---------------------------------------------------------------------------
void loopier::clip::toggleClipSelection(string clipname)
{
    if (!exists(clipname)) return;
    
    if (clips[clipname]->isSelected())  deselectClip(clipname);
    else                                selectClip(clipname);
}

//---------------------------------------------------------------------------
void loopier::clip::selectAllClips()
{
    loopier::ClipMap::iterator it = clips.begin();
    for (it; it != clips.end(); ++it) {
        selectClip(it->first);
    }
}

//---------------------------------------------------------------------------
void loopier::clip::deselectAllClips()
{
    for (auto &clipname : selectedclips) {
        clips[clipname]->deselect();
    }
    
    selectedclips.clear();
}

//---------------------------------------------------------------------------
vector<string> loopier::clip::getSelectedClipnames()
{
    return selectedclips;
}


//---------------------------------------------------------------------------
void loopier::clip::setClipDrawOrder(string clipname, int position)
{
    if (!exists(clipname)) return;
    vector<string>& layers = publicLayers;
    // get current position in public list
    vector<string>::iterator it = find(publicLayers.begin(), publicLayers.end(), clipname);
    // if it's not there get current position in private list
    if (it == publicLayers.end()) {
        it = find(privateLayers.begin(), privateLayers.end(), clipname);
        layers = privateLayers;
    }
    // it's not there at all -- quit
    if (it == privateLayers.end()) {
        ofLogWarning() << "Trying to arrange a clip that doesn't exist: " << clipname;
        return;
    }
    
    if (position >= layers.size()) position = layers.size()-1;
    if (position < 0 ) position = 0;
    
    getClip(clipname)->setDepth(position);
    
    // remove from current position
    layers.erase(std::remove(layers.begin(),
                             layers.end(),
                             clipname));
    // add to new position
    layers.insert(layers.end() - position, clipname);
    listLayers();
}

//---------------------------------------------------------------------------
void loopier::clip::bringClipToFront(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, 0 );
}

//---------------------------------------------------------------------------
void loopier::clip::bringClipForward(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, getClip(clipname)->getDepth() - 1 );
}

//---------------------------------------------------------------------------
void loopier::clip::sendClipBackward(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, getClip(clipname)->getDepth() + 1 );
}

//---------------------------------------------------------------------------
void loopier::clip::sendClipToBack(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, publicLayers.size() - 2);
}

//---------------------------------------------------------------------------
void loopier::clip::setBackgroundClip(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, publicLayers.size() - 1);
}

//---------------------------------------------------------------------------
void loopier::clip::setPublicClip(const string clipname)
{
    if (!exists(clipname))  return;
    if (isPublic(clipname)) return;
    if (isPrivate(clipname)) {
        privateLayers.erase(std::remove(privateLayers.begin(),
                                        privateLayers.end(),
                                        clipname));
    }
    
    publicLayers.push_back(clipname);
}

//---------------------------------------------------------------------------
void loopier::clip::setPrivateClip(const string clipname)
{
    if (!exists(clipname))      return;
    if (isPrivate(clipname))    return;
    if (isPublic(clipname)) {
        publicLayers.erase(std::remove(publicLayers.begin(),
                                       publicLayers.end(),
                                       clipname));
    }
    privateLayers.insert(privateLayers.begin(), clipname);
}

//---------------------------------------------------------------------------
bool loopier::clip::isPublic(const string clipname)
{
    if (!exists(clipname)) return;
    vector<string>::iterator it = find(publicLayers.begin(), publicLayers.end(), clipname);
    return it != publicLayers.end();
}

//---------------------------------------------------------------------------
bool loopier::clip::isPrivate(const string clipname)
{
    if (!exists(clipname)) return;
    vector<string>::iterator it = find(privateLayers.begin(), privateLayers.end(), clipname);
    return it != privateLayers.end();
}

//---------------------------------------------------------------------------
void loopier::clip::addClipChild(const string parentclip, const string childclip)
{
    if (!exists(childclip) || !exists(parentclip) || childclip == parentclip) return;
    getClip(parentclip)->addChild(getClip(childclip));
    
}

//---------------------------------------------------------------------------
void loopier::clip::removeClipChild(const string parentclip, const string childclip)
{
    if (!exists(childclip)) return;
    getClip(parentclip)->removeChild(getClip(childclip));
    
}

//---------------------------------------------------------------------------
void loopier::clip::clearClipChildren(const string clip)
{
    if (!exists(clip)) return;
    getClip(clip)->clearChildren();
}

//---------------------------------------------------------------------------
vector<string> loopier::clip::getClipChildrenNames(const string clip)
{
    if (!exists(clip)) return;
    vector<string> names = getClip(clip)->getChildrenNames();
    string namesstring = clip + "'s children:";
    for (auto &name: names) namesstring += " " + namesstring;
    ofLogVerbose() << namesstring;
    return names;
}

//---------------------------------------------------------------------------
void loopier::clip::saveImages(string clipname) // TODO: Save images
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    // see saveFrames(...)
    
}

//---------------------------------------------------------------------------
void loopier::clip::listAll()
{
    ofLogNotice() << clips.size() << " available clips";
    for (const auto &item : clips) {  ofLogNotice() << "\t" << item.first; }
}

//---------------------------------------------------------------------------
vector<string> loopier::clip::getNamesList()
{
    vector<string> names;
    for (const auto &item : clips) {   names.push_back(item.first); }
    return names;
}

//---------------------------------------------------------------------------
void loopier::clip::listLayers()
{
    string msg = "";
    for (const auto &item : publicLayers) {  msg += " : " + item; }
    ofLogNotice() << "Public layers: " << msg;
    msg = "";
    for (const auto &item : privateLayers) {  msg += " : " + item; }
    ofLogNotice() << "Private layers: " << msg;
}

//---------------------------------------------------------------------------
void loopier::clip::clearAll()
{
    ofLogVerbose() << __PRETTY_FUNCTION__;
    
    while (clips.size() > 0) {
        removeClip(clips.begin()->first);
    }
}

//---------------------------------------------------------------------------
bool loopier::clip::exists(string clipname)
{
    bool b = clips.count(clipname);
    if (!b) ofLogVerbose() << __PRETTY_FUNCTION__ << "\tNo clip found: " << clipname;
    return b;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::getClip(string clipname)
{
    ClipPtr clip;
    if (exists(clipname)) {
        clip = clips.find(clipname)->second;
    } else {
        clip = make_shared<loopier::Clip>(clipname, clipname);
    }
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::clip::getClipAt(const float x, const float y)
{
    loopier::ClipPtr clip;
    
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        ofRectangle boundingBox = (*it->second).getOriginRectangle();
        
        bool b = boundingBox.inside(x,y);
        if (boundingBox.inside(x,y)) {
            clip = it->second;
        }
    }
    return clip;
}

//---------------------------------------------------------------------------
vector<string> loopier::clip::getClipsAt(const float x, const float y)
{
    vector<string> clipnames;
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        ofRectangle boundingBox = (*it->second).getBoundingBox();
        if (boundingBox.inside(x,y)) {
            clipnames.push_back(it->first);
        }
    }
    return clipnames;
}

//---------------------------------------------------------------------------
void loopier::clip::toggleName(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->toggleName();
}

//---------------------------------------------------------------------------
void loopier::clip::showName(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->showName();
}

//---------------------------------------------------------------------------
void loopier::clip::hideName(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->hideName();
}

//---------------------------------------------------------------------------
void loopier::clip::toggleNames()
{
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        (*it->second).toggleName();
    }
}

//---------------------------------------------------------------------------
void loopier::clip::showNames()
{
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        if (it->first == "cv") continue;  // hide CV's name by default
        (*it->second).showName();
    }
}

//---------------------------------------------------------------------------
void loopier::clip::hideNames()
{
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        (*it->second).hideName();
    }
}

//---------------------------------------------------------------------------
void loopier::clip::playClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->play();
}

//---------------------------------------------------------------------------
void loopier::clip::stopClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->stop();
}

//---------------------------------------------------------------------------
void loopier::clip::pauseClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->pause();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::clip::setClipSpeed(const string clipname, const float speed)
{
    if(!exists(clipname)) return;
    clips[clipname]->setSpeed(speed);
}

//---------------------------------------------------------------------------
void loopier::clip::setClipLoopState(const string clipname, const loopier::LoopType state)
{
    if(!exists(clipname)) return;
    clips[clipname]->setLoopState(state);
}

//---------------------------------------------------------------------------
void loopier::clip::setClipPlayDirection(const string clipname, const loopier::PlayDirection direction)
{
    if(!exists(clipname)) return;
    clips[clipname]->setPlayDirection(direction);
}

//---------------------------------------------------------------------------
void loopier::clip::setClipChangePlayDirection(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->changePlayDirection();
}

//---------------------------------------------------------------------------
void loopier::clip::setClipMask(const string clipname, const string maskclipname)
{
    if(!exists(clipname))       return;
    if(!exists(maskclipname))   return;
    clips[clipname]->setMask( clips[maskclipname] );
    //            clips[maskclipname]->hide();
}

//---------------------------------------------------------------------------
void loopier::clip::enableClipMask(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->maskOn();
    clips[clipname]->getMaskClip()->hide();
}

//---------------------------------------------------------------------------
void loopier::clip::disableClipMask(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->maskOff();
    if (clips[clipname]->getMaskClip()) clips[clipname]->getMaskClip()->show();
    // Disable holes mask if needed
    if(!exists("cv") || !clips[clipname]->getMaskClip()) return;
    if (clips[clipname]->getMaskClip()->getName() == "cv") {
        cv::setHolesMask(false);
    }
}

//---------------------------------------------------------------------------
void loopier::clip::setClipHolesMask(const string clipname)
{
    if(!exists(clipname))       return;
    if(!exists("cv"))           return;
    cv::setHolesMask(true);
    setClipMask(clipname, "cv");
}

//---------------------------------------------------------------------------
//  EDIT
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::clip::addFrame(const string recorderclip, const string sourceclip)
{
    // FIXME: OFFSET
    if(!exists(recorderclip) ||
       !exists(sourceclip)   ||
       !isFrameClip(recorderclip)) return;
    // cast from PlayerPtr to FramePlayerPtr -- note that
    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
    FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
    ofImage img = clips[sourceclip]->getImage(); // TODO: Change to getTexture()
    ofTexture maskTexture = getPlayerAsCvPlayer("cv")->getTexture();
    
    img.getTexture().setAlphaMask(maskTexture);
    
    ofFbo imgFbo;
    imgFbo.allocate(img.getWidth(), img.getHeight(), GL_RGBA);
    imgFbo.begin();
    ofClear(255,255,255,0);
    img.draw(0,0);
    imgFbo.end();
    
    ofPixels pixels;
    imgFbo.readToPixels(pixels);
    img.setFromPixels(pixels);
    
    recplayer->addFrame( img );
    
    // set first frame's blob rectangle as original reference
    int numframes = recplayer->getTotalNumFrames();
    if (numframes > 1) return;
    ofRectangle blobrect = cv::getBoundingRect();
    // offset
    ofPoint offset;
    offset.x = blobrect.x;
    offset.y = blobrect.y;
    clips[recorderclip]->getPlayer()->setPosition(offset);
    clips[recorderclip]->getPlayer()->setWidth(blobrect.getWidth());
    clips[recorderclip]->getPlayer()->setHeight(blobrect.getHeight());
}

//---------------------------------------------------------------------------
void loopier::clip::insertFrame(const string recorderclip, const string sourceclip)
{
    if(!exists(recorderclip) ||
       !exists(sourceclip)   ||
       !isFrameClip(recorderclip)) return;
    // cast from PlayerPtr to FramePlayerPtr -- note that
    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
    FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
    recplayer->insertFrame( clips[sourceclip]->getImage() );
    
    ofLogVerbose() << "Inserting frame from '" << sourceclip <<"' to '" << recorderclip << "'";
}

//---------------------------------------------------------------------------
void loopier::clip::removeFrame(const string clipname)
{
    if(!exists(clipname)) return;
    // cast from PlayerPtr to FramePlayerPtr -- note that
    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
    FramePlayerPtr frameplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
    frameplayer->removeFrame();
    
    ofLogVerbose() << "Removing frame from '" << clipname <<"'";
}

//---------------------------------------------------------------------------
void loopier::clip::clearFrames(const string clipname)
{
    if(!exists(clipname)) return;
    // cast from PlayerPtr to FramePlayerPtr -- note that
    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
    FramePlayerPtr frameplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
    frameplayer->clear();
    
    ofLogVerbose() << "Clearing frames from '" << clipname <<"'";
}

//---------------------------------------------------------------------------
namespace { // anonymous namespace to keep this method private
            // creates a unique YAML file for storing frame information
    void saveFrameInfo(const string name, const ofRectangle & rect) {
        string filename = resourceFilesPath+"frames/"+name+"/resource.yml";
        ofxYAML yaml;
        yaml["name"] = name;
        yaml["type"] = "frame";
        yaml["comment"] =  "The following rectangle represents the bounging box of the largest blob in the first frame.  It is used to replace other camera blobs, or other clips.";
        yaml["rect"]["x"] = rect.x;
        yaml["rect"]["y"] = rect.y;
        yaml["rect"]["width"] = ofToString(rect.width);
        yaml["rect"]["height"] = ofToString(rect.height);
        
        loopier::utils::saveYaml(filename, yaml);
    }
}

//---------------------------------------------------------------------------
void loopier::clip::saveFrames(const string clipname)
{
    if(!exists(clipname)) return;
    FramePlayerPtr frameplayer = getPlayerAsFramePlayer(clipname);
    FrameListPtr frames = frameplayer->getFrames();
    // get path from clipname
    string path = resourceFilesPath + "frames/" + clipname;
    ofDirectory dir(path);
    // create directory with clip's name if it doesn't exist
    dir.remove(true);
    dir.create();
    dir.listDir();
    
    // iterate frame list and save each file as 'clipname_xxx.png'
    FrameList::iterator it = frames->begin();
    for (int i = 0; i < frames->size(); ++i) {
        string filename = path + "/" + clipname + "_";
        stringstream ss;                    // needed for formatting number
        ss << setfill('0') << setw(3) << i; // format number with leading zeros
        filename += ss.str() + ".png";
        frames->at(i).save(filename);
        ofLogVerbose() << "Saving image as: " << filename;
    }
    
    saveFrameInfo(clipname, frameplayer->getBoundingBox());
}

//---------------------------------------------------------------------------
// load the info of the frames into the clip
void loopier::clip::loadFrames(const string clipname, const string resourcename)
{
    if(!exists(clipname)) return;
    newClip(clipname, resourcename);
}

//---------------------------------------------------------------------------
ofRectangle loopier::clip::getResourceOriginalRectangle(const string resourcename)
{
    string filename = resourceFilesPath + "frames/" + resourcename + "/resource.yml";
    if(!ofFile(filename).exists()) return ofRectangle(0,0,ofGetWidth(), ofGetHeight());
    ofxYAML yaml;
    yaml.load(filename);
    return ofRectangle(yaml["rect"]["x"].as<float>(),
                       yaml["rect"]["y"].as<float>(),
                       yaml["rect"]["width"].as<float>(),
                       yaml["rect"]["height"].as<float>());
}

//---------------------------------------------------------------------------
void loopier::clip::firstFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->firstFrame();
}

//---------------------------------------------------------------------------
void loopier::clip::nextFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->nextFrame();
}

//---------------------------------------------------------------------------
void loopier::clip::previousFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->previousFrame();
}

//---------------------------------------------------------------------------
void loopier::clip::lastFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->lastFrame();
}

//---------------------------------------------------------------------------
void loopier::clip::goToFrame(const string clipname, const int framenumber)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->setFrame(framenumber);
}

//---------------------------------------------------------------------------
void loopier::clip::saveClip(const string clipname)
{
    if(!exists(clipname)) return;
    
    string filename = resourceFilesPath+"clips/"+clipname+".yml";
    ofLogVerbose() << clipname << ": Saving clip to " << filename;
    
    ClipPtr clip = clips[clipname];
    
    ofxYAML yaml;
    yaml["clip"]["name"] = clip->getName();
    yaml["clip"]["resource"] = clip->getResourceName();
    yaml["clip"]["position"]["x"] = clip->getPosition().x * ofGetWidth();
    yaml["clip"]["position"]["y"] = clip->getPosition().y * ofGetHeight();
    yaml["clip"]["width"] = clip->getWidth();
    yaml["clip"]["height"] = clip->getHeight();
    yaml["clip"]["scale"] = clip->getScale();
    yaml["clip"]["color"]["r"] = clip->getColor().r;
    yaml["clip"]["color"]["g"] = clip->getColor().g;
    yaml["clip"]["color"]["b"] = clip->getColor().b;
    yaml["clip"]["color"]["a"] = clip->getColor().a;
    yaml["clip"]["depth"] = clip->getDepth();
    yaml["clip"]["fullscreen"] = clip->isFullscreen();
    yaml["clip"]["visible"] = clip->isVisible();
    yaml["clip"]["flipV"] = clip->isFlippedV();
    yaml["clip"]["flipH"] = clip->isFlippedH();
    yaml["clip"]["loop"] = static_cast<int>(clip->getLoopState());
    //            yaml["clip"]["parent"] = clip->getParentName();
    yaml["clip"]["offset"]["x"] = clip->getOffset().x;
    yaml["clip"]["offset"]["y"] = clip->getOffset().y;
    
    loopier::utils::saveYaml(filename, yaml);
}

//---------------------------------------------------------------------------
void loopier::clip::loadClip(const string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    
}

//---------------------------------------------------------------------------
void loopier::clip::loadClipLibrary(const string libraryname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    
    ofxJSONElement json;
    
    bool parsingSuccessful = json.open(clipLibraryPath + libraryname + ".json");
    
    if (parsingSuccessful) {
        ofLogVerbose() << json.getRawString();
        ofLogVerbose() << json.size();
        
        for (const auto &clip : json) {
            string  clipname        = clip["name"].asString();
            string  resourcename    = clip["resource"].asString();
            bool    play            = clip["play"].asBool();
            string  loop            = clip["loop"].asString();
            float   speed           = clip["speed"].asFloat();
            float   x               = clip["position"]["x"].asFloat() * ofGetWidth();
            float   y               = clip["position"]["y"].asFloat() * ofGetHeight();
            float   width           = clip["width"].asFloat();
            float   height          = clip["height"].asFloat();
            float   scale           = clip["scale"].asFloat();
            float   r               = clip["color"]["r"].asFloat() * 255;
            float   g               = clip["color"]["g"].asFloat() * 255;
            float   b               = clip["color"]["b"].asFloat() * 255;
            float   a               = clip["color"]["a"].asFloat() * 255;
            ofColor color(r, g, b, a);
            int     depth           = clip["depth"].asInt();
            bool    visible         = clip["visible"].asBool();
            string  mask            = clip["mask"].asString();
            bool    fullscreen      = clip["fullscreen"].asBool();
            bool    flipv           = clip["flipv"].asBool();
            bool    fliph           = clip["fliph"].asBool();
            string  parent          = clip["parent"].asString();
            float   offsetX         = clip["offset"]["x"].asFloat();
            float   offsetY         = clip["offset"]["y"].asFloat();
            
            ClipPtr newclip = newClip(clipname, resourcename);
            if (clip["depth"] != ofxJSONElement::null && !play) newclip->stop();
            if (loop == "palindrome")   newclip->setLoopState(LoopType::palindrome);
            else if (loop == "once")    newclip->setLoopState(LoopType::once);
            if (clip["speed"] != ofxJSONElement::null)   newclip->setSpeed(speed);
            if (clip["position"] != ofxJSONElement::null)   newclip->setPosition(x, y);
            if (clip["width"] != ofxJSONElement::null)      newclip->setWidth(width);
            if (clip["height"] != ofxJSONElement::null)     newclip->setHeight(height);
            if (clip["scale"] != ofxJSONElement::null)  newclip->setScale(scale);
            if (clip["color"] != ofxJSONElement::null)  newclip->setColor(color);
            if (clip["depth"] != ofxJSONElement::null)  newclip->setDepth(depth);
            if (clip["depth"] != ofxJSONElement::null && !visible) newclip->hide();
            //                   if (clip["parent"] != ofxJSONElement::null) newclip->setMask(should be clipPtr not playerPtr);
            if (fullscreen) newclip->toggleFullscreen();
            if (flipv) newclip->flipV();
            if (fliph) newclip->flipH();
            //                    if (clip["parent"] != ofxJSONElement::null)   newclip->setParent(getClip(parent));
        }
    }
}

//---------------------------------------------------------------------------
void loopier::clip::setClipLibraryPath(const string path)
{
    clipLibraryPath = path;
    ofLogVerbose() << "Clip Library path: " << clipLibraryPath;
}

//---------------------------------------------------------------------------
void loopier::clip::listClipLibraryNames()
{
    vector<string> names = getClipLibraryNames();
    for (const auto &name : names) {
        ofLogVerbose() << name;
    }
    
    return names;
}

//---------------------------------------------------------------------------
vector<string> loopier::clip::getClipLibraryNames()
{
    ofDirectory dir(clipLibraryPath);
    vector<ofFile> files = dir.getFiles();
    vector<string> names;
    for (const auto &file : files) {
        names.push_back(file.getBaseName());
    }
    
    return names;
}



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::clip::resetClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->reset();
}

//---------------------------------------------------------------------------
//  MOVE CLIP
//---------------------------------------------------------------------------
void loopier::clip::moveClipTo(const string clipname, const float x, const float y)
{
    if(!exists(clipname)) return;
    clips[clipname]->setPosition(x * ofGetWidth(), y * ofGetHeight());
}

//---------------------------------------------------------------------------
void loopier::clip::centerClip(const string clipname)
{
    if(!exists(clipname)) return;
    //            moveClipTo(clipname, ofGetWidth() / 2, ofGetHeight() / 2);
    moveClipTo(clipname, 0.5, 0.5);
}

//---------------------------------------------------------------------------
//  SCALE CLIP
//---------------------------------------------------------------------------
void loopier::clip::scaleClip(const string clipname, const float scale)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScale(scale);
}

//---------------------------------------------------------------------------
void loopier::clip::setClipWidth(const string clipname, const float width)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScaleX(width);
}

//---------------------------------------------------------------------------
void loopier::clip::setClipHeight(const string clipname, const float height)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScaleY(height);
}

//---------------------------------------------------------------------------
void loopier::clip::scaleUpClip(const string clipname, const float amount)
{
    if(!exists(clipname)) return;
    ClipPtr clip = clips[clipname];
    clip->setScale( clip->getScale() + amount );
}

//---------------------------------------------------------------------------
void loopier::clip::scaleDownClip(const string clipname, const float amount)
{
    if(!exists(clipname)) return;
    ClipPtr clip = clips[clipname];
    clip->setScale( clip->getScale() - amount );
}

//---------------------------------------------------------------------------
void loopier::clip::resetClipScale(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScale(1.0);
}

//---------------------------------------------------------------------------
void loopier::clip::setClipVFlip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->flipV();
}

//---------------------------------------------------------------------------
void loopier::clip::setClipHFlip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->flipH();
}

//---------------------------------------------------------------------------
//  FULSCREEN
//---------------------------------------------------------------------------
void loopier::clip::toggleFullscreenClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->toggleFullscreen();
}

//---------------------------------------------------------------------------
//  VISIBILITY
//---------------------------------------------------------------------------
void loopier::clip::toggleClipVisibility(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->toggleVisibility();
}

//---------------------------------------------------------------------------
void loopier::clip::showClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->show();
}

//---------------------------------------------------------------------------
void loopier::clip::hideClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->hide();
}

//---------------------------------------------------------------------------
//  COLOR
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::clip::setClipColor(const string clipname, const ofColor & color)
{
    if(!exists(clipname)) return;
    clips[clipname]->setColor(color);
}

//---------------------------------------------------------------------------
void loopier::clip::setClipColor(const string clipname, const float& grayscale)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(grayscale * 255));
}

//---------------------------------------------------------------------------
void loopier::clip::setClipColor(const string clipname, const float& grayscale, const float& alpha)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(grayscale * 255, alpha * 255));
}

//---------------------------------------------------------------------------
void loopier::clip::setClipColor(const string clipname, const float& r, const float& g, const float& b)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(r * 255, g * 255, b * 255));
}

//---------------------------------------------------------------------------
void loopier::clip::setClipColor(const string clipname, const float& r, const float& g, const float& b, const float& a)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(r * 255, g * 255, b * 255, a * 255));
}

//---------------------------------------------------------------------------
void loopier::clip::setClipAlpha(const string clipname, const float alpha)
{
    if(!exists(clipname)) return;
    clips[clipname]->setAlpha(alpha * 255);
}


//---------------------------------------------------------------------------
void loopier::cv::setDeviceId(int deviceid)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}


//---------------------------------------------------------------------------
void loopier::cv::setInputClip(string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists(clipname)) return;
    if (!clip::exists("cv")) return;
    clips["cv"]->setInputClip(clip::getClip(clipname));
    clips["cv"]->setAnchorPercent(clips[clipname]->getAnchor());
    clips["cv"]->setPosition(clips[clipname]->getPosition());
    clips["cv"]->setScale(clips[clipname]->getScale());
    //            clips["cv"]->setParent(clips[clipname]);
}

//---------------------------------------------------------------------------
void loopier::cv::setColor(ofColor& color)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    //            clip::setClipColor("cv", color);
}

//---------------------------------------------------------------------------
void loopier::cv::toggleVisibility()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    clips["cv"]->toggleVisibility();
}

//---------------------------------------------------------------------------
void loopier::cv::show()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    clips["cv"]->show();
}

//---------------------------------------------------------------------------
void loopier::cv::hide()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    clips["cv"]->hide();
}

//---------------------------------------------------------------------------
ofTexture & loopier::cv::getMask()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------------------------
ofTexture & loopier::cv::getMaskTexture()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------------------------
ofPixels & loopier::cv::getMaskPixels()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
}

//---------------------------------------------------------------------------
ofTexture & loopier::cv::getHolesMask()
{
    if (!clip::exists("cv")) return;
    return getPlayerAsCvPlayer("cv")->getHolesTexture();
}

//---------------------------------------------------------------------------
void loopier::cv::setMinArea(float newArea)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    getPlayerAsCvPlayer("cv")->setMinArea(newArea);
}

//---------------------------------------------------------------------------
void loopier::cv::setMaxArea(float newArea)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    getPlayerAsCvPlayer("cv")->setMaxArea(newArea);
}

//---------------------------------------------------------------------------
void loopier::cv::setThreshold(float newThreshold)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    getPlayerAsCvPlayer("cv")->setThreshold(newThreshold);
}

//---------------------------------------------------------------------------
void loopier::cv::setFindHoles(bool findHoles)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    getPlayerAsCvPlayer("cv")->setFindHoles(findHoles);
}

//---------------------------------------------------------------------------
void loopier::cv::setHolesMask(bool holesMask)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    getPlayerAsCvPlayer("cv")->setHolesMask(holesMask);
}


//---------------------------------------------------------------------------
void loopier::cv::setMaxBlobs(int numBlobs)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    getPlayerAsCvPlayer("cv")->setMaxBlobs(numBlobs);
}

void loopier::cv::setDetectionArea(ofRectangle & rect)
{
    getPlayerAsCvPlayer("cv")->setDetectionArea(rect);
    detectionAreaRectangle = rect;
}

ofRectangle loopier::cv::getBoundingRect()
{
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    return cv->getBoundingRect();
}

ofRectangle loopier::cv::getBoundingRect(ofImage & image)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    return cv->getBoundingRect(image);
}

//---------------------------------------------------------------------------
void loopier::cv::selectBlob()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->selectCurrentBlob();
}

//---------------------------------------------------------------------------
void loopier::cv::deselectBlob()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->deselectCurrentBlob();
}

//---------------------------------------------------------------------------
void loopier::cv::selectAllBlobs()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->selectAllBlobs();
}

//---------------------------------------------------------------------------
void loopier::cv::deselectAllBlobs()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->deselectAllBlobs();
}

//---------------------------------------------------------------------------
void loopier::cv::firstBlob()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->firstBlob();
}

//---------------------------------------------------------------------------
void loopier::cv::nextBlob()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->nextBlob();
}

//---------------------------------------------------------------------------
void loopier::cv::previousBlob()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->previousBlob();
}

//---------------------------------------------------------------------------
void loopier::cv::lastBlob()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    if (!clip::exists("cv")) return;
    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
    cv->lastBlob();
}




//---------------------------------------------------------------------------
void loopier::script::loadScript(const string & scriptname)
{
    loadScriptFile(scriptname);
}

//---------------------------------------------------------------------------
void loopier::script::loadScripts(const vector<string> & scriptlist)
{
    if (scriptlist.size() <= 0) {
        loadAllScripts();
        return;
    }
    
    for (auto &scriptname : scriptlist) {
        loadScriptFile(scriptname);
    }
}

//---------------------------------------------------------------------------
void loopier::script::loadAllScripts()
{
    clearScriptList();
    ofDirectory dir(scriptsPath);
    vector<ofFile> files = dir.getFiles();
    for (auto &file : files) {
        loadScriptFile(file.getBaseName());
    }
}

//---------------------------------------------------------------------------
void loopier::script::clearScriptList()
{
    scripts.clear();
}

//---------------------------------------------------------------------------
void loopier::script::loadScriptFile(const string & filenameorpath)
{
    string path = filenameorpath;
    if (!ofFile(path).exists()) {
        path = scriptsPath + filenameorpath + ".csl";
    }
    
    ofLogVerbose() << "Load script: " << path;
    
    if (!ofFile(path).exists()) {
        ofLogWarning() << "File not found: " << path;
        return;
    }
    
    string basename = ofFile(path).getBaseName();
    
    vector < string > linesOfTheFile;
    ofBuffer buffer = ofBufferFromFile(path);
    for (auto line : buffer.getLines()){
        // discard comments (starting with #) and blank lines
        vector<string> split = ofSplitString(line, " ");
        if (line.size() <= 0 || split.size() <= 0 || split[0] == "#")  continue;
        
        scripts[basename].push_back(line);
    }
    
}

//---------------------------------------------------------------------------
void loopier::script::setScriptPath(const string & path)
{
    scriptsPath = path;
    ofLogVerbose() << "Script folder path: " << scriptsPath;
}

//---------------------------------------------------------------------------
string loopier::script::getScriptPath()
{
    return scriptsPath;
}

//---------------------------------------------------------------------------
vector<string> loopier::script::getScriptNames()
{
    vector<string> names;
    map<string, vector<string> >::iterator it = scripts.begin();
    for (it; it != scripts.end(); ++it) {
        names.push_back(it->first);
    }
    return names;
}

//---------------------------------------------------------------------------
vector<string> loopier::script::getScriptFileNames()
{
    ofDirectory dir(scriptsPath);
    vector<ofFile> files = dir.getFiles();
    vector<string> names;
    string list = "Scripts: ";
    for (const auto &file : files) {
        names.push_back(file.getBaseName());
        list += file.getBaseName() + " ";
    }
    
    ofLogVerbose() << list;
    return names;
}

//---------------------------------------------------------------------------
void loopier::script::runScript(const string & scriptname)
{
    ofLogVerbose() << "Run script: " << scriptname;
    
    if (scripts.count(scriptname) == 0) {
        ofLogWarning() << "Script not loaded: " << scriptname;
        return;
    }
    
    // scripts[scriptname] is just one script, a vector of commands, because
    // 'scripts' is a map<nameofscript, vectorofcommands>
    vector<string> commands = scripts[scriptname];
    for (auto &command : commands) {
        sendCommand(command);
    }
}

//---------------------------------------------------------------------------
void loopier::script::sendCommand(const string & command)
{
    vector<string> items = ofSplitString(command, ",");
    ofxOscMessage msg;
    msg.setAddress("/loopier/clip"+items.front());
    items.erase(items.begin());
    for (auto item : items) {
        item = ofTrim(item);
        if (utils::isInt(item)) {
            msg.addInt32Arg(ofToInt(item));
            continue;
        } else if (utils::isFloat(item)) {
            msg.addFloatArg(ofToFloat(item));
            continue;
        } else {
            ofStringReplace(item, "\"", "");
            msg.addStringArg(item);
        }
    }
    
    ofxOscSender sender;
    sender.setup("localhost", 12345);
    sender.sendMessage(msg);
}


ofImage loopier::utils::getMaskedImage(ofImage & img, ofTexture & mask){
    // if not using fbo, '.setAlphaMask(...)' is not permanent
    ofFbo fbo;
    fbo.allocate(img.getWidth(), img.getHeight(), GL_RGBA);
    img.getTexture().setAlphaMask(mask);
    fbo.begin();
    img.draw(0,0);
    fbo.end();
    ofPixels pixels;
    fbo.readToPixels(pixels);
    img.setFromPixels(pixels);
    return img;
}

ofTexture loopier::utils::getMaskedTexture(ofTexture & texture, ofTexture & mask){
    // if not using fbo, '.setAlphaMask(...)' is not permanent
    ofFbo fbo;
    fbo.allocate(texture.getWidth(), texture.getHeight(), GL_RGBA);
    texture.setAlphaMask(mask);
    fbo.begin();
    texture.draw(0,0);
    fbo.end();
    return fbo.getTexture();
}

//---------------------------------------------------------------------------
void loopier::utils::saveYaml(const string filename, ofxYAML & yaml)
{
    string name = "Manolos";
    ofRectangle rect(10,20,100,200);
    ofFile file(filename, ofFile::WriteOnly);
    
    string yamlstr = yamlToString(yaml);
    ofLog() << "\n" << yamlstr;
    
    file << yamlstr;
    file.close();
}

string loopier::utils::yamlToString(YAML::Node & yaml, const int tabulations)
{
    string str = "";
    
    ofxYAML::iterator it = yaml.begin();
    for (it; it != yaml.end(); ++it) {
        if (it->second.size() > 0){
            str += ofToString(it->first) + ":\n";
            str += yamlToString(it->second, tabulations+1);
        } else {
            // add tabulation if necessary
            for (int i = 0; i < tabulations; i++) { str += "  "; };
            if ((ofToString(it->first) == "comment")) {
                str += ofToString("# ") + ofToString(it->second) + "\n";
            } else {
                str += ofToString(it->first) + ": " + ofToString(it->second) + "\n";
            }
        }
    }
    
    return str;
}

bool loopier::utils::isFloat(const string & s)
{
    // from https://stackoverflow.com/questions/447206/c-isfloat-function
    std::istringstream iss(s);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
                          // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool loopier::utils::isInt(const string & s)
{
    // from https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
    
    char * p ;
    strtol(s.c_str(), &p, 10) ;
    
    return (*p == 0) ;
}
