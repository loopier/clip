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
    class OscManager
    {
    public:
        OscManager();
        ~OscManager();
        
        void setup();
        void update();
        
        void listenToPort(const int port);
        
        ofEvent<ofxOscMessage> newOscMessageEvent;
        
    private:
        int listenPort;
        
        ofxOscReceiver receiver;
        float counterfortest;
        
        /// \brief Automatic update method
        /// \description    This class is subscribed to ofEvents().update so
        ///     it updates automatically with the app.  There's no need to call
        ///     update() from ofApp::update()
        void update(ofEventArgs& e);
        
    };
    
    /// \brief Print OSC message
    /// \param  m           ofxOscMessage   Message to print
    /// \param  prepend     String          Something to write before the
    ///                                     message address (e.g. who's asking
    ///                                     to print it)
    void printOscMessage(const ofxOscMessage& m, const string& prepend="", const ofLogLevel& loglevel=OF_LOG_NOTICE);
    string getPrintableOscMessage(const ofxOscMessage& m);
}

#endif /* OscManager_hpp */
