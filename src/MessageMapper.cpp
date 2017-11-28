//
//  MessageMapper.cpp
//  clip
//
//  Created by roger on 28/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "MessageMapper.h"


//---------------------------------------------------------
//loopier::MessageMapper::MessageMapper()
//{
//    
//}
//
////---------------------------------------------------------
//loopier::MessageMapper::~MessageMapper()
//{
//    
//}

//---------------------------------------------------------
void loopier::MessageMapper::setup()
{
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &loopier::MessageMapper::mapMessageToFunc);
    setupMap();
    
    loopier::ConsoleUI::setup();
}

//---------------------------------------------------------
void loopier::MessageMapper::setupMap()
{
    // Application commands
    messageMap["/loopier/clip/quit"]        = &loopier::MessageMapper::quit;
    messageMap["/loopier/clip/fullscreen"]  = &loopier::MessageMapper::fullscreen;
    messageMap["/loopier/clip/move"]        = &loopier::MessageMapper::move;
    
    // One Clip commands
    messageMap["/loopier/clip/clip/new"]    = &loopier::MessageMapper::newClip;
    messageMap["/loopier/clip/clip/remove"] = &loopier::MessageMapper::removeClip;
    
    // Clip collection commands
    //  ...
    
    // Video input commands
    //  ...
    
    // Console commands
    //  ...
}


//---------------------------------------------------------
void loopier::MessageMapper::printMessage(Message & msg)
{
    loopier::printOscMessage(msg, "OSC:");
    loopier::ConsoleUI::print(loopier::getSimplifiedOscMessage(msg));
}

//---------------------------------------------------------
void loopier::MessageMapper::mapMessageToFunc(Message & msg)
{
    // Look up the processor for this message address
    map<string, mappedFunc>::iterator iter = messageMap.find(msg.getAddress());
    if (iter != messageMap.end()) {
        (this->*(iter->second))(msg); // call the processor method for this message
        printMessage(msg);
    }
    else {
        ofLogWarning() << "Unhandled OSC message: " << msg.getAddress();
    }
}

//---------------------------------------------------------








//---------------------------------------------------------

//        APPLICATION

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::quit(const Message & msg)
{
    ofExit();
}

//---------------------------------------------------------
void loopier::MessageMapper::fullscreen(const Message & msg)
{
    ofToggleFullscreen();
}

//---------------------------------------------------------
void loopier::MessageMapper::move(const Message & msg)
{
    ofSetFullscreen(false);
    float x = msg.getArgAsFloat(1) * ofGetScreenWidth();
    float y = msg.getArgAsFloat(2) * ofGetScreenHeight();
    ofSetWindowPosition(x, y);
}








//---------------------------------------------------------

//        ONE CLIP

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::newClip(const Message & msg)
{
    int n = msg.getNumArgs();
    if      (n == 1)    loopier::newClip(msg.getArgAsString(0));
    else if (n == 2)    loopier::newClip(msg.getArgAsString(0), msg.getArgAsString(1));
}


//---------------------------------------------------------
void loopier::MessageMapper::removeClip(const Message & msg)
{
    loopier::removeClip(msg.getArgAsString(0));
}