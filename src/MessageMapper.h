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
#include "ClipController.h"
#include "Clip.h"
#include "Cv.h"
#include "ConsoleUI.h"
#include "Types.h"

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

    // Application commands
    void quit       (const Message & msg);
    void fullscreen (const Message & msg);
    void move       (const Message & msg);

    // One Clip commands
    void newClip              (const Message & msg);
    void removeClip           (const Message & msg);
    void resetClip            (const Message & msg);
    void setClipDrawOrder     (const Message & msg);
    void bringClipForward     (const Message & msg);
    void bringClipToFront     (const Message & msg);
    void sendClipBackward     (const Message & msg);
    void sendClipToBack       (const Message & msg);
    void scaleUpClip          (const Message & msg);
    void scaleDownClip        (const Message & msg);
    void scaleClip            (const Message & msg);
    void setClipWidth         (const Message & msg);
    void setClipHeight        (const Message & msg);
    void resetClipScale       (const Message & msg);
    void setClipVFlip         (const Message & msg);
    void setClipHFlip         (const Message & msg);
    void toggleFullscreenClip (const Message & msg);
    void toggleClipVisibility (const Message & msg);
    void showClip             (const Message & msg);
    void hideClip             (const Message & msg);
    void setClipMask          (const Message & msg);
    void enableClipMask       (const Message & msg);
    void disableClipMask      (const Message & msg);
    // play
    void playClip         (const Message & msg);
    void stopClip         (const Message & msg);
    void pauseClip        (const Message & msg);
    void setClipLoopState (const Message & msg);
    void setClipSpeed     (const Message & msg);
    // edit
    void addFrame         (const Message & msg);
    void insertFrame      (const Message & msg);
    void removeFrame      (const Message & msg);
    void clearFrames      (const Message & msg);
    
    // attributes
    void moveClipTo   (const Message & msg);
    void setClipColor (const Message & msg);
    void setClipAlpha (const Message & msg);

    // Clip collection commands
    void clearClips         (const Message & msg);
    void listClipNames      (const Message & msg);
    void listResourceNames  (const Message & msg);
    void toggleClipNames    (const Message & msg);
    void showClipNames      (const Message & msg);
    void hideClipNames      (const Message & msg);
    
    // Cv commands
    void setCvThreshold     (const Message & msg);
    void setCvMinArea       (const Message & msg);
    void setCvMaxArea       (const Message & msg);
    void setCvHoles         (const Message & msg);
    void setCvInputClip     (const Message & msg);
    void setCvDeviceId      (const Message & msg);
    
    // Console commands
    void setConsoleColor    (const Message & msg);
    void setConsoleAlpha    (const Message & msg);
    void setConsolePrompt   (const Message & msg);
    void printToConsole     (const Message & msg);
    void setConsoleLinesNum (const Message & msg);
    void toggleConsole      (const Message & msg);
    void showConsole        (const Message & msg);
    void hideConsole        (const Message & msg);
    void moveConsole        (const Message & msg);
    void setConsoleFont     (const Message & msg);
    void setConsoleFontSize (const Message & msg);
    
    // Helpers
    /// \brief  Translates a message with variable arguments to a color object
    static ofColor getColorFromMessage(const Message & msg);

    map<string, mappedFunc> messageMap;
    OscManager              osc;

    ConsoleUI   console;
};

}

#endif
