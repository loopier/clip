//
//  ResourceManager.h
//  clip
//
//  Created by roger on 21/06/2018.
//
//  Manage resources like images, movies, ...

#ifndef ResourceManager_h
#define ResourceManager_h

#include "ofMain.h"
#include "Types.h"

namespace loopier {
    class ResourceManager {
    public:
        static ResourceManager * getInstance();
        /// \brief   Lists all available resources
        void    setResourcePath(string path);
        string& getResourcePath();
        void    listAllResources();
        void    listCameras();
        /// \brief  Load a resource
        void    loadResource(const string & namresourcename);
        /// \brief  Load a list of resources.  Load all if no list is provided
        void    loadResources(const vector<string> resourcenames = vector<string>());
        void    loadAllResources();
        /// \brief Delete all resources
        void    clearResourceList();
        void    loadFrameList(const string & name);
        void    loadMovie(const string & name);
        /// \brief  Returns a list of the names of all resources
        vector<string> getResourceNames();
        /// \brief  Returns a list of the names of all cameras
        vector<string> getCameraNames();
        /// \brief   Checks if a resource exists
        bool    exists(string resourcename);
        /// \brief   Sets the syphon player of the given clip to listen to the given syphon server
        /// \param   clipname            String      Name of the clip showing the syphon input
        /// \param   syphonservername    String      Name of the syphon server
        /// \param   syphonserverapp     String      Name of the app hosting the syphon server
        void    setSyphonServerName(const string clipname, const string syphonservername, const string syphonserverapp);
        
    private:
        ResourceManager() {};
        ResourceManager(ResourceManager const&);
        void operator=(ResourceManager const&);
        
        static ResourceManager * instance;
        
        string filesPath;
        MovieMap        movies;
        FrameListMap    frames;
    };
}

#endif /* ResourceManager_h */
