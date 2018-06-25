//
//  PlayerManager.h
//  clip
//
//  Created by roger on 25/06/2018.
//
//  Manage players

#ifndef PlayerManager_h
#define PlayerManager_h

#include "BasePlayer.h"
#include "CameraPlayer.h"
#include "MoviePlayer.h"
#include "FramePlayer.h"
#include "CvPlayer.h"
#include "SyphonPlayer.h"
//#include "TextPlayer.h"

#include "ResourceManager.h"

namespace loopier {
    class PlayerManager
    {
    public:
        static PlayerManager * getInstance() ;
        ~PlayerManager(){ if (!instance) delete instance;};
        
        template<typename T>
        static T createPlayer(string & resourcename);
//        static CameraPlayerPtr createCameraPlayer();
//        static MoviePlayerPtr createMoviePlayer();
//        static FramePlayerPtr createFramePlayer();
//        static CvPlayerPtr createCvPlayer();
//        static SyphonPlayerPtr createSyphonPlayer();
        
        /// \brief  Initialize resources
        void setup();
        
    private:
        PlayerManager() {  setup(); };
        PlayerManager(PlayerManager const&);
        void operator=(PlayerManager const&);
        
        static PlayerManager * instance;
        
        map<string, PlayerMap> players;
        
        ResourceManager* resourceManager;
        
        void addPlayer(string & playername);
        void removePlayer(string & playername);
        
    };
}

#endif /* PlayerManager_hpp */
