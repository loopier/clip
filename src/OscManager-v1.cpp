//
//  OscManager.cpp
//  Teatrillu1
//
//  Created by roger on 10/04/2015.
//
//

// TODO: Add copyright (attribution to Glen)

#include "OscManager.h"

#include "ofMain.h"
#include "ofEvents.h"

loopier::OscManager::OscManager()
: listeningPort(54321)
, remoteIp("localhost")
, remotePort(57120) // supercollider lang port (sclang port)
{
    setupProcessMap();
    enableUpdateListener();
}

loopier::OscManager::OscManager(const int newListeningPort)
: listeningPort(newListeningPort)
, remoteIp("localhost")
, remotePort(57120) // supercollider lang port (sclang port)
{
    setupProcessMap();
    enableUpdateListener();
}

loopier::OscManager::OscManager(const int newListeningPort, const string& newRemoteIp, const int newRemotePort)
: listeningPort(newListeningPort)
, remoteIp(newRemoteIp)
, remotePort(newRemotePort)
{
    setupProcessMap();
    enableUpdateListener();
}

loopier::OscManager::~OscManager()
{
    ofAddListener(ofEvents().update, this, &eventsObject::update);
}

void loopier::OscManager::setupProcessMap()
{
//    processMap["/loopier/actor/create"] = &OscManager::actorCreate;
//    processMap["/loopier/asset/create"] = &OscManager::assetCreate;
    
    processMap["/loopier/clip/load"] = &OscManager::loadClip;
}

void loopier::OscManager::setup()
{
    ofLogVerbose() << "Setting up OSC...";

    oscReceiver.setup(listeningPort);
    oscSender.setup(remoteIp, remotePort); // FIXME: remote server configurable

    ofLogVerbose() << "Listening for OSC messages on port: " << listeningPort;
    ofLogVerbose() << "Sending OSC messages to " << remoteIp << ":" << remotePort;
    
    // custom event
    ofAddListener(ofEvents().update, this, &eventsObject::update);
}

void loopier::OscManager::setup(const int newListeningPort)
{
    setListeningPort(newListeningPort);
    setup();
}

void loopier::OscManager::setup(const int newListeningPort, const string& newRemoteIp, const int newRemotePort)
{
    setListeningPort(newListeningPort);
    setRemoteIp(newRemoteIp);
    setRemotePort(newRemotePort);
    setup();
}

void loopier::OscManager::setListeningPort(const int port)
{
    listeningPort = port;
}

void loopier::OscManager::setRemoteIp(const string& ip)
{
    remoteIp = ip;
}

void loopier::OscManager::setRemotePort(const int port)
{
    remotePort = port;
}

void loopier::OscManager::processMessages()
{
    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        printMessage(m);
        processMessage(m);
    }
}

void loopier::OscManager::sendMessage(const string& address, const string& arg)
{
    ofxOscMessage m;
    m.setAddress(address);
    m.addStringArg(arg);
    m.addFloatArg(ofGetElapsedTimef());
    oscSender.sendMessage(m);
}

void loopier::OscManager::processMessage(const ofxOscMessage& inMessage)
{
    // Look up the processor for this message address
    map<string, processFunc>::iterator iter = processMap.find(inMessage.getAddress());

    if (iter != processMap.end()) {
        // call the processor method for this message
        (this->*(iter->second))(inMessage);
    } else {
        ofLogWarning() << "Unhandled OSC message: " << inMessage.getAddress();
    }
}

void loopier::OscManager::printMessage(const ofxOscMessage& inMessage)
{
    string msgString;
    msgString = inMessage.getAddress();
    for (int i = 0; i < inMessage.getNumArgs(); i++) {
        msgString += " ";
        msgString += inMessage.getArgTypeName(i);
        msgString += ":";
        if (inMessage.getArgType(i) == OFXOSC_TYPE_INT32) {
            msgString += ofToString(inMessage.getArgAsInt32(i)) + " ";
        }
        else if (inMessage.getArgType(i) == OFXOSC_TYPE_FLOAT) {
            msgString += ofToString(inMessage.getArgAsFloat(i)) + " ";
        }
        else if (inMessage.getArgType(i) == OFXOSC_TYPE_STRING) {
            msgString += inMessage.getArgAsString(i) + " ";
        }
        else {
            msgString += "unknown ";
        }

        ofLogNotice() << "OSC Message received: " << msgString;
    }
}

void loopier::OscManager::updateEvent(ofEventArgs& e)
{
    processMessages();
}

void loopier::OscManager::enableUpdateListener()
{
    ofAddListener(ofEvents().update, this, &loopier::OscManager::updateEvent);
}

 // ------------- OSC MESSAGES -----------------
void loopier::OscManager::loadClip(const ofxOscMessage& inMessage)
{
    // !!! TODO: call Clip class somehow
    // check /Users/roger/Documents/openFrameworks/of_084/apps/teatrillu/Teatrillu/src
    ofLogVerbose() << "Load clip.  Needs calling Clip::load(path)";
}

//
//void loopier::OscManager::actorCreate(const ofxOscMessage &inMessage)
//{
//    string className(inMessage.getArgAsString(0));
//    string actorName(wu::getRandomWord());
//    string suffix = ofToString(loopier::actors.size());
//
//    string skinAssetName(actorName + "Skin-" + suffix);
//    loopier::SkinPtr skin = loopier::createSkinAssetFromFile(skinAssetName, "wu.png");
//
//    string posAssetName(actorName + "Position-" + suffix);
//    int x = ofRandom(ofGetWidth());
//    int y = ofRandom(ofGetHeight());
//    loopier::PositionPtr pos = loopier::createPositionAsset(posAssetName, x,y);
//
//    loopier::createActor(actorName, skin, pos);
//}
//
//void loopier::OscManager::assetCreate(const ofxOscMessage &inMessage)
//{
//    /// !!! TODO
//}
