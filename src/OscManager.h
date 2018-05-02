//
//  OscManager.hpp
//  clip
//
//  Created by roger on 11/08/2017.
//
//

#ifndef OscManager_h
#define OscManager_h

#include "ofxOsc.h"
#include "ofEvents.h"
#include "ofMain.h"


namespace loopier {
    namespace osc {
    class OscManager
    {
    public:
        OscManager();
        ~OscManager();
        
        void setup();
        void update();
        
        void listenToPort(const int port);
        void sendMessage(ofxOscMessage& m);
        
        ofEvent<ofxOscMessage> newOscMessageEvent;
        
    private:        
        /// \brief Automatic update method
        /// \description    This class is subscribed to ofEvents().update so
        ///     it updates automatically with the app.  There's no need to call
        ///     update() from ofApp::update()
        void update(ofEventArgs& e);
        
        int listenPort;
        string remoteIp;
        int remotePort;
        
        ofxOscReceiver receiver;
        ofxOscSender    sender;
        float counterfortest;
        
    };
    
    /// \brief Print OSC message
    /// \param  m           ofxOscMessage   Message to print
    /// \param  prepend     String          Something to write before the
    ///                                     message address (e.g. who's asking
    ///                                     to print it)
    void printMessage(const ofxOscMessage& m, const string& prepend="", const ofLogLevel& loglevel=OF_LOG_NOTICE);
    string getPrintableMessage(const ofxOscMessage& m);
    string getSimplifiedMessage(const ofxOscMessage& m);
    } // namespace osc
} // namespace loopier

#endif /* OscManager_hpp */
