//
//  MessageMapper.cpp
//  clip
//
//  Created by roger on 28/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "MessageMapper.h"

namespace loopier {
    namespace osc {
        
        //---------------------------------------------------------
        void MessageMapper::setup()
        {
            osc.setup();
            ofAddListener(osc.newOscMessageEvent, this, &MessageMapper::mapMessageToFunc);
            setupAppCommandsMap();
            setupClipCommandsMap();
            setupClipCollectionCommandsMap();
            setupSyphonCommandsMap();
            setupCvCommandsMap();
            setupConsoleCommandsMap();
            setupUvcCommandsMap();
            
            ConsoleUI::setup();
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setupAppCommandsMap()
        {
            // Application commands
            messageMap["/loopier/clip/app/test"]       = &MessageMapper::test;
            
            // Application commands
            messageMap["/loopier/clip/app/quit"]        = &MessageMapper::quit;
            messageMap["/loopier/clip/app/fullscreen"]  = &MessageMapper::fullscreen;
            messageMap["/loopier/clip/app/move"]        = &MessageMapper::move;
            
            messageMap["/loopier/clip/app/loadresource"]        = &MessageMapper::loadResources;
            messageMap["/loopier/clip/app/loadresources"]        = &MessageMapper::loadResources;
            messageMap["/loopier/clip/app/clearresources"]       = &MessageMapper::clearResources;
            
            messageMap["/loopier/clip/script/load"]     = &MessageMapper::loadScriptFile;
            messageMap["/loopier/clip/script/listnames"]   = &MessageMapper::listScriptNames;
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setupClipCommandsMap()
        {
            
            // One Clip commands
            messageMap["/loopier/clip/clip/new"]                = &MessageMapper::newClip;
            // TODO: should replace clip, not resource
            messageMap["/loopier/clip/clip/replace"]            = &MessageMapper::newClip;
            messageMap["/loopier/clip/clip/replaceblob"]        = &MessageMapper::newClipFromBlob;
            messageMap["/loopier/clip/clip/remove"]             = &MessageMapper::removeClip;
            messageMap["/loopier/clip/clip/reset"]              = &MessageMapper::resetClip;
            messageMap["/loopier/clip/clip/select"]             = &MessageMapper::selectClip;
            messageMap["/loopier/clip/clip/deselect"]           = &MessageMapper::deselectClip;
            messageMap["/loopier/clip/clip/selectall"]          = &MessageMapper::selectAllClips;
            messageMap["/loopier/clip/clip/deselectall"]        = &MessageMapper::deselectAllClips;
            messageMap["/loopier/clip/clip/listinfo"]           = &MessageMapper::listClipInfo;
            // parent
            messageMap["/loopier/clip/clip/parent"]         = &MessageMapper::setParent;
            messageMap["/loopier/clip/clip/removeparent"]   = &MessageMapper::removeParent;
            messageMap["/loopier/clip/clip/offset"]         = &MessageMapper::setOffset;
            // Arrange
            messageMap["/loopier/clip/clip/depth"]          = &MessageMapper::setClipDrawOrder;
            messageMap["/loopier/clip/clip/front"]          = &MessageMapper::bringClipToFront;
            messageMap["/loopier/clip/clip/forward"]        = &MessageMapper::bringClipForward;
            messageMap["/loopier/clip/clip/backward"]       = &MessageMapper::sendClipBackward;
            messageMap["/loopier/clip/clip/back"]           = &MessageMapper::sendClipToBack;
            messageMap["/loopier/clip/clip/background"]     = &MessageMapper::setBackgroundClip;
            messageMap["/loopier/clip/clip/public"]         = &MessageMapper::setPublicClip;
            messageMap["/loopier/clip/clip/private"]        = &MessageMapper::setPrivateClip;
            // TODO: Move to ../app/.. or ../clips/..
            messageMap["/loopier/clip/clip/layers"]         = &MessageMapper::listLayers;
            // Size
            messageMap["/loopier/clip/clip/scaleup"]            = &MessageMapper::scaleUpClip;
            messageMap["/loopier/clip/clip/scaledown"]          = &MessageMapper::scaleDownClip;
            messageMap["/loopier/clip/clip/scale"]              = &MessageMapper::scaleClip;
            messageMap["/loopier/clip/clip/xscale"]             = &MessageMapper::setClipWidth;
            messageMap["/loopier/clip/clip/yscale"]             = &MessageMapper::setClipHeight;
            messageMap["/loopier/clip/clip/resetscale"]         = &MessageMapper::resetClipScale;
            messageMap["/loopier/clip/clip/fullscreen"]         = &MessageMapper::toggleFullscreenClip;
            // Orientation
            messageMap["/loopier/clip/clip/flipv"]              = &MessageMapper::setClipVFlip;
            messageMap["/loopier/clip/clip/fliph"]              = &MessageMapper::setClipHFlip;
            // Visibility
            messageMap["/loopier/clip/clip/togglevisibility"]   = &MessageMapper::toggleClipVisibility;
            messageMap["/loopier/clip/clip/show"]               = &MessageMapper::showClip;
            messageMap["/loopier/clip/clip/hide"]               = &MessageMapper::hideClip;
            // Visibility
            messageMap["/loopier/clip/clip/togglename"]   = &MessageMapper::toggleClipName;
            messageMap["/loopier/clip/clip/showname"]               = &MessageMapper::showClipName;
            messageMap["/loopier/clip/clip/hidename"]               = &MessageMapper::hideClipName;
            // FX
            messageMap["/loopier/clip/clip/mask"]               = &MessageMapper::setClipMask;
            messageMap["/loopier/clip/clip/maskon"]             = &MessageMapper::enableClipMask;
            messageMap["/loopier/clip/clip/maskoff"]            = &MessageMapper::disableClipMask;
            // play
            messageMap["/loopier/clip/clip/play"]           = &MessageMapper::playClip;
            messageMap["/loopier/clip/clip/stop"]           = &MessageMapper::stopClip;
            messageMap["/loopier/clip/clip/pause"]          = &MessageMapper::pauseClip;
            messageMap["/loopier/clip/clip/loop"]           = &MessageMapper::setClipLoopState;
            messageMap["/loopier/clip/clip/playdirection"]  = &MessageMapper::setClipPlayDirection;
            messageMap["/loopier/clip/clip/speed"]          = &MessageMapper::setClipSpeed;
            // edit
            messageMap["/loopier/clip/clip/addframe"]           = &MessageMapper::addFrame;
            messageMap["/loopier/clip/clip/insertframe"]        = &MessageMapper::insertFrame;
            messageMap["/loopier/clip/clip/removeframe"]        = &MessageMapper::removeFrame;
            messageMap["/loopier/clip/clip/clearframes"]        = &MessageMapper::clearFrames;
            messageMap["/loopier/clip/clip/saveframes"]         = &MessageMapper::saveFrames;
            messageMap["/loopier/clip/clip/loadframes"]         = &MessageMapper::loadFrames;
            messageMap["/loopier/clip/clip/firstframe"]         = &MessageMapper::firstFrame;
            messageMap["/loopier/clip/clip/nextframe"]          = &MessageMapper::nextFrame;
            messageMap["/loopier/clip/clip/previousframe"]      = &MessageMapper::previousFrame;
            messageMap["/loopier/clip/clip/lastframe"]          = &MessageMapper::lastFrame;
            messageMap["/loopier/clip/clip/gotoframe"]          = &MessageMapper::goToFrame;
            messageMap["/loopier/clip/clip/save"]               = &MessageMapper::saveClip;
            // move
            messageMap["/loopier/clip/clip/moveto"] = &MessageMapper::moveClipTo;
            messageMap["/loopier/clip/clip/center"] = &MessageMapper::centerClip;
            // color
            messageMap["/loopier/clip/clip/color"]  = &MessageMapper::setClipColor;
            messageMap["/loopier/clip/clip/alpha"]  = &MessageMapper::setClipAlpha;
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setupClipCollectionCommandsMap()
        {
            
            // Clip collection commands
            messageMap["/loopier/clip/clips/loadlibrary"]   = &MessageMapper::loadClipLibrary;
            messageMap["/loopier/clip/clips/clearall"]      = &MessageMapper::clearClips;
            messageMap["/loopier/clip/clips/listnames"]     = &MessageMapper::listClipNames;
            messageMap["/loopier/clip/clips/listresources"] = &MessageMapper::listResourceNames;
            messageMap["/loopier/clip/clips/listlibraries"] = &MessageMapper::listClipLibraryNames;
            messageMap["/loopier/clip/clips/listcameras"]   = &MessageMapper::listCameraNames;
            messageMap["/loopier/clip/clips/togglenames"]   = &MessageMapper::toggleClipNames;
            messageMap["/loopier/clip/clips/shownames"]     = &MessageMapper::showClipNames;
            messageMap["/loopier/clip/clips/hidenames"]     = &MessageMapper::hideClipNames;
            
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setupSyphonCommandsMap()
        {
            // Syphon
            messageMap["/loopier/clip/syphon/servername"]   = &MessageMapper::setSyphonServerName;
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setupCvCommandsMap()
        {
            // CV commands
            messageMap["/loopier/clip/cv/setinput"]         = &MessageMapper::setCvInputClip;
            messageMap["/loopier/clip/cv/color"]            = &MessageMapper::setCvColor;
            messageMap["/loopier/clip/cv/threshold"]        = &MessageMapper::setCvThreshold;
            messageMap["/loopier/clip/cv/minArea"]          = &MessageMapper::setCvMinArea;
            messageMap["/loopier/clip/cv/maxArea"]          = &MessageMapper::setCvMaxArea;
            messageMap["/loopier/clip/cv/holes"]            = &MessageMapper::setCvHoles;
            messageMap["/loopier/clip/cv/toggle"]           = &MessageMapper::toggleCvVisibility;
            messageMap["/loopier/clip/cv/show"]             = &MessageMapper::showCv;
            messageMap["/loopier/clip/cv/hide"]             = &MessageMapper::hideCv;
            messageMap["/loopier/clip/cv/detectionarea"]    = &MessageMapper::setCvDetectionArea;
            messageMap["/loopier/clip/cv/maxblobs"]         = &MessageMapper::setCvMaxBlobs;
            messageMap["/loopier/clip/cv/select"]           = &MessageMapper::selectBlob;
            messageMap["/loopier/clip/cv/deselect"]         = &MessageMapper::deselectBlob;
            messageMap["/loopier/clip/cv/selectall"]        = &MessageMapper::selectAllBlobs;
            messageMap["/loopier/clip/cv/deselectall"]      = &MessageMapper::deselectAllBlobs;
            messageMap["/loopier/clip/cv/first"]            = &MessageMapper::firstBlob;
            messageMap["/loopier/clip/cv/next"]             = &MessageMapper::nextBlob;
            messageMap["/loopier/clip/cv/previous"]         = &MessageMapper::previousBlob;
            messageMap["/loopier/clip/cv/last"]             = &MessageMapper::lastBlob;
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setupConsoleCommandsMap()
        {
            // Console commands
            messageMap["/loopier/clip/console/color"]       = &MessageMapper::setConsoleColor;
            messageMap["/loopier/clip/console/alpha"]       = &MessageMapper::setConsoleAlpha;
            messageMap["/loopier/clip/console/prompt"]      = &MessageMapper::setConsolePrompt;
            messageMap["/loopier/clip/console/print"]       = &MessageMapper::printToConsole;
            messageMap["/loopier/clip/console/lines"]       = &MessageMapper::setConsoleLinesNum;
            messageMap["/loopier/clip/console/toggle"]      = &MessageMapper::toggleConsole;
            messageMap["/loopier/clip/console/show"]        = &MessageMapper::showConsole;
            messageMap["/loopier/clip/console/hide"]        = &MessageMapper::hideConsole;
            messageMap["/loopier/clip/console/moveto"]      = &MessageMapper::moveConsole;
            messageMap["/loopier/clip/console/font"]        = &MessageMapper::setConsoleFont;
            messageMap["/loopier/clip/console/fontsize"]    = &MessageMapper::setConsoleFontSize;
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setupUvcCommandsMap()
        {
            messageMap["/loopier/clip/uvc/add"]          = &MessageMapper::addUvcCamera;
            messageMap["/loopier/clip/uvc/use"]          = &MessageMapper::useUvcCamera;
            messageMap["/loopier/clip/uvc/autoexposure"] = &MessageMapper::setUvcAutoExposure;
            messageMap["/loopier/clip/uvc/exposure"]     = &MessageMapper::setUvcExposure;
            messageMap["/loopier/clip/uvc/autofocus"]    = &MessageMapper::setUvcAutoFocus;
            messageMap["/loopier/clip/uvc/focus"]        = &MessageMapper::setUvcFocus;
            messageMap["/loopier/clip/uvc/autowhitebalance"] = &MessageMapper::setUvcAutoWhiteBalance;
            messageMap["/loopier/clip/uvc/whitebalance"] = &MessageMapper::setUvcWhiteBalance;
            messageMap["/loopier/clip/uvc/gain"]         = &MessageMapper::setUvcGain;
            messageMap["/loopier/clip/uvc/brightness"]   = &MessageMapper::setUvcBrightness;
            messageMap["/loopier/clip/uvc/contrast"]     = &MessageMapper::setUvcContrast;
            messageMap["/loopier/clip/uvc/saturation"]   = &MessageMapper::setUvcSaturation;
            messageMap["/loopier/clip/uvc/sharpness"]    = &MessageMapper::setUvcSharpness;
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::printMessage(Message & msg)
        {
            osc::printMessage(msg, "OSC:");
            ConsoleUI::print(osc::getSimplifiedMessage(msg));
        }
        
        //---------------------------------------------------------
        void MessageMapper::mapMessageToFunc(Message & msg)
        {
            // Look up the processor for this message address
            map<string, mappedFunc>::iterator iter = messageMap.find(msg.getAddress());
            if (iter != messageMap.end()) {
                (this->*(iter->second))(msg); // call the processor method for this message
                printMessage(msg);
            }
            else {
                ofLogWarning() << "Unhandled OSC message: " << msg.getAddress();
            }
        }
        
        //---------------------------------------------------------
        
        
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        TEST
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        void MessageMapper::test(const Message & msg)
        {
            ClipPtr clip = clip::getClip(msg.getArgAsString(0));
            
        }
        
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        APPLICATION
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        void MessageMapper::quit(const Message & msg)
        {
            ofExit();
        }
        
        //---------------------------------------------------------
        void MessageMapper::fullscreen(const Message & msg)
        {
            ofToggleFullscreen();
        }
        
        //---------------------------------------------------------
        void MessageMapper::move(const Message & msg)
        {
            ofSetFullscreen(false);
            float x = msg.getArgAsFloat(1) * ofGetScreenWidth();
            float y = msg.getArgAsFloat(2) * ofGetScreenHeight();
            ofSetWindowPosition(x, y);
        }
        
        //---------------------------------------------------------
        void MessageMapper::loadResources(const Message & msg)
        {
            vector<string> resourcenames;
            for (int i = 0; i < msg.getNumArgs(); i++) {
                resourcenames.push_back(msg.getArgAsString(i));
            }
            
            resource::load(resourcenames);
        }
        
        //---------------------------------------------------------
        void MessageMapper::clearResources(const Message & msg)
        {
            resource::clearAll();
        }
        
        void MessageMapper::loadScriptFile(const Message & msg)
        {
            script::loadScriptFile(msg.getArgAsString(0));
        }
        
        void MessageMapper::listScriptNames(const Message & msg)
        {
//            command::getCommandLibraryNames(msg.getArgAsString(0));
            sendScriptNames();
        }
        
        
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        ONE CLIP
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        void MessageMapper::newClip(const Message & msg)
        {
            int n = msg.getNumArgs();
            if      (n == 1)    clip::newClip(msg.getArgAsString(0));
            else if (n == 2)    clip::newClip(msg.getArgAsString(0), msg.getArgAsString(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::newClipFromBlob(const Message & msg)
        {
            int n = msg.getNumArgs();
            if      (n == 1)    clip::newClipFromBlob(msg.getArgAsString(0));
            else if (n == 2)    clip::newClipFromBlob(msg.getArgAsString(0), msg.getArgAsString(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::removeClip(const Message & msg)
        {
            clip::removeClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::resetClip(const Message & msg)
        {
            clip::resetClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::selectClip(const Message & msg)
        {
            clip::selectClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::deselectClip(const Message & msg)
        {
            clip::deselectClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::selectAllClips(const Message & msg)
        {
            clip::selectAllClips();
        }
        
        //---------------------------------------------------------
        void MessageMapper::deselectAllClips(const Message & msg)
        {
            clip::deselectAllClips();
        }
        
        //---------------------------------------------------------
        void MessageMapper::setParent(const Message & msg)
        {
            clip::setParentClip(msg.getArgAsString(0), msg.getArgAsString(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::removeParent(const Message & msg)
        {
            clip::removeParentClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setOffset(const Message & msg)
        {
            clip::setOffsetToParentClip(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipDrawOrder(const Message & msg)
        {
            clip::setClipDrawOrder(msg.getArgAsString(0), msg.getArgAsInt(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::bringClipToFront(const Message & msg)
        {
            clip::bringClipToFront(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::bringClipForward(const Message & msg)
        {
            clip::bringClipForward(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::sendClipBackward(const Message & msg)
        {
            clip::sendClipBackward(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::sendClipToBack(const Message & msg)
        {
            clip::sendClipToBack(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setBackgroundClip(const Message & msg)
        {
            clip::setBackgroundClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setPublicClip(const Message & msg)
        {
            clip::setPublicClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setPrivateClip(const Message & msg)
        {
            clip::setPrivateClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::listLayers(const Message & msg)
        {
            clip::listLayers();
        }
        
        //---------------------------------------------------------
        void MessageMapper::scaleUpClip(const Message & msg)
        {
            clip::scaleUpClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::scaleDownClip(const Message & msg)
        {
            clip::scaleDownClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::scaleClip(const Message & msg)
        {
            clip::scaleClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipWidth(const Message & msg)
        {
            clip::setClipWidth(msg.getArgAsString(0), msg.getArgAsFloat(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipHeight(const Message & msg)
        {
            clip::setClipHeight(msg.getArgAsString(0), msg.getArgAsFloat(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::resetClipScale(const Message & msg)
        {
            clip::resetClipScale(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipVFlip(const Message & msg)
        {
            clip::setClipVFlip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipHFlip(const Message & msg)
        {
            clip::setClipHFlip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::toggleFullscreenClip(const Message & msg)
        {
            clip::toggleFullscreenClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::toggleClipVisibility(const Message & msg)
        {
            clip::toggleClipVisibility(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::showClip(const Message & msg)
        {
            clip::showClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::hideClip(const Message & msg)
        {
            clip::hideClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::toggleClipName(const Message & msg)
        {
            clip::toggleName(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::showClipName(const Message & msg)
        {
            clip::showName(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::hideClipName(const Message & msg)
        {
            clip::hideName(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipMask(const Message & msg)
        {
            clip::setClipMask(msg.getArgAsString(0), msg.getArgAsString(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::enableClipMask(const Message & msg)
        {
            clip::enableClipMask(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::disableClipMask(const Message & msg)
        {
            clip::disableClipMask(msg.getArgAsString(0));
        }
        
        
        // PLAY
        //---------------------------------------------------------
        void MessageMapper::playClip(const Message & msg)
        {
            clip::playClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::stopClip(const Message & msg)
        {
            clip::stopClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::pauseClip(const Message & msg)
        {
            clip::pauseClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipLoopState(const Message & msg)
        {
            string arg = msg.getArgAsString(1);
            LoopType looptype = LoopType::normal;
            
            if      (arg == "palindrome")   looptype = LoopType::palindrome;
            else if (arg == "none" )        looptype = LoopType::none;
            else if (arg == "once" )        looptype = LoopType::once;
            
            clip::setClipLoopState(msg.getArgAsString(0), looptype);
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipPlayDirection(const Message & msg)
        {
            string arg = msg.getArgAsString(1);
            PlayDirection direction = PlayDirection::normal;
            
            if (arg == "reverse")   direction = PlayDirection::reverse;
            
            clip::setClipPlayDirection(msg.getArgAsString(0), direction);
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipSpeed(const Message & msg)
        {
            clip::setClipSpeed(msg.getArgAsString(0), msg.getArgAsFloat(1));
        }
        
        // EDIT
        
        //---------------------------------------------------------
        void MessageMapper::addFrame(const Message & msg)
        {
            clip::addFrame(msg.getArgAsString(0), msg.getArgAsString(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::insertFrame(const Message & msg)
        {
            clip::insertFrame(msg.getArgAsString(0), msg.getArgAsString(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::removeFrame(const Message & msg)
        {
            clip::removeFrame(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::clearFrames(const Message & msg)
        {
            clip::clearFrames(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::saveFrames(const Message & msg)
        {
            clip::saveFrames(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::loadFrames(const Message & msg)
        {
            clip::loadFrames(msg.getArgAsString(0), msg.getArgAsString(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::firstFrame(const Message & msg)
        {
            clip::firstFrame(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::nextFrame(const Message & msg)
        {
            clip::nextFrame(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::previousFrame(const Message & msg)
        {
            clip::previousFrame(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::lastFrame(const Message & msg)
        {
            clip::lastFrame(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::goToFrame(const Message & msg)
        {
            clip::goToFrame(msg.getArgAsString(0), msg.getArgAsInt(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::saveClip(const Message & msg)
        {
            clip::saveClip(msg.getArgAsString(0));
        }
        
        // MOVE
        //---------------------------------------------------------
        void MessageMapper::moveClipTo(const Message & msg)
        {
            clip::moveClipTo(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
        }
        
        //---------------------------------------------------------
        void MessageMapper::centerClip(const Message & msg)
        {
            clip::centerClip(msg.getArgAsString(0));
        }
        
        
        // COLOR
        //---------------------------------------------------------
        void MessageMapper::setClipColor(const Message & msg)
        {
            //    ofColor color = MessageMapper::getColorFromMessage(msg);
            //    clip::setClipColor(msg.getArgAsString(0), color);
            if (msg.getNumArgs() == 2) clip::setClipColor(msg.getArgAsString(0), msg.getArgAsFloat(1));
            if (msg.getNumArgs() == 3) clip::setClipColor(msg.getArgAsString(0),
                                                          msg.getArgAsFloat(1),
                                                          msg.getArgAsFloat(2));
            if (msg.getNumArgs() == 4) clip::setClipColor(msg.getArgAsString(0),
                                                          msg.getArgAsFloat(1),
                                                          msg.getArgAsFloat(2),
                                                          msg.getArgAsFloat(3));
            if (msg.getNumArgs() == 5) clip::setClipColor(msg.getArgAsString(0),
                                                          msg.getArgAsFloat(1),
                                                          msg.getArgAsFloat(2),
                                                          msg.getArgAsFloat(3),
                                                          msg.getArgAsFloat(4));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setClipAlpha(const Message & msg)
        {
            clip::setClipAlpha(msg.getArgAsString(0), msg.getArgAsFloat(1));
        }
        
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        CLIP COLLECTIONS
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        void MessageMapper::loadClipLibrary(const Message & msg)
        {
            clip::loadClipLibrary(msg.getArgAsString(0));
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::clearClips(const Message & msg)
        {
            clip::clearAll();
        }
        
        //---------------------------------------------------------
        void MessageMapper::listClipNames(const Message & msg)
        {
            clip::listAll();
            sendClipNames();
        }
        
        //---------------------------------------------------------
        void MessageMapper::listResourceNames(const Message & msg)
        {
            //    listResourceNames();
            resource::listAll();
            sendResourceNames();
        }
        
        //---------------------------------------------------------
        void MessageMapper::listCameraNames(const Message & msg)
        {
            sendCameraNames();
        }
        
        //---------------------------------------------------------
        void MessageMapper::listClipLibraryNames(const Message & msg)
        {
            clip::listClipLibraryNames();
            sendLibraryNames();
        }
        
        //---------------------------------------------------------
        void MessageMapper::toggleClipNames(const Message & msg)
        {
            clip::toggleNames();
        }
        
        //---------------------------------------------------------
        void MessageMapper::showClipNames(const Message & msg)
        {
            clip::showNames();
        }
        
        //---------------------------------------------------------
        void MessageMapper::hideClipNames(const Message & msg)
        {
            clip::hideNames();
        }
        
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        Syphon
        
        //---------------------------------------------------------
        
        //---------------------------------------------------------
        void MessageMapper::setSyphonServerName(const Message & msg)
        {
            resource::setSyphonServerName(msg.getArgAsString(0),
                                          msg.getArgAsString(1),
                                          msg.getArgAsString(2));
        }
        
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        CV
        
        //---------------------------------------------------------
        
        //---------------------------------------------------------
        void MessageMapper::setCvColor(const Message & msg)
        {
            // change the color of the clip named "cv"
            Message newmsg;
            newmsg.setAddress(msg.getAddress());
            newmsg.addStringArg("cv");
            for (int i = 0; i < msg.getNumArgs(); i++) {
                newmsg.addFloatArg(msg.getArgAsFloat(i));
            }
            setClipColor(newmsg);
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvThreshold(const Message & msg)
        {
            cv::setThreshold(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvMinArea(const Message & msg)
        {
            cv::setMinArea(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvMaxArea(const Message & msg)
        {
            cv::setMaxArea(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvHoles(const Message & msg)
        {
            cv::setFindHoles(msg.getArgAsBool(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvMaxBlobs(const Message & msg)
        {
            cv::setMaxBlobs(msg.getArgAsInt(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvInputClip(const Message & msg)
        {
            cv::setInputClip(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvDeviceId(const Message & msg)
        {
            cv::setDeviceId(msg.getArgAsInt(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::toggleCvVisibility(const Message & msg)
        {
            cv::toggleVisibility();
        }
        
        //---------------------------------------------------------
        void MessageMapper::showCv(const Message & msg)
        {
            cv::show();
        }
        
        //---------------------------------------------------------
        void MessageMapper::hideCv(const Message & msg)
        {
            cv::hide();
        }
        
        //---------------------------------------------------------
        void MessageMapper::setCvDetectionArea(const Message & msg)
        {
            ofRectangle rect(msg.getArgAsFloat(0), msg.getArgAsFloat(1),
                             msg.getArgAsFloat(2), msg.getArgAsFloat(3));
            cv::setDetectionArea(rect);
        }
        
        //---------------------------------------------------------
        void MessageMapper::selectBlob(const Message & msg)
        {
            cv::selectBlob();
        }
        
        //---------------------------------------------------------
        void MessageMapper::deselectBlob(const Message & msg)
        {
            cv::deselectBlob();
        }
        
        //---------------------------------------------------------
        void MessageMapper::selectAllBlobs(const Message & msg)
        {
            cv::selectAllBlobs();
        }
        
        //---------------------------------------------------------
        void MessageMapper::deselectAllBlobs(const Message & msg)
        {
            cv::deselectAllBlobs();
        }
        
        //---------------------------------------------------------
        void MessageMapper::firstBlob(const Message & msg)
        {
            cv::firstBlob();
        }
        
        //---------------------------------------------------------
        void MessageMapper::nextBlob(const Message & msg)
        {
            cv::nextBlob();
        }
        
        //---------------------------------------------------------
        void MessageMapper::previousBlob(const Message & msg)
        {
            cv::previousBlob();
        }
        
        //---------------------------------------------------------
        void MessageMapper::lastBlob(const Message & msg)
        {
            cv::lastBlob();
        }
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        CONSOLE
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        void MessageMapper::setConsoleColor(const Message & msg)
        {
            ConsoleUI::setColor(MessageMapper::getColorFromMessage(msg));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setConsoleAlpha(const Message & msg)
        {
            ConsoleUI::setAlpha(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setConsolePrompt(const Message & msg)
        {
            ConsoleUI::setPrompt(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::printToConsole(const Message & msg)
        {
            ConsoleUI::print(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setConsoleLinesNum(const Message & msg)
        {
            ConsoleUI::setMaxLines(msg.getArgAsInt(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::toggleConsole(const Message & msg)
        {
            ConsoleUI::toggle();
        }
        
        //---------------------------------------------------------
        void MessageMapper::showConsole(const Message & msg)
        {
            ConsoleUI::show();
        }
        
        //---------------------------------------------------------
        void MessageMapper::hideConsole(const Message & msg)
        {
            ConsoleUI::hide();
        }
        
        //---------------------------------------------------------
        void MessageMapper::moveConsole(const Message & msg)
        {
            ConsoleUI::setPosition(msg.getArgAsFloat(0), msg.getArgAsFloat(1));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setConsoleFont(const Message & msg)
        {
            ConsoleUI::setFont(msg.getArgAsString(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setConsoleFontSize(const Message & msg)
        {
            ConsoleUI::setFontSize(msg.getArgAsInt(0));
        }
        
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        UVC
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        void MessageMapper::addUvcCamera(const Message & msg)
        {
            int     vendorId        = msg.getArgAsInt(0);
            int     productId       = msg.getArgAsInt(1);
            int     interfaceNum    = msg.getArgAsInt(2);
            string  name            = msg.getArgAsString(3);
            uvc::addCamera(vendorId, productId, interfaceNum, name);
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::useUvcCamera(const Message & msg)
        {
            uvc::useCamera(msg.getArgAsString(0)); // camera name
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::setUvcAutoExposure(const Message & msg)
        {
            uvc::setAutoExposure(msg.getArgAsBool(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcExposure(const Message & msg)
        {
            uvc::setExposure(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcAutoFocus(const Message & msg)
        {
            uvc::setAutoFocus(msg.getArgAsBool(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcFocus(const Message & msg)
        {
            uvc::setFocus(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcAutoWhiteBalance(const Message & msg)
        {
            uvc::setAutoWhiteBalance(msg.getArgAsBool(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcWhiteBalance(const Message & msg)
        {
            uvc::setWhiteBalance(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcGain(const Message & msg)
        {
            uvc::setGain(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcBrightness(const Message & msg)
        {
            uvc::setBrightness(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcContrast(const Message & msg)
        {
            uvc::setContrast(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcSaturation(const Message & msg)
        {
            uvc::setSaturation(msg.getArgAsFloat(0));
        }
        
        //---------------------------------------------------------
        void MessageMapper::setUvcSharpness(const Message & msg)
        {
            uvc::setSharpness(msg.getArgAsFloat(0));
        }
        
        
        
        
        
        
        //---------------------------------------------------------
        
        //        SENDERS
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        void MessageMapper::sendClipNames()
        {
            vector<string> names = loopier::clip::getNamesList();
            Message msg;
            
            msg.setAddress("/loopier/clip/clips/clipnames");
            
            for (const auto &item : names) {
                if (item == "cv" || item == "syphon") continue; // skip cv and syphon clips
                msg.addStringArg(item);
            };
            
            osc.sendMessage(msg);
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::sendResourceNames()
        {
            vector<string> names = loopier::resource::getNamesList();
            Message msg;
            
            msg.setAddress("/loopier/clip/clips/resourcenames");
            
            for (const auto &item : names) {  msg.addStringArg(item); };
            
            osc.sendMessage(msg);
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::sendCameraNames()
        {
            vector<string> names = loopier::resource::getCameraNames();
            Message msg;
            
            msg.setAddress("/loopier/clip/clips/cameranames");
            
            for (const auto &item : names) {  msg.addStringArg(item); };
            
            osc.sendMessage(msg);
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::sendLibraryNames()
        {
            vector<string> names = loopier::clip::getClipLibraryNames();
            Message msg;
            
            msg.setAddress("/loopier/clip/clips/librarynames");
            
            for (const auto &item : names) {
                msg.addStringArg(item);
            };
            
            osc.sendMessage(msg);
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::listClipInfo(const Message &msg)
        {
            sendClipInfo(msg.getArgAsString(0));
        }
        
        
        //---------------------------------------------------------
        void MessageMapper::sendClipInfo(const string clipname)
        {
            if (!clip::exists(clipname)) return;
            ClipPtr clip = clip::getClip(clipname);
            Message msg;
            
            msg.setAddress("/loopier/clip/clip/info");
            msg.addStringArg(clip->getName());
            msg.addStringArg(clip->getResourceName());
            msg.addBoolArg(clip->isPlaying());
            float speed = clip->getSpeed();
            if (clip->getPlayDirection() == PlayDirection::reverse) speed *= -1;
            msg.addFloatArg(clip->getSpeed());
            if      (clip->getLoopState() == LoopType::normal)      msg.addStringArg("normal");
            else if (clip->getLoopState() == LoopType::palindrome)  msg.addStringArg("palindrome");
            else if (clip->getLoopState() == LoopType::once)        msg.addStringArg("once");
            msg.addFloatArg(clip->getPosition().x);
            msg.addFloatArg(clip->getPosition().y);
            msg.addFloatArg(clip->getWidth());
            msg.addFloatArg(clip->getHeight());
            msg.addFloatArg(clip->getScale());
            msg.addFloatArg(clip->getColor().r / 255.0);
            msg.addFloatArg(clip->getColor().g / 255.0);
            msg.addFloatArg(clip->getColor().b / 255.0);
            float alpha = clip->getColor().a / 255.0;
            msg.addFloatArg(clip->getColor().a / 255.0);
            msg.addInt32Arg(clip->getDepth());
            msg.addBoolArg(clip->isVisible());
            //            msg.addStringArg(clip->getNask()); // TODO
            msg.addBoolArg(clip->isFullscreen());
            msg.addBoolArg(clip->isFlippedV());
            msg.addBoolArg(clip->isFlippedH());
            msg.addStringArg(clip->getParentName());
            msg.addFloatArg(clip->getOffset().x);
            msg.addFloatArg(clip->getOffset().y);
            
            osc.sendMessage(msg);
        }
        
        
        
        
        //---------------------------------------------------------
        void MessageMapper::sendScriptNames()
        {
            vector<string> names = loopier::script::getScriptNames();
            Message msg;
            
            msg.setAddress("/loopier/clip/script/names");
            
            for (const auto &item : names) {
                msg.addStringArg(item);
            };
            
            osc.sendMessage(msg);
        }
        
        
        
        
        //---------------------------------------------------------
        
        //        CONSOLE
        
        //---------------------------------------------------------
        
        
        //---------------------------------------------------------
        ofColor MessageMapper::getColorFromMessage(const Message & msg)
        {
            ofColor color;
            int numArgs = msg.getNumArgs();
            
            if      (numArgs == 1)  color = ofColor(msg.getArgAsFloat(1) * 255);
            else if (numArgs == 2)  color = ofColor(msg.getArgAsFloat(1) * 255, msg.getArgAsFloat(2) * 255);
            else if (numArgs == 3)  color = ofColor(msg.getArgAsFloat(1) * 255,
                                                    msg.getArgAsFloat(2) * 255,
                                                    msg.getArgAsFloat(3) * 255);
            else if (numArgs == 4)  color = ofColor(msg.getArgAsFloat(1) * 255,
                                                    msg.getArgAsFloat(2) * 255,
                                                    msg.getArgAsFloat(3) * 255,
                                                    msg.getArgAsFloat(4) * 255);
            return color;
        }
    } // namespace osc
} // namespace loopier
