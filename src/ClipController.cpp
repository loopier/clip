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
    loopier::CameraMap          cameras;    // cameras plugged
    
    vector<string>   drawingLayers; // used to control drawing order (depth)
    
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
            loopier::CameraPtr cam(new loopier::Camera());
            cam->setDeviceID(i);
//            cam->initGrabber(ofGetWidth(), ofGetHeight());
            // Get las word of the name
            string name = ofSplitString(devices[i].deviceName, " ").back();
            cameras[name] = cam;
            
            // create a player from this camera
            loopier::CameraPlayerPtr cameraplayer(new loopier::CameraPlayer(cam));
            cameraplayers[name + "-player"] = cameraplayer;
        }
        
        for (const auto &cam : cameras) cam.second->initGrabber(ofGetWidth(), ofGetHeight());
        
        ofLogVerbose() << "Loaded " << cameras.size() << " movie files";
    }
    
    //---------------------------------------------------------------------------
    loopier::ClipPtr initializeCv()
    {
        if (cameras.size() <= 0) return;    // needs to provide a camera to the cv player constructor
        
        // FIX: now sets first camera -- should set any camera.  Something like this:
        string cameraname = cameras.begin()->first;
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
        ofLogVerbose() << "Created cilp: [cv]\t'" << clipname << "' using '" <<cameraname << "'";
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
//                                 // now it collides with CvPlayer that uses it's own
//                                 // ofVideoGrabber because I couldn't make it
//                                 // work dynamically
//            initializeCv();
            clip::newClip("cv");
            loopier::resource::listAll();
        }
        
        //---------------------------------------------------------------------------
        void update()
        {
            // local helpers declared above in unnamed namespace
            for (const auto &item : clips) {
                clip::setClipDrawOrder(item.first, item.second->getDepth());
            };
        }
        
        //---------------------------------------------------------------------------
        void draw()
        {
            // local helpers declared above in unnamed namespace
            for (const auto &clipname : drawingLayers) {
                if (!clip::exists(clipname)) continue;
                clips.at(clipname)->draw();
            };
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
            ofLogNotice() << "Number of cameras loaded: " << cameras.size();
            for (const auto &item : cameras) {  ofLogNotice() << "\t" << item.first; }
            ofLogNotice() << "Number of cameras players loaded: " << cameraplayers.size();
            for (const auto &item : cameraplayers) {  ofLogNotice() << "\t" << item.first; }
        }
        
        //---------------------------------------------------------------------------
        bool exists(string resourcename)
        {
            if (frames.count(resourcename) ||
                movies.count(resourcename) ||
                cameras.count(resourcename)) return true;
            else return false;
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
            // if clip with this name exists -- change new clip's name to clipname + timestamp
//            if (exists(clipname)) clipname += ofGetTimestampString("%H%M%S%i");
            if (resourcename == "") resourcename = clipname;
            
            loopier::ClipPtr clip;
            if (exists(clipname)) {
                clip = getClip(clipname);
            } else {
                clip = make_shared<loopier::Clip>(clipname, resourcename);
                drawingLayers.push_back(clipname);
            }
            
            // !!!: Should change to something more kosher, like classes returning their types
            if (isFrameClip(clipname)) {
                frameclipslist.erase(std::remove(frameclipslist.begin(),
                                                frameclipslist.end(),
                                                clipname));
            }
            
            string cliptype = "";
            
            // look for a resource with this name
            // if it doesn't exist, create a new Empty FrameClip, so it can be saved later
            
            // movie
            if ( movies.count(resourcename) > 0) {
                loopier::MoviePlayerPtr movieplayer(new MoviePlayer(movies[resourcename]));
                clip->setup(movieplayer);
                cliptype = "movie";
            }
            // cv
            else if (resourcename == "cv") {
                loopier::CvPlayerPtr cvplayer(new loopier::CvPlayer());
                cvplayer->setCamera(*cameras["C525"]);
                clip->setup(cvplayer);
            }
            // camera
            else if ( cameras.count(resourcename) > 0) {
                loopier::CameraPlayerPtr cameraplayer(new CameraPlayer(cameras[resourcename]));
                clip->setup(cameraplayer);
                cameraplayers[resourcename + "-player"] = cameraplayer;
                cliptype = "camera";
            }
            
            // frame list
            else if (frames.count(resourcename) > 0) {
                loopier::FramePlayerPtr frameplayer(new FramePlayer(frames[resourcename]));
                clip->setup(frameplayer);
                frameclipslist.push_back(clipname);
                cliptype = "frame";
            }
            
            // doesn't exist -- create a frame clip with an empty framelist -- aka framerecorder
            else {
//                loopier::FrameListPtr emptyframelist(new loopier::FrameList());
//                loopier::FramePlayerPtr frameplayer(new FramePlayer(emptyframelist));
                // !!!: CLUMSY should pass an empty framelist as above (commented out) but
                //          it won't work when filled (doesn't draw in player)
                loopier::FramePlayerPtr frameplayer(new FramePlayer(frames.begin()->second));
                frameplayer->clear();

                clip->setup(frameplayer);
                frameclipslist.push_back(clipname);
                cliptype = "frame";
            }
            
//            clip->setDepth(0);
            clips[clipname] = clip;
            clip->show();
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
            if (position >= drawingLayers.size()) position = drawingLayers.size()-1;
            if (position < 0 ) position = 0;
            
            getClip(clipname)->setDepth(position);
            
            // remove from current position
            drawingLayers.erase(std::remove(drawingLayers.begin(),
                                       drawingLayers.end(),
                                       clipname));
            // add to new position
            drawingLayers.insert(drawingLayers.end() - position, clipname);
            listDrawOrder();
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
            setClipDrawOrder(clipname, drawingLayers.size() - 2);
        }
        
        //---------------------------------------------------------------------------
        void setBackgroundClip(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, drawingLayers.size() - 1);
        }
        
        // Frame
        
        
        // CV
        //---------------------------------------------------------------------------
        void setCvInput(string clipname)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            //            if (!exists("cv"))      return; // there's no cv clip -- TODO: change if there'd be
            
            ClipPtr cvclip = getClip("cv");
            
            //            CameraPlayerPtr inputplayer = cameraplayers.begin()->second;
            
            //                                            // other instances of cv clips
            //            if (!exists(clipname))  return;
            //            ClipPtr inputclip = getClip(clipname);
            //            // cast from PlayerPtr to CvPlayerPtr -- note that
            //            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            //            CvPlayerPtr cvplayer = dynamic_pointer_cast<CvPlayer> (getClip("cv")->getPlayer());
            //            cvplayer->setInputPlayer(inputclip->getPlayer());
            //            inputclip->hide(); // hides input clip
        }
        
        //---------------------------------------------------------------------------
        void setCvDeviceId(const int n)
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
        }
        
        //---------------------------------------------------------------------------
        void saveImages(string clipname) // TODO: Save images
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            // if directory 'clipname' exists, warn and change name to 'clipname_' + YYYYMMDD-HHMM
            //    ofGetTimestampString(%Y%m%d-%H%M)
            
        }
        
        //---------------------------------------------------------------------------
        void listAll()
        {
            ofLogNotice() << clips.size() << " available clips";
            for (const auto &item : clips) {  ofLogNotice() << "\t" << item.first; }
        }
        
        //---------------------------------------------------------------------------
        void listDrawOrder()
        {
            string msg = "";
            for (const auto &item : drawingLayers) {  msg += " : " + item; }
            
            ofLogNotice() << "Drawing order: " << msg;
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
            //            loopier::ClipMap::iterator it;
            //            for (it = loopier::clipmap.begin(); it != loopier::clipmap.end(); ++it) {
            //                (*it->second).toggleName();
            //            }
        }
        
        //---------------------------------------------------------------------------
        void showNames()
        {
            //            loopier::ClipMap::iterator it;
            //            for (it = loopier::clipmap.begin(); it != loopier::clipmap.end(); ++it) {
            //                (*it->second).showName();
            //            }
        }
        
        //---------------------------------------------------------------------------
        void hideNames()
        {
            //            loopier::ClipMap::iterator it;
            //            for (it = loopier::clipmap.begin(); it != loopier::clipmap.end(); ++it) {
            //                (*it->second).hideName();
            //            }
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
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setSpeed(speed);
        }
        
        //---------------------------------------------------------------------------
        void setClipLoopState(const string clipname, const loopier::LoopType state)
        {
//            if(!exists(clipname)) return;
//                        clips[clipname]->setLoopState(state);
        }
        
        //---------------------------------------------------------------------------
        void setClipMask(const string clipname, const string maskclipname)
        {
            if(!exists(clipname))       return;
            if(!exists(maskclipname))   return;
            clips[clipname]->setMask( clips[maskclipname]->getPlayer() );
            clips[maskclipname]->hide();
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
            if(!exists(recorderclip) ||
               !exists(sourceclip)   ||
               !isFrameClip(recorderclip)) return;
            // cast from PlayerPtr to FramePlayerPtr -- note that
            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
            recplayer->addFrame( clips[sourceclip]->getImage() );
            
            ofLogVerbose() << "Adding frame from '" << sourceclip <<"' to '" << recorderclip << "'";
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
            FramePlayerPtr frameplayer = dynamic_pointer_cast<FramePlayer> (clips[clipname]->getPlayer());
            FrameListPtr frames = frameplayer->getFrames();
            // get path from clipname
            string path = resourceFilesPath + "frames/" + clipname;
            // iterate frame list and save each file as 'clipname_xxx.png'
            
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
}