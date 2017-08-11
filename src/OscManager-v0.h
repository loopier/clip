//
//  OscManager.hpp
//  clip
//
//  Created by roger on 09/08/2017.
//
//

#ifndef OscManager_h
#define OscManager_h

#include "ofMain.h"
#include "ofxOsc.h"

class OscManager {
    
public:
    OscManager();
    ~OscManager();
    
    // !!! TODO: make this methods automatic (that we don't need to explicitly call them - there's a way to do it, adding this class as an event listener somewhere)
    void setup();
    void update();
    void draw();
    
    // !!! TODO: add listeners that want to be notified when a message arrives
    
private:
    
    int listeningPort;
    ofxOscReceiver oscReceiver;
    
    /// print message to console
    void printMsg(ofxOscMessage& msg);
};

#endif /* OscManager_hpp */
