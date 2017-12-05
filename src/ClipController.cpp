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
    vector<string>                          frameplayerslist;
    
    // images
    vector<ofImage> framebuffer;    // temporary buffer to hold images to be saved
                                    // used by image saving functions
    
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
    
    bool    isFramePlayer(string name)
    {
        bool isit = false;
        vector<string>::iterator it;
        it = std::find(frameplayerslist.begin(), frameplayerslist.end(), name);
        if (it == frameplayerslist.end())   return false;
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
            
            loopier::ClipPtr clip;
            if (exists(clipname)) clip = getClip(clipname);
            else clip = make_shared<loopier::Clip>(clipname, resourcename);
            
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
                frameplayerslist.push_back(clipname);
                cliptype = "frame";
            }
            
            // doesn't exist -- create a frame clip with 'empty' (check frames folder)
            else {
                //                newClip(clipname, "empty");
                //                return;
            }
            
            clip->setDepth(0);
            clips[clipname] = clip;
            drawingLayers.push_back(clipname);
            ofLogVerbose() << "Created cilp: [" << cliptype << "]\t'" << clipname << "' using '" << resourcename << "'";
            return clip;
        }
        
        //---------------------------------------------------------------------------
        void removeClip(string clipname)
        {
            // FIX: CRASHES APP
//            if (!exists(clipname)) return;
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
            listDrawOrder();
        }
        
        //---------------------------------------------------------------------------
        void bringClipForward(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, getClip(clipname)->getDepth() - 1 );
            listDrawOrder();
        }
        
        //---------------------------------------------------------------------------
        void sendClipBackward(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, getClip(clipname)->getDepth() + 1 );
            listDrawOrder();
        }
        
        //---------------------------------------------------------------------------
        void sendClipToBack(string clipname)
        {
            if (!exists(clipname)) return;
            setClipDrawOrder(clipname, drawingLayers.size() );
            listDrawOrder();
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
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setLoopState(state);
        }
        
        //---------------------------------------------------------------------------
        void setClipMask(const string clipname, const string maskclipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            if(!loopier::clipExists(maskclipname)) return;
            //            loopier::clipmap[clipname]->setMask( loopier::getClipByName(maskclipname)->getPlayer() );
            //            loopier::getClipByName(maskclipname)->hide();
        }
        
        //---------------------------------------------------------------------------
        void enableClipMask(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->maskOn();
        }
        
        //---------------------------------------------------------------------------
        void disableClipMask(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->maskOff();
        }
        
        //---------------------------------------------------------------------------
        //  EDIT
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        void addFrame(const string recorderclip, const string sourceclip)
        {
            if(!exists(recorderclip) ||
               !exists(sourceclip)   ||
               !isFramePlayer(recorderclip)) return;
            // cast from PlayerPtr to FramePlayerPtr -- note that
            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
            recplayer->addFrame( clips[sourceclip]->getImage() );
            
            ofLogVerbose() << "Adding frame from '" << sourceclip <<"' to '" << recorderclip;
        }
        
        //---------------------------------------------------------------------------
        void insertFrame(const string recorderclip, const string sourceclip)
        {
            if(!exists(recorderclip) ||
               !exists(sourceclip)   ||
               !isFramePlayer(recorderclip)) return;
            // cast from PlayerPtr to FramePlayerPtr -- note that
            // dynamic_pointer_cast uses the class name, not the class pointer name (--Ptr)
            FramePlayerPtr recplayer = dynamic_pointer_cast<FramePlayer> (clips[recorderclip]->getPlayer());
            recplayer->insertFrame( clips[sourceclip]->getImage() );
            
            ofLogVerbose() << "Inserting frame from '" << sourceclip <<"' to '" << recorderclip;
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
            
            ofLogVerbose() << "Removing frame from '" << clipname <<"'";
        }
        
        //---------------------------------------------------------------------------
        //
        //---------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------
        void resetClip(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->reset();
        }
        
        //---------------------------------------------------------------------------
        //  MOVE CLIP
        //---------------------------------------------------------------------------
        void moveClipTo(const string clipname, const float x, const float y)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setPosition(x, y);
        }
        
        //---------------------------------------------------------------------------
        //  SCALE CLIP
        //---------------------------------------------------------------------------
        void scaleClip(const string clipname, const float scale)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setScale(scale);
        }
        
        //---------------------------------------------------------------------------
        void setClipWidth(const string clipname, const float width)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setScaleX(width);
        }
        
        //---------------------------------------------------------------------------
        void setClipHeight(const string clipname, const float height)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setScaleY(height);
        }
        
        //---------------------------------------------------------------------------
        void scaleUpClip(const string clipname, const float amount)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //
            //            ClipPtr clip = loopier::clipmap[clipname];
            //            clip->setScale( clip->getScale() + amount );
        }
        
        //---------------------------------------------------------------------------
        void scaleDownClip(const string clipname, const float amount)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //
            //            ClipPtr clip = loopier::clipmap[clipname];
            //            clip->setScale( clip->getScale() - amount );
        }
        
        //---------------------------------------------------------------------------
        void resetClipScale(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setScale(1.0);
        }
        
        //---------------------------------------------------------------------------
        void setClipVFlip(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->flipV();
        }
        
        //---------------------------------------------------------------------------
        void setClipHFlip(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->flipH();
        }
        
        //---------------------------------------------------------------------------
        //  FULSCREEN
        //---------------------------------------------------------------------------
        void toggleFullscreenClip(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->toggleFullscreen();
        }
        
        //---------------------------------------------------------------------------
        //  VISIBILITY
        //---------------------------------------------------------------------------
        void toggleClipVisibility(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->toggleVisibility();
        }
        
        //---------------------------------------------------------------------------
        void showClip(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->show();
        }
        
        //---------------------------------------------------------------------------
        void hideClip(const string clipname)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->hide();
        }
        
        //---------------------------------------------------------------------------
        //  COLOR
        //---------------------------------------------------------------------------
        void setClipColor(const string clipname, const string& color)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //
            //            vector<string> tokens = ofSplitString(color, ",", true, true);
            //
            //            ofColor c;
            //
            //            if (tokens.size() == 1) {
            //                c = ofColor(ofToFloat(tokens[0]) * 255);
            //            } else if (tokens.size() == 2) {
            //                c = ofColor(ofToFloat(tokens[0]) * 255);
            //                loopier::clipmap[clipname]->setAlpha(ofToFloat(tokens[1]));
            //            } else {
            //                c.r = ofToFloat(tokens[0]) * 255;
            //                c.g = ofToFloat(tokens[1]) * 255;
            //                c.b = ofToFloat(tokens[2]) * 255;
            //            }
            //            if (tokens.size() == 4) {
            //                loopier::clipmap[clipname]->setAlpha(ofToFloat(tokens[3]));
            //            }
            //            
            //            ofLogVerbose() << __PRETTY_FUNCTION__ << "\t" << c;
            //            
            //            loopier::clipmap[clipname]->setColor(c);
        }
        
        void setClipColor(const string clipname, const ofColor & color)
        {
            //            loopier::clipmap[clipname]->setColor(color);
        }
        
        void setClipColor(const string clipname, const float& grayscale)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            
            //            loopier::clipmap[clipname]->setColor(ofColor(grayscale * 255));
        }
        
        //---------------------------------------------------------------------------
        void setClipAlpha(const string clipname, const float alpha)
        {
            //            if(!loopier::clipExists(clipname)) return;
            //            loopier::clipmap[clipname]->setAlpha(alpha);
        }
    } // namespace clip
}