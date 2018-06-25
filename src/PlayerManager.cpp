//
//  PlayerManager.cpp
//  clip
//
//  Created by roger on 25/06/2018.
//
//

#include "PlayerManager.h"

loopier::PlayerManager* loopier::PlayerManager::instance = 0;
loopier::PlayerManager * loopier::PlayerManager::getInstance()
{
    if(!instance) {
        instance = new PlayerManager();
        ofLogVerbose() << __PRETTY_FUNCTION__ << ": First instance\n";
        return instance;
    }
    else {
        ofLogVerbose() << __PRETTY_FUNCTION__ << ": previous instance\n";
        return instance;
    }
}

//---------------------------------------------------------------------------
void loopier::PlayerManager::setup()
{
    resourceManager = loopier::ResourceManager::getInstance();
    
    players["cameras"];
    players["frames"];
    players["movies"];
    players["cv"];
    players["syphon"];
    players["text"];
    
    
}

//---------------------------------------------------------------------------
template<typename T>
T loopier::PlayerManager::createPlayer(string & resourcename)
{
    
}