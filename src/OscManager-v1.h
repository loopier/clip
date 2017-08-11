//
//  OscManager.h
//  Teatrillu1
//
//  Created by roger on 10/04/2015.
//
//

#ifndef __Teatrillu__OscManager__
#define __Teatrillu__OscManager__

#include "ofxOsc.h"

// Forward declarations
class ofxOscMessage;

namespace loopier
{
    class OscManager {
    public:
        OscManager();
        OscManager(const int newListeningPort);
        OscManager(const int newListeningPort, const string& newRemoteIp, const int newRemotePort);
        ~OscManager();
        void setup();
        void setup(const int newListeningPort);
        void setup(const int newListeningPort, const string& newRemoteIp, const int newRemotePort);
        void setListeningPort(const int port);
        void setRemoteIp(const string& ip);
        void setRemotePort(const int port);

        /// \brief Sends an OSC message with a single string argument
        void sendMessage(const string& address, const string& arg);

    private:
        typedef void (OscManager::* processFunc)(const ofxOscMessage&);

        map<string, processFunc>    processMap;

        int     listeningPort;
        string  remoteIp;
        int     remotePort;
        ofxOscReceiver oscReceiver;
        ofxOscSender oscSender;

//        OscManager(); // Disable default constructor
        OscManager(const OscManager &); // Disable copy constructor
        OscManager& operator=( const OscManager& rhs); // Disable default assignment operator

        void setupProcessMap();

        void processMessages();
        void processMessage(const ofxOscMessage& inMessage);
        void printMessage(const ofxOscMessage& inMessage);
        
        // ofApp::update() automatically calls updateEvent.  No need to call it explicitly
        void updateEvent(ofEventArgs& e);
        void enableUpdateListener();
        
        
        // ------------- OSC MESSAGES -----------------
        void loadClip(const ofxOscMessage& inMessage);
//
//        void actorCreate(const ofxOscMessage& inMessage);
//        void assetCreate(const ofxOscMessage& inMessage);
//


    };
}

#endif /* defined(__Teatrillu1__OscManager__) */
