//
//  ClipManager.cpp
//  clip
//
//  Created by roger on 21/06/2018.
//
//

#include "ClipManager.h"

loopier::ClipManager* loopier::ClipManager::instance = 0;
loopier::ClipManager * loopier::ClipManager::getInstance()
{
    if(!instance) {
        instance = new ClipManager();
        ofLogVerbose() << __PRETTY_FUNCTION__ << ": First instance\n";
        return instance;
    }
    else {
        ofLogVerbose() << __PRETTY_FUNCTION__ << ": previous instance\n";
        return instance;
    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setup()
{
    groups["publiclayer"];
    groups["privatelayer"];
    groups["selectedclips"];
    groups["frameclips"];
}


//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newClip(string clipname)
{
    return newClip(clipname, clipname);
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newClip(string clipname, string resourcename)
{
    if (resourcename == "") resourcename = clipname;
    
    // if clip exists, replace it instead of creating a new one
    loopier::ClipPtr clip;
//    if (exists(clipname)) {
//        clip = getClip(clipname);
//        clip->setResourceName(resourcename);
//    } else {
//        clip = make_shared<loopier::Clip>(clipname, resourcename);
//        centerClip(clipname);
//    }
//    
//    // !!!: Should change to something more kosher, like classes returning their types
//    if (isFrameClip(clipname)) {
//        frameclipslist.erase(std::remove(frameclipslist.begin(),
//                                         frameclipslist.end(),
//                                         clipname));
//    }
//    
//    string cliptype = "";
//    
//    // look for a resource with this name
//    // if it doesn't exist, create a new Transparent FrameClip, so it can be saved later
//    
//    // TODO: Move every 'if' statement to a dedicated method for every type of clip
//    
//    // movie
//    if ( movies.count(resourcename) > 0) {
//        clip = newMovieClip(clipname, resourcename);
//        cliptype = "movie";
//    }
//    // syphon
//    else if (resourcename == "syphon") {
//        clip = newSyphonClip(clipname, resourcename);
//        cliptype = "syphon";
//    }
//    // cv
//    else if (resourcename == "cv") {
//        clip = newCvClip(clipname, resourcename);
//        cliptype = "cv";
//    }
//    // camera
//    else if ( cameraplayers.count(resourcename) > 0) {
//        clip = newCameraClip(clipname, resourcename);
//        cliptype = "camera";
//    }
//    
//    // frame list
//    else if (frames.count(resourcename) > 0) {
//        clip = newFrameClip(clipname, resourcename);
//        cliptype = "frame";
//    }
//    
//    // doesn't exist -- create a frame clip with a single transparent frame -- aka frame recorder
//    else {
//        clip = newEmptyFrameClip(clipname, resourcename);
//        cliptype = "frame";
//    }
//    
//    
//    clips[clipname] = clip;
//    clip->show();
//    clip->getPlayer()->setName(resourcename);
//    centerClip(clipname);
//    if (!isPrivate(clipname)) setPublicClip(clipname);
//    bringClipToFront(clipname);
//    ofLogVerbose() << "Created cilp: [" << cliptype << "]\t'" << clipname << "' using '" << clip->getResourceName() << "'";
    return clip;
    
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newClipFromBlob(string clipname, string resourcename)
{
    if (!exists("cv")) return;
    
    ClipPtr clip;
//    if (exists(clipname)) {
//        removeClip(clipname);
//    }
//    
//    if (resourcename.length() == 0) resourcename = clipname;
//    clip = newClip(clipname, resourcename);
//    
//    
//    // get info from the blob (size and position)
//    CvPlayerPtr cv = getPlayerAsCvPlayer("cv");
//    ofRectangle blobRect = cv->getBoundingRect();
//    // get info from the original resource
//    ofRectangle clipRect = clip->getPlayer()->getBoundingBox();
//    
//    float   scaleratio = blobRect.getHeight() / clipRect.getHeight();
//    
//    ofPoint finalposition;
//    finalposition.x = blobRect.x + (((clip->getAnchor().x * clip->getWidth()) - clipRect.x) * scaleratio);
//    finalposition.y = blobRect.y + (((clip->getAnchor().y * clip->getHeight()) - clipRect.y) * scaleratio);
//    
//    clip->setPosition(finalposition);
//    clip->setScale(scaleratio);
    
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newMovieClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
//    loopier::MoviePlayerPtr movieplayer(new MoviePlayer(movies[resourcename]));
//    clip->setup(movieplayer);
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newSyphonClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
    loopier::SyphonPlayerPtr syphonplayer(new loopier::SyphonPlayer());
    clip->setup(syphonplayer);
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newCvClip(string clipname, string resourcename)
{
    ClipPtr clip = getClip(clipname);
    loopier::CvPlayerPtr cvplayer(new loopier::CvPlayer());
    clip->setup(cvplayer);
    setPrivateClip(clipname);
    clip->setAnchorPercent(0, 0);
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newCameraClip(string clipname, string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    ClipPtr clip = getClip(clipname);
//    clip->setup(cameraplayers[resourcename]);
//    clip->setWidth(ofGetWidth());
//    clip->setHeight(ofGetHeight());
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newFrameClip(string clipname, string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    ClipPtr clip = getClip(clipname);
//    loopier::FramePlayerPtr frameplayer(new FramePlayer(frames[resourcename]));
//    clip->setup(frameplayer);
//    frameclipslist.push_back(clipname);
//    string name = resourcename;
//    float x = 0;
//    float y = 0;
//    float w = ofGetWidth();
//    float h = ofGetHeight();
//    
//    // load YAML info from the file
//    string filename = resourceFilesPath+"frames/"+resourcename+"/resource.yml";
//    if (!ofFile(filename).exists()) return clip;
//    ofxYAML yaml;
//    yaml.load(filename);
//    frameplayer->setName(yaml["name"].as<string>());
//    frameplayer->setPosition(yaml["rect"]["x"].as<float>(), yaml["rect"]["y"].as<float>());
//    frameplayer->setWidth(yaml["rect"]["width"].as<float>());
//    frameplayer->setHeight(yaml["rect"]["height"].as<float>());
    
    return clip;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::newEmptyFrameClip(string clipname, string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    // Every new empty clip needs it's own independent list of frames. We need to create a
    // new instance with its own pointer to the object and add it to as a new resource.
//    loopier::FrameListPtr framelist = make_shared<FrameList>(*frames["transparent"]);
//    frames[clipname] = framelist;
//    loopier::ClipPtr clip = newFrameClip(clipname, clipname);
//    clearFrames(clipname);
    loopier::ClipPtr clip;
    return clip;
}

//---------------------------------------------------------------------------
void loopier::ClipManager::removeClip(string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    // FIX: removing from map CRASHES APP
    if (!exists(clipname)) return;
    
//    vector<string>::iterator it;
//    // remove from frameclipslist vector
//    it = std::find(frameclipslist.begin(), frameclipslist.end(), clipname);
//    if (it != frameclipslist.end()) frameclipslist.erase(it);
//    // remove from public layers vector
//    it = std::find(publicLayers.begin(), publicLayers.end(), clipname);
//    if (it != publicLayers.end()) publicLayers.erase(it);
//    // remove from private layers vector
//    it = std::find(privateLayers.begin(), privateLayers.end(), clipname);
//    if (it != privateLayers.end()) privateLayers.erase(it);
//    // remove from private layers vector
//    it = std::find(selectedclips.begin(), selectedclips.end(), clipname);
//    if (it != selectedclips.end()) selectedclips.erase(it);
//    // remove clip
//    clips.erase(clipname);
    
    ofLogNotice() << "Clip '" << clipname << "' has been removed.";
}

//---------------------------------------------------------------------------
void loopier::ClipManager::addClipToGroup(string clipname, string groupname)
{
    // add only if clip is not already in the group
    ClipGroup group = groups[groupname];
    if (std::find(group.begin(), group.end(), clipname) != group.end()) {
        ofLogError() << "You are trying to select a clip that's already selected";
    } else {
        group.push_back(clipname);
        ofLogVerbose() << __PRETTY_FUNCTION__ << " " << clipname;
    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::removeClipFromGroup(string clipname, string groupname)
{
    if (!exists(clipname) || groups.count(groupname) <= 0) {
        ofLogError() << "Cannot remove clip from group: Either "
        << clipname << " or "
        << groupname << " doesn't exist.";
        return;
    }
    ClipGroup group = groups[groupname];
        vector<string>::iterator it = std::find(group.begin(), group.end(), clipname);
        if (it != group.end()) {
            group.erase(it);
        }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::selectClip(string clipname)
{
    if (!exists(clipname)) return;
    addClipToGroup(clipname, "selectedclips");
    clips[clipname]->select();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::deselectClip(string clipname)
{
    if (!exists(clipname)) return;
    
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    clips[clipname]->deselect();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::selectNextClip()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    string nextClipName = "";
//    if (selectedclips.size() <= 0) {
//        nextClipName = clips.begin()->first;
//    } else {
//        // get last selected clip
//        ClipMap::iterator currentClip = clips.find(selectedclips.back());
//        ClipMap::iterator nextClip = next(currentClip, 1);
//        if (nextClip == clips.end())    nextClip = clips.begin();
//        nextClipName = nextClip->first;
//    }
//    deselectAllClips();
//    selectClip(nextClipName);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::toggleClipSelection(string clipname)
{
    if (!exists(clipname)) return;
    
    if (clips[clipname]->isSelected())  deselectClip(clipname);
    else                                selectClip(clipname);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::selectAllClips()
{
    loopier::ClipMap::iterator it = clips.begin();
    for (it; it != clips.end(); ++it) {
        selectClip(it->first);
    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::deselectAllClips()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    for (auto &clipname : selectedclips) {
//        clips[clipname]->deselect();
//    }
//    
//    selectedclips.clear();
}

//---------------------------------------------------------------------------
vector<string> loopier::ClipManager::getSelectedClipnames()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    return selectedclips;
    return vector<string>();
}


//---------------------------------------------------------------------------
void loopier::ClipManager::setClipDrawOrder(string clipname, int position)
{
    if (!exists(clipname)) return;
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    vector<string>& layers = publicLayers;
//    // get current position in public list
//    vector<string>::iterator it = find(publicLayers.begin(), publicLayers.end(), clipname);
//    // if it's not there get current position in private list
//    if (it == publicLayers.end()) {
//        it = find(privateLayers.begin(), privateLayers.end(), clipname);
//        layers = privateLayers;
//    }
//    // it's not there at all -- quit
//    if (it == privateLayers.end()) {
//        ofLogWarning() << "Trying to arrange a clip that doesn't exist: " << clipname;
//        return;
//    }
//    
//    if (position >= layers.size()) position = layers.size()-1;
//    if (position < 0 ) position = 0;
//    
//    getClip(clipname)->setDepth(position);
//    
//    // remove from current position
//    layers.erase(std::remove(layers.begin(),
//                             layers.end(),
//                             clipname));
//    // add to new position
//    layers.insert(layers.end() - position, clipname);
//    listLayers();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::bringClipToFront(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, 0 );
}

//---------------------------------------------------------------------------
void loopier::ClipManager::bringClipForward(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, getClip(clipname)->getDepth() - 1 );
}

//---------------------------------------------------------------------------
void loopier::ClipManager::sendClipBackward(string clipname)
{
    if (!exists(clipname)) return;
    setClipDrawOrder(clipname, getClip(clipname)->getDepth() + 1 );
}

//---------------------------------------------------------------------------
void loopier::ClipManager::sendClipToBack(string clipname)
{
    if (!exists(clipname)) return;
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    setClipDrawOrder(clipname, publicLayers.size() - 2);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setBackgroundClip(string clipname)
{
    if (!exists(clipname)) return;
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    setClipDrawOrder(clipname, publicLayers.size() - 1);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setPublicClip(const string clipname)
{
    if (!exists(clipname))  return;
    if (isPublic(clipname)) return;
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    if (isPrivate(clipname)) {
//        privateLayers.erase(std::remove(privateLayers.begin(),
//                                        privateLayers.end(),
//                                        clipname));
//    }
//    
//    publicLayers.push_back(clipname);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setPrivateClip(const string clipname)
{
    if (!exists(clipname))      return;
    if (isPrivate(clipname))    return;
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    if (isPublic(clipname)) {
//        publicLayers.erase(std::remove(publicLayers.begin(),
//                                       publicLayers.end(),
//                                       clipname));
//    }
//    privateLayers.insert(privateLayers.begin(), clipname);
}

//---------------------------------------------------------------------------
bool loopier::ClipManager::isPublic(const string clipname)
{
    if (!exists(clipname)) return;
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    vector<string>::iterator it = find(publicLayers.begin(), publicLayers.end(), clipname);
//    return it != publicLayers.end();
}

//---------------------------------------------------------------------------
bool loopier::ClipManager::isPrivate(const string clipname)
{
    if (!exists(clipname)) return;
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//    vector<string>::iterator it = find(privateLayers.begin(), privateLayers.end(), clipname);
//    return it != privateLayers.end();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::addClipChild(const string parentclip, const string childclip)
{
    if (!exists(childclip) || !exists(parentclip) || childclip == parentclip) return;
    getClip(parentclip)->addChild(getClip(childclip));
    
}

//---------------------------------------------------------------------------
void loopier::ClipManager::removeClipChild(const string parentclip, const string childclip)
{
    if (!exists(childclip)) return;
    getClip(parentclip)->removeChild(getClip(childclip));
    
}

//---------------------------------------------------------------------------
void loopier::ClipManager::clearClipChildren(const string clip)
{
    if (!exists(clip)) return;
    getClip(clip)->clearChildren();
}

//---------------------------------------------------------------------------
vector<string> loopier::ClipManager::getClipChildrenNames(const string clip)
{
    if (!exists(clip)) return;
    vector<string> names = getClip(clip)->getChildrenNames();
    string namesstring = clip + "'s children:";
    for (auto &name: names) namesstring += " " + namesstring;
    ofLogVerbose() << namesstring;
    return names;
}

//---------------------------------------------------------------------------
void loopier::ClipManager::saveImages(string clipname) // TODO: Save images
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    // see saveFrames(...)
    
}

//---------------------------------------------------------------------------
void loopier::ClipManager::listAll()
{
    ofLogNotice() << clips.size() << " available clips";
    for (const auto &item : clips) {  ofLogNotice() << "\t" << item.first; }
}

//---------------------------------------------------------------------------
vector<string> loopier::ClipManager::getNamesList()
{
    vector<string> names;
    for (const auto &item : clips) {   names.push_back(item.first); }
    return names;
}

//---------------------------------------------------------------------------
void loopier::ClipManager::listLayers()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    string msg = "";
//    for (const auto &item : publicLayers) {  msg += " : " + item; }
//    ofLogNotice() << "Public layers: " << msg;
//    msg = "";
//    for (const auto &item : privateLayers) {  msg += " : " + item; }
    ofLogNotice() << "Private layers: " << msg;
}

//---------------------------------------------------------------------------
void loopier::ClipManager::clearAll()
{
    ofLogVerbose() << __PRETTY_FUNCTION__;
    
    while (clips.size() > 0) {
        removeClip(clips.begin()->first);
    }
}

//---------------------------------------------------------------------------
bool loopier::ClipManager::exists(string clipname)
{
    bool b = clips.count(clipname);
    if (!b) ofLogVerbose() << __PRETTY_FUNCTION__ << "\tNo clip found: " << clipname;
    return b;
}

//---------------------------------------------------------------------------
loopier::ClipPtr loopier::ClipManager::getClip(string clipname)
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
loopier::ClipPtr loopier::ClipManager::getClipAt(const float x, const float y)
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
vector<string> loopier::ClipManager::getClipsAt(const float x, const float y)
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
void loopier::ClipManager::toggleName(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->toggleName();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::showName(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->showName();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::hideName(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->hideName();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::toggleNames()
{
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        (*it->second).toggleName();
    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::showNames()
{
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        if (it->first == "cv") continue;  // hide CV's name by default
        (*it->second).showName();
    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::hideNames()
{
    loopier::ClipMap::iterator it;
    for (it = clips.begin(); it != clips.end(); ++it) {
        (*it->second).hideName();
    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::playClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->play();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::stopClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->stop();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::pauseClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->pause();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipSpeed(const string clipname, const float speed)
{
    if(!exists(clipname)) return;
    clips[clipname]->setSpeed(speed);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipLoopState(const string clipname, const loopier::LoopType state)
{
    if(!exists(clipname)) return;
    clips[clipname]->setLoopState(state);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipPlayDirection(const string clipname, const loopier::PlayDirection direction)
{
    if(!exists(clipname)) return;
    clips[clipname]->setPlayDirection(direction);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipChangePlayDirection(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->changePlayDirection();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipMask(const string clipname, const string maskclipname)
{
    if(!exists(clipname))       return;
    if(!exists(maskclipname))   return;
    clips[clipname]->setMask( clips[maskclipname] );
    //            clips[maskclipname]->hide();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::enableClipMask(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->maskOn();
    clips[clipname]->getMaskClip()->hide();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::disableClipMask(const string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if(!exists(clipname)) return;
//    clips[clipname]->maskOff();
//    if (clips[clipname]->getMaskClip()) clips[clipname]->getMaskClip()->show();
//    // Disable holes mask if needed
//    if(!exists("cv") || !clips[clipname]->getMaskClip()) return;
//    if (clips[clipname]->getMaskClip()->getName() == "cv") {
//        cv::setHolesMask(false);
//    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipHolesMask(const string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if(!exists(clipname))       return;
//    if(!exists("cv"))           return;
//    cv::setHolesMask(true);
//    setClipMask(clipname, "cv");
}

//---------------------------------------------------------------------------
//  EDIT
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::ClipManager::addFrame(const string recorderclip, const string sourceclip)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    // FIXME: OFFSET
//    if(!exists(recorderclip) ||
//       !exists(sourceclip)   ||
//       !isFrameClip(recorderclip)) return;
//    // cast from PlayerPtr to FramePlayerPtr -- note that
//    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
//    FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
//    ofImage img = clips[sourceclip]->getImage(); // TODO: Change to getTexture()
//    ofTexture maskTexture = getPlayerAsCvPlayer("cv")->getTexture();
//    
//    img.getTexture().setAlphaMask(maskTexture);
//    
//    ofFbo imgFbo;
//    imgFbo.allocate(img.getWidth(), img.getHeight(), GL_RGBA);
//    imgFbo.begin();
//    ofClear(255,255,255,0);
//    img.draw(0,0);
//    imgFbo.end();
//    
//    ofPixels pixels;
//    imgFbo.readToPixels(pixels);
//    img.setFromPixels(pixels);
//    
//    recplayer->addFrame( img );
//    
//    // set first frame's blob rectangle as original reference
//    int numframes = recplayer->getTotalNumFrames();
//    if (numframes > 1) return;
//    ofRectangle blobrect = cv::getBoundingRect();
//    // offset
//    ofPoint offset;
//    offset.x = blobrect.x;
//    offset.y = blobrect.y;
//    clips[recorderclip]->getPlayer()->setPosition(offset);
//    clips[recorderclip]->getPlayer()->setWidth(blobrect.getWidth());
//    clips[recorderclip]->getPlayer()->setHeight(blobrect.getHeight());
}

//---------------------------------------------------------------------------
void loopier::ClipManager::insertFrame(const string recorderclip, const string sourceclip)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if(!exists(recorderclip) ||
//       !exists(sourceclip)   ||
//       !isFrameClip(recorderclip)) return;
//    // cast from PlayerPtr to FramePlayerPtr -- note that
//    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
//    FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
//    recplayer->insertFrame( clips[sourceclip]->getImage() );
//    
//    ofLogVerbose() << "Inserting frame from '" << sourceclip <<"' to '" << recorderclip << "'";
}

//---------------------------------------------------------------------------
void loopier::ClipManager::removeFrame(const string clipname)
{
    if(!exists(clipname)) return;
    // cast from PlayerPtr to FramePlayerPtr -- note that
    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
    FramePlayerPtr frameplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
    frameplayer->removeFrame();
    
    ofLogVerbose() << "Removing frame from '" << clipname <<"'";
}

//---------------------------------------------------------------------------
void loopier::ClipManager::clearFrames(const string clipname)
{
    if(!exists(clipname)) return;
    // cast from PlayerPtr to FramePlayerPtr -- note that
    // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
    FramePlayerPtr frameplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
    frameplayer->clear();
    
    ofLogVerbose() << "Clearing frames from '" << clipname <<"'";
}

//---------------------------------------------------------------------------
//namespace { // anonymous namespace to keep this method private
//            // creates a unique YAML file for storing frame information
//    void saveFrameInfo(const string name, const ofRectangle & rect) {
//        string filename = resourceFilesPath+"frames/"+name+"/resource.yml";
//        ofxYAML yaml;
//        yaml["name"] = name;
//        yaml["type"] = "frame";
//        yaml["comment"] =  "The following rectangle represents the bounging box of the largest blob in the first frame.  It is used to replace other camera blobs, or other clips.";
//        yaml["rect"]["x"] = rect.x;
//        yaml["rect"]["y"] = rect.y;
//        yaml["rect"]["width"] = ofToString(rect.width);
//        yaml["rect"]["height"] = ofToString(rect.height);
//        
//        loopier::utils::saveYaml(filename, yaml);
//    }
//}

//---------------------------------------------------------------------------
void loopier::ClipManager::saveFrames(const string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if(!exists(clipname)) return;
//    FramePlayerPtr frameplayer = getPlayerAsFramePlayer(clipname);
//    FrameListPtr frames = frameplayer->getFrames();
//    // get path from clipname
//    string path = resourceFilesPath + "frames/" + clipname;
//    ofDirectory dir(path);
//    // create directory with clip's name if it doesn't exist
//    dir.remove(true);
//    dir.create();
//    dir.listDir();
//    
//    // iterate frame list and save each file as 'clipname_xxx.png'
//    FrameList::iterator it = frames->begin();
//    for (int i = 0; i < frames->size(); ++i) {
//        string filename = path + "/" + clipname + "_";
//        stringstream ss;                    // needed for formatting number
//        ss << setfill('0') << setw(3) << i; // format number with leading zeros
//        filename += ss.str() + ".png";
//        frames->at(i).save(filename);
//        ofLogVerbose() << "Saving image as: " << filename;
//    }
//    
//    saveFrameInfo(clipname, frameplayer->getBoundingBox());
}

//---------------------------------------------------------------------------
// load the info of the frames into the clip
void loopier::ClipManager::loadFrames(const string clipname, const string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if(!exists(clipname)) return;
//    newClip(clipname, resourcename);
}

//---------------------------------------------------------------------------
ofRectangle loopier::ClipManager::getResourceOriginalRectangle(const string resourcename)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    string filename = resourceFilesPath + "frames/" + resourcename + "/resource.yml";
//    if(!ofFile(filename).exists()) return ofRectangle(0,0,ofGetWidth(), ofGetHeight());
//    ofxYAML yaml;
//    yaml.load(filename);
//    return ofRectangle(yaml["rect"]["x"].as<float>(),
//                       yaml["rect"]["y"].as<float>(),
//                       yaml["rect"]["width"].as<float>(),
//                       yaml["rect"]["height"].as<float>());
}

//---------------------------------------------------------------------------
void loopier::ClipManager::firstFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->firstFrame();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::nextFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->nextFrame();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::previousFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->previousFrame();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::lastFrame(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->lastFrame();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::goToFrame(const string clipname, const int framenumber)
{
    if(!exists(clipname)) return;
    clips[clipname]->getPlayer()->setFrame(framenumber);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::saveClip(const string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    if(!exists(clipname)) return;
//    
//    string filename = resourceFilesPath+"clips/"+clipname+".yml";
//    ofLogVerbose() << clipname << ": Saving clip to " << filename;
//    
//    ClipPtr clip = clips[clipname];
//    
//    ofxYAML yaml;
//    yaml["clip"]["name"] = clip->getName();
//    yaml["clip"]["resource"] = clip->getResourceName();
//    yaml["clip"]["position"]["x"] = clip->getPosition().x * ofGetWidth();
//    yaml["clip"]["position"]["y"] = clip->getPosition().y * ofGetHeight();
//    yaml["clip"]["width"] = clip->getWidth();
//    yaml["clip"]["height"] = clip->getHeight();
//    yaml["clip"]["scale"] = clip->getScale();
//    yaml["clip"]["color"]["r"] = clip->getColor().r;
//    yaml["clip"]["color"]["g"] = clip->getColor().g;
//    yaml["clip"]["color"]["b"] = clip->getColor().b;
//    yaml["clip"]["color"]["a"] = clip->getColor().a;
//    yaml["clip"]["depth"] = clip->getDepth();
//    yaml["clip"]["fullscreen"] = clip->isFullscreen();
//    yaml["clip"]["visible"] = clip->isVisible();
//    yaml["clip"]["flipV"] = clip->isFlippedV();
//    yaml["clip"]["flipH"] = clip->isFlippedH();
//    yaml["clip"]["loop"] = static_cast<int>(clip->getLoopState());
//    //            yaml["clip"]["parent"] = clip->getParentName();
//    yaml["clip"]["offset"]["x"] = clip->getOffset().x;
//    yaml["clip"]["offset"]["y"] = clip->getOffset().y;
//    
//    loopier::utils::saveYaml(filename, yaml);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::loadClip(const string clipname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    
}

//---------------------------------------------------------------------------
void loopier::ClipManager::loadClipLibrary(const string libraryname)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
    
//    ofxJSONElement json;
//    
//    bool parsingSuccessful = json.open(clipLibraryPath + libraryname + ".json");
//    
//    if (parsingSuccessful) {
//        ofLogVerbose() << json.getRawString();
//        ofLogVerbose() << json.size();
//        
//        for (const auto &clip : json) {
//            string  clipname        = clip["name"].asString();
//            string  resourcename    = clip["resource"].asString();
//            bool    play            = clip["play"].asBool();
//            string  loop            = clip["loop"].asString();
//            float   speed           = clip["speed"].asFloat();
//            float   x               = clip["position"]["x"].asFloat() * ofGetWidth();
//            float   y               = clip["position"]["y"].asFloat() * ofGetHeight();
//            float   width           = clip["width"].asFloat();
//            float   height          = clip["height"].asFloat();
//            float   scale           = clip["scale"].asFloat();
//            float   r               = clip["color"]["r"].asFloat() * 255;
//            float   g               = clip["color"]["g"].asFloat() * 255;
//            float   b               = clip["color"]["b"].asFloat() * 255;
//            float   a               = clip["color"]["a"].asFloat() * 255;
//            ofColor color(r, g, b, a);
//            int     depth           = clip["depth"].asInt();
//            bool    visible         = clip["visible"].asBool();
//            string  mask            = clip["mask"].asString();
//            bool    fullscreen      = clip["fullscreen"].asBool();
//            bool    flipv           = clip["flipv"].asBool();
//            bool    fliph           = clip["fliph"].asBool();
//            string  parent          = clip["parent"].asString();
//            float   offsetX         = clip["offset"]["x"].asFloat();
//            float   offsetY         = clip["offset"]["y"].asFloat();
//            
//            ClipPtr newclip = newClip(clipname, resourcename);
//            if (clip["depth"] != ofxJSONElement::null && !play) newclip->stop();
//            if (loop == "palindrome")   newclip->setLoopState(LoopType::palindrome);
//            else if (loop == "once")    newclip->setLoopState(LoopType::once);
//            if (clip["speed"] != ofxJSONElement::null)   newclip->setSpeed(speed);
//            if (clip["position"] != ofxJSONElement::null)   newclip->setPosition(x, y);
//            if (clip["width"] != ofxJSONElement::null)      newclip->setWidth(width);
//            if (clip["height"] != ofxJSONElement::null)     newclip->setHeight(height);
//            if (clip["scale"] != ofxJSONElement::null)  newclip->setScale(scale);
//            if (clip["color"] != ofxJSONElement::null)  newclip->setColor(color);
//            if (clip["depth"] != ofxJSONElement::null)  newclip->setDepth(depth);
//            if (clip["depth"] != ofxJSONElement::null && !visible) newclip->hide();
//            //                   if (clip["parent"] != ofxJSONElement::null) newclip->setMask(should be clipPtr not playerPtr);
//            if (fullscreen) newclip->toggleFullscreen();
//            if (flipv) newclip->flipV();
//            if (fliph) newclip->flipH();
//            //                    if (clip["parent"] != ofxJSONElement::null)   newclip->setParent(getClip(parent));
//        }
//    }
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipLibraryPath(const string path)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    clipLibraryPath = path;
//    ofLogVerbose() << "Clip Library path: " << clipLibraryPath;
}

//---------------------------------------------------------------------------
void loopier::ClipManager::listClipLibraryNames()
{
    vector<string> names = getClipLibraryNames();
    for (const auto &name : names) {
        ofLogVerbose() << name;
    }
    
    return names;
}

//---------------------------------------------------------------------------
vector<string> loopier::ClipManager::getClipLibraryNames()
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation.";
//    ofDirectory dir(clipLibraryPath);
//    vector<ofFile> files = dir.getFiles();
//    vector<string> names;
//    for (const auto &file : files) {
//        names.push_back(file.getBaseName());
//    }
//    
//    return names;
}



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::ClipManager::resetClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->reset();
}

//---------------------------------------------------------------------------
//  MOVE CLIP
//---------------------------------------------------------------------------
void loopier::ClipManager::moveClipTo(const string clipname, const float x, const float y)
{
    if(!exists(clipname)) return;
    clips[clipname]->setPosition(x * ofGetWidth(), y * ofGetHeight());
}

//---------------------------------------------------------------------------
void loopier::ClipManager::centerClip(const string clipname)
{
    if(!exists(clipname)) return;
    //            moveClipTo(clipname, ofGetWidth() / 2, ofGetHeight() / 2);
    moveClipTo(clipname, 0.5, 0.5);
}

//---------------------------------------------------------------------------
//  SCALE CLIP
//---------------------------------------------------------------------------
void loopier::ClipManager::scaleClip(const string clipname, const float scale)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScale(scale);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipWidth(const string clipname, const float width)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScaleX(width);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipHeight(const string clipname, const float height)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScaleY(height);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::scaleUpClip(const string clipname, const float amount)
{
    if(!exists(clipname)) return;
    ClipPtr clip = clips[clipname];
    clip->setScale( clip->getScale() + amount );
}

//---------------------------------------------------------------------------
void loopier::ClipManager::scaleDownClip(const string clipname, const float amount)
{
    if(!exists(clipname)) return;
    ClipPtr clip = clips[clipname];
    clip->setScale( clip->getScale() - amount );
}

//---------------------------------------------------------------------------
void loopier::ClipManager::resetClipScale(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->setScale(1.0);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipVFlip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->flipV();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipHFlip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->flipH();
}

//---------------------------------------------------------------------------
//  FULSCREEN
//---------------------------------------------------------------------------
void loopier::ClipManager::toggleFullscreenClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->toggleFullscreen();
}

//---------------------------------------------------------------------------
//  VISIBILITY
//---------------------------------------------------------------------------
void loopier::ClipManager::toggleClipVisibility(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->toggleVisibility();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::showClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->show();
}

//---------------------------------------------------------------------------
void loopier::ClipManager::hideClip(const string clipname)
{
    if(!exists(clipname)) return;
    clips[clipname]->hide();
}

//---------------------------------------------------------------------------
//  COLOR
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipColor(const string clipname, const ofColor & color)
{
    if(!exists(clipname)) return;
    clips[clipname]->setColor(color);
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipColor(const string clipname, const float& grayscale)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(grayscale * 255));
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipColor(const string clipname, const float& grayscale, const float& alpha)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(grayscale * 255, alpha * 255));
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipColor(const string clipname, const float& r, const float& g, const float& b)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(r * 255, g * 255, b * 255));
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipColor(const string clipname, const float& r, const float& g, const float& b, const float& a)
{
    if(!exists(clipname)) return;
    setClipColor(clipname, ofColor(r * 255, g * 255, b * 255, a * 255));
}

//---------------------------------------------------------------------------
void loopier::ClipManager::setClipAlpha(const string clipname, const float alpha)
{
    if(!exists(clipname)) return;
    clips[clipname]->setAlpha(alpha * 255);
}

