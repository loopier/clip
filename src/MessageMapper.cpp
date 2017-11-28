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
}

//---------------------------------------------------------
void loopier::MessageMapper::setupMap()
{
    messageMap["/loopier/clip/clip/new"] = &loopier::MessageMapper::newClip;
}


//---------------------------------------------------------
void loopier::MessageMapper::update()
{
    
}

//---------------------------------------------------------
void loopier::MessageMapper::mapMessageToFunc(Message & msg)
{
    ofLogVerbose() << __PRETTY_FUNCTION__ << " has not been implemented";
    // Look up the processor for this message address
    map<string, mappedFunc>::iterator iter = messageMap.find(msg.getAddress());
    if (iter != messageMap.end()) {
        (this->*(iter->second))(msg); // call the processor method for this message
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