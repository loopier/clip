//
//  OscManager.cpp
//  clip
//
//  Created by roger on 11/08/2017.
//
//

#include "OscManager.h"


//------------------------------------------------------------------------------------------
//      CLASS
//------------------------------------------------------------------------------------------

loopier::OscManager::OscManager()
: listenPort(12345)
{
    ofLogVerbose() << __FUNCTION__ << ": Automatically listening to 'update' event";
    // automatically update without needing to call it from ofApp
    ofAddListener(ofEvents().update, this, &loopier::OscManager::update);
    
    counterfortest=0;
}

loopier::OscManager::~OscManager()
{
    ofRemoveListener(ofEvents().update, this, &loopier::OscManager::update);
    ofLogVerbose() << __FUNCTION__ << ": OscManager object destroyed";
}

void loopier::OscManager::setup()
{
    receiver.setup(listenPort);
    ofLogNotice() << "OSC listening on port " << listenPort;
}

void loopier::OscManager::update()
{
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        if (receiver.getNextMessage(m)) {
            // notify all the listeners about this message and send it to them
            ofNotifyEvent(newOscMessageEvent, m, this);
        }
        
    }
    
    
}

void loopier::OscManager::update(ofEventArgs& e)
{
    update();
}

void loopier::OscManager::listenToPort(const int port)
{
    listenPort = port;
    ofLogVerbose() << __FUNCTION__ << ": Now listening to port " << listenPort;
}

//------------------------------------------------------------------------------------------
//      INTERFACE FUNCTIONS
//------------------------------------------------------------------------------------------

void loopier::printOscMessage(const ofxOscMessage& m, const string& prepend, const ofLogLevel& loglevel)
{
    //    ofLogVerbose() << typeid(this).name() << "::" << __FUNCTION__;
    string msg = prepend + "\t";
    msg += loopier::getPrintableOscMessage(m);
    
    ofLogNotice() << msg;
}

string loopier::getPrintableOscMessage(const ofxOscMessage& m)
{
    string msg;
    msg = m.getAddress();
    msg += " \t";
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg += m.getArgTypeName(i);
        msg += ":";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg += m.getArgAsString(i);
        }
        else{
            msg += "unknown";
        }
        
        msg += "\t";
    }
    
    return msg;
}

string loopier::getSimplifiedOscMessage(const ofxOscMessage& m)
{
    string msg;
    msg = m.getAddress();
    msg += " \t";
    for(int i = 0; i < m.getNumArgs(); i++){
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
//            msg += "\"" + m.getArgAsString(i) + "\"";
            msg += m.getArgAsString(i);
        }
        else{
            msg += "unknown";
        }
        
        msg += " ";
    }
    
    return msg;
}

