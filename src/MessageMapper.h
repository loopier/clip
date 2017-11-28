//
//  MessageMapper.h
//  clip
//
//  Created by roger on 28/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//
//  Maps OSC messages to application functions
//
//  From this class you remotely control all the application.
//  If you need to implement a new behaviour, add the osc message to
//      messageMap in setupMap() and a new method that makes what you need.

#ifndef _MessageMapper
#define _MessageMapper


#include "ofMain.h"
#include "OscManager.h"
#include "Clip.h"
#include "ConsoleUI.h"

namespace loopier {
    typedef ofxOscMessage Message;
    
class MessageMapper{
	
public:
//    MessageMapper();
//    virtual MessageMapper();
    
    void setup();
    void setupMap();
    
private:
    void printMessage(Message & msg);
    void mapMessageToFunc(Message & msg);
    
    typedef void (MessageMapper::* mappedFunc)(const Message&);
    
    void quit(const Message & msg);
    void fullscreen(const Message & msg);
    void move(const Message & msg);
    
    void newClip    (const Message & msg);
    void removeClip (const Message & msg);
    
    void clearClips         (const Message & msg);
    void listClipNames      (const Message & msg);
    void listResourceNames  (const Message & msg);
    void toggleClipNames    (const Message & msg);
    void showClipNames      (const Message & msg);
    void hideClipNames      (const Message & msg);
    
    map<string, mappedFunc> messageMap;
    OscManager              osc;
    
    ConsoleUI   console;
};
    
}

#endif