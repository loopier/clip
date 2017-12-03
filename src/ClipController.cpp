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
    loopier::ClipMap        clips; // all clips that have been created
    loopier::MovieMap       movies; // movies in resources folder
    loopier::FrameListMap   frames; // frame sequences in resources folder
    loopier::CameraMap      cameras;
    
    // images
    vector<ofImage> framebuffer;    // temporary buffer to hold images to be saved
    // used by image saving functions
    
    // * * * HELPER FUNCTIONS LOCAL TO THIS FILE * * * * * * * * * * * * * * * * * * * * *
    
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
        
        ofLogVerbose() << "* * * * * * * * * * * * * * * * \t" << movies.size();
        ofLogVerbose() << "Loaded " << movies.size() << " movie files";
    }
    
    void initializeCameras()
    {
        ofVideoGrabber vidGrabber;
        vector<ofVideoDevice> devices = vidGrabber.listDevices();
        
        for (int i = 0; i < devices.size(); i++) {
            loopier::CameraPtr cam(new loopier::Camera(vidGrabber));
            cam->setDeviceID(i);
            cam->initGrabber(ofGetWidth(), ofGetHeight());
            // Get las word of the name
            string name = ofSplitString(devices[i].deviceName, " ").back();
            cameras[name] = cam;
            ofLogVerbose() << "* * * * * * * * * * * * * * * * \t" << cameras.size();
        }
        
        ofLogVerbose() << "* * * * * * * * * * * * * * * * \t" << cameras.size();
        ofLogVerbose() << "Loaded " << cameras.size() << " movie files";
    }
} // namesapce


namespace loopier {
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    namespace app {
        
        void init()
        {
            loadFrameLists();
            loadMovies();
            initializeCameras();
            loopier::resource::listAll();
        }
    }   // namespace app
    
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    namespace resource {
        
        void setPath(const string path)
        {
            resourceFilesPath = path;
            ofLogVerbose() << "Resource files path: " << resourceFilesPath;
        }
        
        string & getPath()
        {
            return resourceFilesPath;
        }
        
        void listAll()
        {
            ofLogNotice() << "Number of frame lists loaded: " << frames.size();
            for (const auto &item : frames) {   ofLogNotice() << "\t" << item.first; }
            ofLogNotice() << "Number of movies loaded: " << movies.size();
            for (const auto &item : movies) {   ofLogNotice() << "\t" << item.first; }
            ofLogNotice() << "Number of cameras loaded: " << cameras.size();
            for (const auto &item : cameras) {  ofLogNotice() << "\t" << item.first; }
        }
        
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
        
        void newClip(string clipname)
        {
            newClip(clipname, clipname);
        }
        
        void newClip(string clipname, string resourcename)
        {
            // if clip with this name exists -- change new clip's name to clipname + timestamp
            if (clips.count(clipname) > 0) clipname += ofGetTimestampString("%H%M%S%i");
            loopier::ClipPtr clip(new loopier::Clip(clipname, resourcename));
            
            string logMsg = "New clip '" + clipname + "' of type: ";
            loopier::PlayerPtr player;
            // look for a resource with this name
            // if it doesn't exist, create a new Empty FrameClip, so it can be saved later
            if ( movies.count(resourcename) > 0) {
                player = make_shared<MoviePlayer>();
                logMsg += "movie";
            } else if ( cameras.count(resourcename) > 0) {
                loopier::CameraPlayerPtr cam(new CameraPlayer());
                cam->setCamera(cameras[resourcename]);
                player = cam;
                logMsg += "camera";
            } else { // if it's a FramePlayer or it doesn't exist create a FramePlayer
                player = make_shared<MoviePlayer>();
                logMsg += "frame";
            }
            // set clip's player
            clip->setPlayer(player);
            clip->setup();
            clips[clipname] = clip;
            ofLogVerbose() << "Creating cilp: " << clipname;
        }
        
        void saveImages(string clipname) // TODO: Save images
        {
            ofLogVerbose() << __PRETTY_FUNCTION__ << " needs implementation";
            // if directory 'clipname' exists, warn and change name to 'clipname_' + YYYYMMDD-HHMM
            //    ofGetTimestampString(%Y%m%d-%H%M)
        }
        
        void listAll()
        {
            ofLogNotice() << clips.size() << " available clips";
            for (const auto &item : clips) {  ofLogNotice() << "\t" << item.first; }
//            ofLogNotice() << clips.begin()->first;
        }
    } // namespace clip
}