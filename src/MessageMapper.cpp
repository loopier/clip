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
    messageMap["/loopier/clip/clip/new"]    = &loopier::MessageMapper::newClip;
    messageMap["/loopier/clip/clip/remove"] = &loopier::MessageMapper::removeClip;
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