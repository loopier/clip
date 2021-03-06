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
#include "Uvc.h"

namespace loopier {
    namespace osc {
        typedef ofxOscMessage Message;
        
        class MessageMapper{
            
        public:
            //    MessageMapper();
            //    virtual MessageMapper();
            
            void setup();
            void setupAppCommandsMap();
            void setupClipCommandsMap();
            void setupClipCollectionCommandsMap();
            void setupSyphonCommandsMap();
            void setupCvCommandsMap();
            void setupConsoleCommandsMap();
            void setupUvcCommandsMap();
            
        private:
            void printMessage(Message & msg);
            void mapMessageToFunc(Message & msg);
            /// \brief  Replaces any message address with '.../selection...' to '.../clip...'
            /// \description    This way all messages mapped to '/clip clipname' can be
            ///                 reused without haveing to retype them.
            void fromSelectionToClip(Message & msg);
            
            typedef void (MessageMapper::* mappedFunc)(const Message&);
            
            // FIX: REMOVE!!!
            // TEST
            void test (const Message & msg);
            // -- END REMOVE --
            
            // Application commands
            void quit       (const Message & msg);
            void fullscreen (const Message & msg);
            void move       (const Message & msg);
            void loadResources      (const Message & msg);
            void clearResources     (const Message & msg);
            void loadKeymap         (const Message & msg);
            void loadScriptFile     (const Message & msg);
            void loadAllScripts     (const Message & msg);
            void clearScriptList    (const Message & msg);
            void runScript          (const Message & msg);
            void loadAndRunScript   (const Message & msg);
            void listScriptNames    (const Message & msg);
            
            // One Clip commands
            void newClip              (const Message & msg);
            void newClipFromBlob      (const Message & msg);
            void removeClip           (const Message & msg);
            void resetClip            (const Message & msg);
            void selectClip           (const Message & msg);
            void deselectClip         (const Message & msg);
            void selectNextClip       (const Message & msg);
            void selectAllClips     (const Message & msg);
            void deselectAllClips   (const Message & msg);
            void listClipInfo       (const Message & msg);
            // parent
            void addClipChild           (const Message & msg);
            void removeClipChild        (const Message & msg);
            void clearClipChildren      (const Message & msg);
            void listClipChildren       (const Message & msg);
            // arrange
            void setClipDrawOrder       (const Message & msg);
            void bringClipForward       (const Message & msg);
            void bringClipToFront       (const Message & msg);
            void sendClipBackward       (const Message & msg);
            void sendClipToBack         (const Message & msg);
            void setBackgroundClip      (const Message & msg);
            void setPublicClip          (const Message & msg);
            void setPrivateClip         (const Message & msg);
            void listLayers             (const Message & msg);
            // size
            void scaleUpClip          (const Message & msg);
            void scaleDownClip        (const Message & msg);
            void scaleClip            (const Message & msg);
            void setClipWidth         (const Message & msg);
            void setClipHeight        (const Message & msg);
            void resetClipScale       (const Message & msg);
            void toggleFullscreenClip (const Message & msg);
            // orientation
            void setClipVFlip         (const Message & msg);
            void setClipHFlip         (const Message & msg);
            // visibility
            void toggleClipVisibility (const Message & msg);
            void showClip             (const Message & msg);
            void hideClip             (const Message & msg);
            // name
            void toggleClipName (const Message & msg);
            void showClipName   (const Message & msg);
            void hideClipName   (const Message & msg);
            // fx
            void setClipMask          (const Message & msg);
            void enableClipMask       (const Message & msg);
            void disableClipMask      (const Message & msg);
            void setClipHolesMask     (const Message & msg);
            // play
            void playClip               (const Message & msg);
            void stopClip               (const Message & msg);
            void pauseClip              (const Message & msg);
            void setClipLoopState       (const Message & msg);
            void setClipPlayDirection   (const Message & msg);
            void setClipSpeed           (const Message & msg);
            // edit
            void addFrame         (const Message & msg);
            void insertFrame      (const Message & msg);
            void removeFrame      (const Message & msg);
            void clearFrames      (const Message & msg);
            void saveFrames       (const Message & msg);
            void loadFrames       (const Message & msg);
            void firstFrame       (const Message & msg);
            void nextFrame        (const Message & msg);
            void previousFrame    (const Message & msg);
            void lastFrame        (const Message & msg);
            void goToFrame        (const Message & msg);
            void saveClip         (const Message & msg);
            // move
            void moveClipTo   (const Message & msg);
            void centerClip   (const Message & msg);
            // color
            void setClipColor (const Message & msg);
            void setClipAlpha (const Message & msg);
            
            // Clip collection commands
            void loadClipLibrary    (const Message & msg);
            void clearClips         (const Message & msg);
            void listClipNames      (const Message & msg);
            void listResourceNames  (const Message & msg);
            void listCameraNames    (const Message & msg);
            void listClipLibraryNames   (const Message & msg);
            void toggleClipNames    (const Message & msg);
            void showClipNames      (const Message & msg);
            void hideClipNames      (const Message & msg);
            
            // Syphon
            void setSyphonServerName    (const Message & msg);
            
            // Cv commands
            void setCvColor         (const Message & msg);
            void setCvThreshold     (const Message & msg);
            void setCvMinArea       (const Message & msg);
            void setCvMaxArea       (const Message & msg);
            void setCvHoles         (const Message & msg);
            void setCvHolesMask     (const Message & msg);
            void setCvMaxBlobs      (const Message & msg);
            void setCvInputClip     (const Message & msg);
            void setCvDeviceId      (const Message & msg);
            void toggleCvVisibility (const Message & msg);
            void showCv             (const Message & msg);
            void hideCv             (const Message & msg);
            void setCvDetectionArea (const Message & msg);
            void selectBlob         (const Message & msg);
            void deselectBlob       (const Message & msg);
            void selectAllBlobs     (const Message & msg);
            void deselectAllBlobs   (const Message & msg);
            void firstBlob          (const Message & msg);
            void nextBlob           (const Message & msg);
            void previousBlob       (const Message & msg);
            void lastBlob           (const Message & msg);
            
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
            
            // UVC
            void addUvcCamera       (const Message & msg);
            void useUvcCamera       (const Message & msg);
            void setUvcAutoExposure (const Message & msg);
            void setUvcExposure     (const Message & msg);
            void setUvcAutoFocus    (const Message & msg);
            void setUvcFocus        (const Message & msg);
            void setUvcAutoWhiteBalance (const Message & msg);
            void setUvcWhiteBalance (const Message & msg);
            void setUvcGain         (const Message & msg);
            void setUvcBrightness   (const Message & msg);
            void setUvcContrast     (const Message & msg);
            void setUvcSaturation   (const Message & msg);
            void setUvcSharpness    (const Message & msg);
            
            
            //------------------------------------------------------------------------------------------
            // SENDER METHODS
            
            void sendClipNames();
            void sendResourceNames();
            void sendCameraNames();
            void sendLibraryNames();
            void sendClipInfo(const string clipname);
            void sendScriptNames();
            void sendClipChildrenNames(const string clipname);
            
            //------------------------------------------------------------------------------------------
            // COMMANDS FROM FILES
            
            // Helpers
            /// \brief  Translates a message with variable arguments to a color object
            static ofColor getColorFromMessage(const Message & msg);
            
            map<string, mappedFunc> messageMap;
            osc::OscManager         osc;
            
            ConsoleUI   console;
        };
    } // namespace osc
    
} // namespace loopeir

#endif
