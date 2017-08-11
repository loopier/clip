//
//  OscManager.cpp
//  clip
//
//  Created by roger on 09/08/2017.
//
//

#include "OscManager.h"

OscManager::OscManager()
:listeningPort(12345)
{
}

OscManager::~OscManager()
{
    ofLogVerbose() << "OscManager destructed";
}

void OscManager::setup()
{
    ofLogVerbose() << "listening to port " << listeningPort;
    oscReceiver.setup(listeningPort);
    
    ofAddListener(ofEvents().setup, this, &OscManager::setup);
    ofAddListener(ofEvents().update, this, &OscManager::update);
    ofAddListener(ofEvents().draw, this, &OscManager::draw);
}

void OscManager::update()
{
    while(oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        string address = m.getAddress();
        
        printMsg(m);
    }
    
}

void OscManager::draw()
{
    
}

void OscManager::printMsg(ofxOscMessage& m)
{
    // unrecognized message: display on the bottom of the screen
    string msg_string;
    msg_string = m.getAddress();
    msg_string += ": ";
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg_string += m.getArgTypeName(i);
        msg_string += ":";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
        else{
            msg_string += "unknown";
        }
        msg_string += " ";
    }
    
    ofLogVerbose() << msg_string;

}