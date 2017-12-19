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
    string  resourceFilesPath  = "";
    
    // clips
    loopier::ClipMap            clips;      // all clips that have been created
    loopier::PlayerMap          players;    // all players
    
    // files
    loopier::MovieMap           movies;     // movies in resources folder
    loopier::FrameListMap       frames;     // frame sequences in resources folder
//    loopier::CameraList         cameras;    // cameras plugged -- handled by camera players
    
    vector<string>  publicLayers;      // used to control drawing order (depth)
    vector<string>  privateLayers;      // rendered only in private screen
    
    ofxSyphonServer publicSyphonServer;
    ofxSyphonServer privateSyphonServer;
    
    ofRectangle detectionAreaRectangle; // a rectangle created dragging the mouse -- see mouse-event methods
    
    map<string, loopier::CameraPlayerPtr>   cameraplayers;
    vector<string>                          frameclipslist;
    
    
    
    // * * * HELPER FUNCTIONS LOCAL TO THIS FILE * * * * * * * * * * * * * * * * * * * * *
    
    //---------------------------------------------------------------------------
    void loadFrameLists()
    {
        ofLogVerbose() << "Loading frame image files from: " << resourceFilesPath;
        
        ofDirectory dir(resourceFilesPath+"frames/");
        
        vector<ofFile> subdirs = dir.getFiles();
        
        for (int x = 0; x < subdirs.size(); x++) {
            ofDirectory subdir = ofDirectory(subdirs[x]);
            if (!subdir.isDirectory()) continue;
            subdir.allowExt("png");
            subdir.allowExt("jpg");
            subdir.allowExt("gif");
            
            string name = subdirs[x].getBaseName(); // folder name used in map
            vector<ofFile> files = subdir.getFiles(); // images in folder
            
            // skip empty folders
            if (files.size() <= 0) {
                ofLogWarning() << "'" << name << "' folder is empty.  Skipping";
                continue;
            }
            
            loopier::FrameListPtr framelist(new loopier::FrameList);     // actual list of frames
            
            for (int i = 0; i < files.size(); i++) {
                ofImage img;
                img.load(files[i].getAbsolutePath());
                framelist->push_back(img);
            }
            ofLogVerbose() << "Loaded " << framelist->size() << " frames from " << name;
            frames[name] = framelist;
        }
        
        ofLogVerbose() << "Loaded " << frames.size() << " frame lists";
        //        ofExit();
    }
    
    //---------------------------------------------------------------------------
    void loadMovies()
    {
        ofLogVerbose() << "Loading movie files from: " << resourceFilesPath;
        
        ofDirectory dir(resourceFilesPath+"movies/");
        dir.allowExt("mov");
        vector<ofFile> files = dir.getFiles();
        
        for (int i = 0; i < files.size(); i++) {
            loopier::MoviePtr movie(new loopier::Movie);
            movie->load(files[i].getAbsolutePath());
            movies[files[i].getBaseName()] = movie;
        }
        
        ofLogVerbose() << "Loaded " << movies.size() << " movie files";
    }
    
    //---------------------------------------------------------------------------
    void initializeCameras()
    {
        ofVideoGrabber vidGrabber;
        vector<ofVideoDevice> devices = vidGrabber.listDevices();
        
        for (int i = 0; i < devices.size(); i++) {
            // Get las word of the name
            string name = ofSplitString(devices[i].deviceName, " ").back();
            
            // create a player from this camera
            // FIX: There's a problem when camera size is not set to 320 x 240.  Only the
            //      the camera that is initialized first will draw.
            float width = 320; // ofGetWidth(); -- one of both cams won't work with this
            float height = 240; // ofGetHeight(); -- one of both cams won't work with this
            loopier::CameraPlayerPtr cameraplayer(new loopier::CameraPlayer(width, height, i));
            cameraplayers[name] = cameraplayer;
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
    
    // Returns a Syphon player from the given clip
    loopier::SyphonPlayerPtr getPlayerAsSyphonPlayer(string clipname)
    {
        return dynamic_pointer_cast<loopier::SyphonPlayer> (clips[clipname]->getPlayer());
    }
    
} // namesapce


namespace loopier {
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    namespace app {
        
        //---------------------------------------------------------------------------
        void init()
        {
            // local helpers declared above in unnamed namespace
            loadFrameLists();
            loadMovies();
            initializeCameras(); // FIX: find a way to have them all on.
            
            clip::newClip("syphon");
            clip::hideClip("syphon");
            clip::newClip("cv");
            loopier::resource::listAll();
            
            publicSyphonServer.setName("Public Screen");
            privateSyphonServer.setName("Private Screen");
        }
        
        //---------------------------------------------------------------------------
        void update()
        {
            for (const auto &item : clips) {
                item.second->update();
            }
        }
        
        //---------------------------------------------------------------------------
        void draw()
        {
            for (const auto &clipname : publicLayers) {
                if (!clip::exists(clipname)) continue;
                clips.at(clipname)->draw();
            };
            
            publicSyphonServer.publishScreen();
            
            for (const auto &clipname : privateLayers) {
                if (!clip::exists(clipname)) continue;
                clips.at(clipname)->draw();
            };
            
            ofPushStyle();
            ofSetColor(127, 127, 0);
            ofNoFill();
            ofSetLineWidth(1);
            ofDrawRectangle(detectionAreaRectangle);
            ofPopStyle();
            
            privateSyphonServer.publishScreen();
        }
        
        //---------------------------------------------------------------------------
        void mousePressed(int x, int y, int button)
        {
            detectionAreaRectangle.setX(x);
            detectionAreaRectangle.setY(y);
        }
        
        //---------------------------------------------------------------------------
        void mouseReleased(int x, int y, int button)
        {
            detectionAreaRectangle.setWidth(x - detectionAreaRectangle.x);
            detectionAreaRectangle.setHeight(y - detectionAreaRectangle.y);
            
            if (x == detectionAreaRectangle.x ||  y == detectionAreaRectangle.y) {
                resetDetectionAreaRectangle();
            }
            loopier::cv::setDetectionArea(detectionAreaRectangle);
        }
        
        //---------------------------------------------------------------------------
        void mouseDragged(int x, int y, int button)
        {
            mouseReleased(x, y, button);
        }
        
        void resetDetectionAreaRectangle()
        {
            detectionAreaRectangle.set(0,0, ofGetWidth(), ofGetHeight());
        }
    }   // namespace app
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    namespace resource {
        
        //---------------------------------------------------------------------------
        void setPath(const string path)
        {
            resourceFilesPath = path;
            ofLogVerbose() << "Resource files path: " << resourceFilesPath;
        }
        
        //---------------------------------------------------------------------------
        string & getPath()
        {
            return resourceFilesPath;
        }
        
        //---------------------------------------------------------------------------
        void listAll()
        {
            ofLogNotice() << "Number of frame lists loaded: " << frames.size();
            for (const auto &item : frames) {   ofLogNotice() << "\t" << item.first; }
            ofLogNotice() << "Number of movies loaded: " << movies.size();
            for (const auto &item : movies) {   ofLogNotice() << "\t" << item.first; }
            ofLogNotice() << "Number of cameras players loaded: " << cameraplayers.size();
            for (const auto &item : cameraplayers) {  ofLogNotice() << "\t" << item.first; }
        }
        
        //---------------------------------------------------------------------------
        bool exists(string resourcename)
        {
            if (frames.count(resourcename) ||
                movies.count(resourcename) ||
                cameraplayers.count(resourcename)) return true;
            else return false;
        }
        
        //---------------------------------------------------------------------------
        void setSyphonServerName(const string clipname, const string syphonservername, const string syphonserverapp)
        {
            if (!clip::exists(clipname)) return;
            getPlayerAsSyphonPlayer(clipname)->setServerName(syphonservername, syphonserverapp);
            
        }
    }  // namesapce resource
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    namespace clip {
        
        //---------------------------------------------------------------------------
        ClipPtr newClip(string clipname)
        {
            return newClip(clipname, clipname);
        }
        
        //---------------------------------------------------------------------------
        ClipPtr newClip(string clipname, string resourcename)
        {
            if (resourcename == "") resourcename = clipname;
            
            // if clip exists, replace it instead of creating a new one
            loopier::ClipPtr clip;
            if (exists(clipname)) {
                clip = getClip(clipname);
            } else {
                clip = make_shared<loopier::Clip>(clipname, resourcename);
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
            
            // movie
            if ( movies.count(resourcename) > 0) {
                loopier::MoviePlayerPtr movieplayer(new MoviePlayer(movies[resourcename]));
                clip->setup(movieplayer);
                cliptype = "movie";
            }
            // syphon
            else if (resourcename == "syphon") {
                loopier::SyphonPlayerPtr syphonplayer(new loopier::SyphonPlayer());
                clip->setup(syphonplayer);
                cliptype = "syphon";
            }
            // cv
            else if (resourcename == "cv") {
                loopier::CvPlayerPtr cvplayer(new loopier::CvPlayer());
                clip->setup(cvplayer);
                setPrivateClip(clipname);
                cliptype = "cv";
            }
            // camera
            else if ( cameraplayers.count(resourcename) > 0) {
                clip->setup(cameraplayers[resourcename]);
                clip->setScale(3.2);
                cliptype = "camera";
            }
            
            // frame list
            else if (frames.count(resourcename) > 0) {
                loopier::FramePlayerPtr frameplayer(new FramePlayer(frames[resourcename]));
                clip->setup(frameplayer);
                frameclipslist.push_back(clipname);
                cliptype = "frame";
            }
            
            // doesn't exist -- create a frame clip with a single transparent frame -- aka frame recorder
            else {                
                loopier::FramePlayerPtr frameplayer(new FramePlayer(frames["transparent"]));
                clip->setup(frameplayer);
                frameclipslist.push_back(clipname);
                cliptype = "frame";
                frameplayer->clear();
            }
            
            
            clips[clipname] = clip;
            clip->show();
            if (!isPrivate(clipname)) setPublicClip(clipname);
            bringClipToFront(clipname);
            centerClip(clipname);
            ofLogVerbose() << "Created cilp: [" << cliptype << "]\t'" << clipname << "' using '" << resourcename << "'";
            return clip;
        
        }
        
        //---------------------------------------------------------------------------
        void removeClip(string clipname)
        {
            // FIX: removing from map CRASHES APP
            if (!exists(clipname)) return;
            
//            vector<string>::iterator it;
//            it = std::find(frameplayerslist.begin(), frameplayerslist.end(), clipname);
//            frameplayerslist.erase(it);
            clips[clipname]->hide();
            clips[clipname]->stop();
//            clips.erase(clipname);
        }
        
        //---------------------------------------------------------------------------
        void setClipDrawOrder(string clipname, int position)
        {
            if (!exists(clipname)) return;
            vector<string>& layers = publicLayers;
            // get current position in public list
            vector<string>::iterator it = find(publicLayers.begin(), publicLayers.end(), clipname);
            // if it's not there get current position in private list
            if (it == publicLayers.end()) {
                it = find(publicLayers.begin(), publicLayers.end(), clipname);
                layers = privateLayers;
            }
            //
            if (it == privateLayers.end()) return;  // it's not there at all -- quit
            
            if (position >= publicLayers.size()) position = publicLayers.size()-1;
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
        void bringClipToFront(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, 0 );
        }
        
        //---------------------------------------------------------------------------
        void bringClipForward(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, getClip(clipname)->getDepth() - 1 );
        }
        
        //---------------------------------------------------------------------------
        void sendClipBackward(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, getClip(clipname)->getDepth() + 1 );
        }
        
        //---------------------------------------------------------------------------
        void sendClipToBack(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, publicLayers.size() - 2);
        }
        
        //---------------------------------------------------------------------------
        void setBackgroundClip(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, publicLayers.size() - 1);
        }
        
        //---------------------------------------------------------------------------
        void setPublicClip(const string clipname)
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
        void setPrivateClip(const string clipname)
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
        bool isPublic(const string clipname)
        {
            if (!exists(clipname)) return;
            vector<string>::iterator it = find(publicLayers.begin(), publicLayers.end(), clipname);
            return it != publicLayers.end();
        }
        
        //---------------------------------------------------------------------------
        bool isPrivate(const string clipname)
        {
            if (!exists(clipname)) return;
            vector<string>::iterator it = find(privateLayers.begin(), privateLayers.end(), clipname);
            return it != privateLayers.end();
        }
        
        //---------------------------------------------------------------------------
        void saveImages(string clipname) // TODO: Save images
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            // see saveFrames(...)
            
        }
        
        //---------------------------------------------------------------------------
        void listAll()
        {
            ofLogNotice() << clips.size() << " available clips";
            for (const auto &item : clips) {  ofLogNotice() << "\t" << item.first; }
        }
        
        //---------------------------------------------------------------------------
        void listLayers()
        {
            string msg = "";
            for (const auto &item : publicLayers) {  msg += " : " + item; }
            ofLogNotice() << "Public layers: " << msg;
            msg = "";
            for (const auto &item : privateLayers) {  msg += " : " + item; }
            ofLogNotice() << "Private layers: " << msg;
        }
        
        //---------------------------------------------------------------------------
        void clearAll()
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
        }
        
        //---------------------------------------------------------------------------
        bool exists(string clipname)
        {
            bool b = clips.count(clipname);
            if (!b) ofLogVerbose() << __PRETTY_FUNCTION__ << "\tNo clip found: " << clipname;
            return b;
        }
        
        //---------------------------------------------------------------------------
        loopier::ClipPtr getClip(string clipname)
        {
            return clips.find(clipname)->second;
        }
        
        //---------------------------------------------------------------------------
        void toggleNames()
        {
            loopier::ClipMap::iterator it;
            for (it = clips.begin(); it != clips.end(); ++it) {
                (*it->second).toggleName();
            }
        }
        
        //---------------------------------------------------------------------------
        void showNames()
        {
            loopier::ClipMap::iterator it;
            for (it = clips.begin(); it != clips.end(); ++it) {
                (*it->second).showName();
            }
        }
        
        //---------------------------------------------------------------------------
        void hideNames()
        {
            loopier::ClipMap::iterator it;
            for (it = clips.begin(); it != clips.end(); ++it) {
                (*it->second).hideName();
                        }
        }
        
        //---------------------------------------------------------------------------
        void playClip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->play();
        }
        
        //---------------------------------------------------------------------------
        void stopClip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->stop();
        }
        
        //---------------------------------------------------------------------------
        void pauseClip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->pause();
        }
        
        //---------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------
        void setClipSpeed(const string clipname, const float speed)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setSpeed(speed);
        }
        
        //---------------------------------------------------------------------------
        void setClipLoopState(const string clipname, const loopier::LoopType state)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setLoopState(state);
        }
        
        //---------------------------------------------------------------------------
        void setClipMask(const string clipname, const string maskclipname)
        {
            if(!exists(clipname))       return;
            if(!exists(maskclipname))   return;
            clips[clipname]->setMask( clips[maskclipname]->getPlayer() );
        }
        
        //---------------------------------------------------------------------------
        void enableClipMask(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->maskOn();
        }
        
        //---------------------------------------------------------------------------
        void disableClipMask(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->maskOff();
        }
        
        //---------------------------------------------------------------------------
        //  EDIT
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        void setRecordingSource(const string clipname, const string sourceclip)
        {
            if(!exists(clipname) ||
               !exists(sourceclip)   ||
               !isFrameClip(clipname)) return;
            // cast from PlayerPtr to FramePlayerPtr -- note that
            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
            recplayer->setRecordingSourcePlayer(clips[sourceclip]->getPlayer());
            
            ofLogVerbose() << "Set '" << sourceclip <<"' as source for recording to '" << clipname << "'";
        }
        
        //---------------------------------------------------------------------------
        void addFrame(const string recorderclip, const string sourceclip)
        {
            // FIXME: OFFSET
            if(!exists(recorderclip) ||
               !exists(sourceclip)   ||
               !isFrameClip(recorderclip)) return;            
            // cast from PlayerPtr to FramePlayerPtr -- note that
            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
            ofImage img = clips[sourceclip]->getImage();
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
            
            clips[recorderclip]->setWidth(img.getWidth());
            clips[recorderclip]->setHeight(img.getHeight());
            clips[recorderclip]->setPosition(clips[sourceclip]->getPosition());
            recplayer->addFrame( img );
        }
        
        //---------------------------------------------------------------------------
        void insertFrame(const string recorderclip, const string sourceclip)
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
        void removeFrame(const string clipname)
        {
            if(!exists(clipname)) return;
            // cast from PlayerPtr to FramePlayerPtr -- note that
            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            FramePlayerPtr frameplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
            frameplayer->removeFrame();
            
            ofLogVerbose() << "Removing frame from '" << clipname <<"'";
        }
        
        //---------------------------------------------------------------------------
        void clearFrames(const string clipname)
        {
            if(!exists(clipname)) return;
            // cast from PlayerPtr to FramePlayerPtr -- note that
            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            FramePlayerPtr frameplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
            frameplayer->clear();
            
            ofLogVerbose() << "Clearing frames from '" << clipname <<"'";
        }
        
        //---------------------------------------------------------------------------
        void saveFrames(const string clipname)
        {
            if(!exists(clipname)) return;
            FramePlayerPtr frameplayer = getPlayerAsFramePlayer(clipname);
            FrameListPtr frames = frameplayer->getFrames();
            // get path from clipname
            string path = resourceFilesPath + "frames/" + clipname;
            ofDirectory dir(path);
            // create directory with clip's name if it doesn't exist
            if (!dir.exists()) dir.create();
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
        }
        
        //---------------------------------------------------------------------------
        void loadFrames(const string clipname, const string resourcename)
        {
//            if(!exists(clipname)) return;
            newClip(clipname, resourcename);
        }
        
        //---------------------------------------------------------------------------
        //
        //---------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------
        void resetClip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->reset();
        }
        
        //---------------------------------------------------------------------------
        //  MOVE CLIP
        //---------------------------------------------------------------------------
        void moveClipTo(const string clipname, const float x, const float y)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setPosition(x, y);
        }
        
        //---------------------------------------------------------------------------
        void centerClip(const string clipname)
        {
            if(!exists(clipname)) return;
//            moveClipTo(clipname, ofGetWidth() / 2, ofGetHeight() / 2);
            moveClipTo(clipname, 0.5, 0.5);
        }
        
        //---------------------------------------------------------------------------
        //  SCALE CLIP
        //---------------------------------------------------------------------------
        void scaleClip(const string clipname, const float scale)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setScale(scale);
        }
        
        //---------------------------------------------------------------------------
        void setClipWidth(const string clipname, const float width)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setScaleX(width);
        }
        
        //---------------------------------------------------------------------------
        void setClipHeight(const string clipname, const float height)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setScaleY(height);
        }
        
        //---------------------------------------------------------------------------
        void scaleUpClip(const string clipname, const float amount)
        {
            if(!exists(clipname)) return;
            ClipPtr clip = clips[clipname];
            clip->setScale( clip->getScale() + amount );
        }
        
        //---------------------------------------------------------------------------
        void scaleDownClip(const string clipname, const float amount)
        {
            if(!exists(clipname)) return;
            ClipPtr clip = clips[clipname];
            clip->setScale( clip->getScale() - amount );
        }
        
        //---------------------------------------------------------------------------
        void resetClipScale(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setScale(1.0);
        }
        
        //---------------------------------------------------------------------------
        void setClipVFlip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->flipV();
        }
        
        //---------------------------------------------------------------------------
        void setClipHFlip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->flipH();
        }
        
        //---------------------------------------------------------------------------
        //  FULSCREEN
        //---------------------------------------------------------------------------
        void toggleFullscreenClip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->toggleFullscreen();
        }
        
        //---------------------------------------------------------------------------
        //  VISIBILITY
        //---------------------------------------------------------------------------
        void toggleClipVisibility(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->toggleVisibility();
        }
        
        //---------------------------------------------------------------------------
        void showClip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->show();
        }
        
        //---------------------------------------------------------------------------
        void hideClip(const string clipname)
        {
            if(!exists(clipname)) return;
            clips[clipname]->hide();
        }
        
        //---------------------------------------------------------------------------
        //  COLOR
        //---------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------
        void setClipColor(const string clipname, const ofColor & color)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setColor(color);
        }
        
        //---------------------------------------------------------------------------
        void setClipColor(const string clipname, const float& grayscale)
        {
            if(!exists(clipname)) return;
            setClipColor(clipname, ofColor(grayscale * 255));
        }
        
        //---------------------------------------------------------------------------
        void setClipColor(const string clipname, const float& grayscale, const float& alpha)
        {
            if(!exists(clipname)) return;
            setClipColor(clipname, ofColor(grayscale * 255, alpha * 255));
        }
        
        //---------------------------------------------------------------------------
        void setClipColor(const string clipname, const float& r, const float& g, const float& b)
        {
            if(!exists(clipname)) return;
            setClipColor(clipname, ofColor(r * 255, g * 255, b * 255));
        }
        
        //---------------------------------------------------------------------------
        void setClipColor(const string clipname, const float& r, const float& g, const float& b, const float& a)
        {
            if(!exists(clipname)) return;
            setClipColor(clipname, ofColor(r * 255, g * 255, b * 255, a * 255));
        }
        
        //---------------------------------------------------------------------------
        void setClipAlpha(const string clipname, const float alpha)
        {
            if(!exists(clipname)) return;
            clips[clipname]->setAlpha(alpha * 255);
        }
    } // namespace clip
      // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    namespace cv {
        
        //---------------------------------------------------------------------------
        void setDeviceId(int deviceid)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
        }

        
        //---------------------------------------------------------------------------
        void setInputClip(string clipname)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            
            if (!clip::exists("cv")) return;
            CvPlayerPtr cvplayer = getPlayerAsCvPlayer("cv");
            cvplayer->setInputPlayer(getPlayerAsCameraPlayer(clipname));
        }
        
        //---------------------------------------------------------------------------
        void setColor(ofColor& color)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
//            clip::setClipColor("cv", color);
        }
        
        //---------------------------------------------------------------------------
        void toggleVisibility()
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
        }
        
        //---------------------------------------------------------------------------
        void show()
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            if (!clip::exists("cv")) return;
            clips["cv"]->show();
        }
        
        //---------------------------------------------------------------------------
        void hide()
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            if (!clip::exists("cv")) return;
            clips["cv"]->hide();
        }
        
        //---------------------------------------------------------------------------
        ofTexture & getMask()
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
        }
        
        //---------------------------------------------------------------------------
        ofTexture & getMaskTexture()
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
        }
        
        //---------------------------------------------------------------------------
        ofPixels & getMaskPixels()
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
        }
        
        //---------------------------------------------------------------------------
        void setMinArea(float newArea)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            if (!clip::exists("cv")) return;
            getPlayerAsCvPlayer("cv")->setMinArea(newArea);
        }
        
        //---------------------------------------------------------------------------
        void setMaxArea(float newArea)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            if (!clip::exists("cv")) return;
            getPlayerAsCvPlayer("cv")->setMaxArea(newArea);
        }
        
        //---------------------------------------------------------------------------
        void setThreshold(float newThreshold)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            if (!clip::exists("cv")) return;
            getPlayerAsCvPlayer("cv")->setThreshold(newThreshold);
        }
        
        //---------------------------------------------------------------------------
        void setFindHoles(bool findHoles)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            if (!clip::exists("cv")) return;
            getPlayerAsCvPlayer("cv")->setFindHoles(findHoles);
        }
        
        void setDetectionArea(ofRectangle & rect)
        {
            getPlayerAsCvPlayer("cv")->setDetectionArea(rect);
            detectionAreaRectangle = rect;
        }
        
        //---------------------------------------------------------------------------
    }   // namespace cv
    
    namespace utils {
        ofImage getMaskedImage(ofImage & img, ofTexture & mask){
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
        
        ofTexture getMaskedTexture(ofTexture & texture, ofTexture & mask){
            // if not using fbo, '.setAlphaMask(...)' is not permanent
            ofFbo fbo;
            fbo.allocate(texture.getWidth(), texture.getHeight(), GL_RGBA);
            texture.setAlphaMask(mask);
            fbo.begin();
            texture.draw(0,0);
            fbo.end();
            return fbo.getTexture();
        }
    } // namespace utils
}