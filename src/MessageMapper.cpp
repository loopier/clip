//
//  MessageMapper.cpp
//  clip
//
//  Created by roger on 28/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "MessageMapper.h"

//---------------------------------------------------------
void loopier::osc::MessageMapper::setup()
{
    clipManager = ClipManager::getInstance();
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &loopier::osc::MessageMapper::mapMessageToFunc);
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
void loopier::osc::MessageMapper::setupAppCommandsMap()
{
    // Application commands
    messageMap["/loopier/clip/test"]       = &loopier::osc::MessageMapper::test;
    
    // Application commands
    messageMap["/loopier/clip/quit"]        = &loopier::osc::MessageMapper::quit;
    messageMap["/loopier/clip/fullscreen"]  = &loopier::osc::MessageMapper::fullscreen;
    messageMap["/loopier/clip/move"]        = &loopier::osc::MessageMapper::move;
    
    messageMap["/loopier/clip/loadresource"]        = &loopier::osc::MessageMapper::loadResources;
    messageMap["/loopier/clip/loadresources"]        = &loopier::osc::MessageMapper::loadResources;
    messageMap["/loopier/clip/clearresources"]       = &loopier::osc::MessageMapper::clearResources;
    
    messageMap["/loopier/clip/loadkeymap"]       = &loopier::osc::MessageMapper::loadKeymap;
    
    messageMap["/loopier/clip/layers"]         = &loopier::osc::MessageMapper::listLayers;
    
    messageMap["/loopier/clip/script/load"]     = &loopier::osc::MessageMapper::loadScriptFile;
    messageMap["/loopier/clip/script/loadall"]  = &loopier::osc::MessageMapper::loadAllScripts;
    messageMap["/loopier/clip/script/clearall"] = &loopier::osc::MessageMapper::clearScriptList;
    messageMap["/loopier/clip/script/run"]      = &loopier::osc::MessageMapper::runScript;
    messageMap["/loopier/clip/script/loadnrun"] = &loopier::osc::MessageMapper::loadAndRunScript;
    messageMap["/loopier/clip/script/listnames"]   = &loopier::osc::MessageMapper::listScriptNames;
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::setupClipCommandsMap()
{
    
    // One Clip commands
    messageMap["/loopier/clip/clip/new"]                = &loopier::osc::MessageMapper::newClip;
    // TODO: should replace clip, not resource
    messageMap["/loopier/clip/clip/replace"]            = &loopier::osc::MessageMapper::newClip;
    messageMap["/loopier/clip/clip/replaceblob"]        = &loopier::osc::MessageMapper::newClipFromBlob;
    messageMap["/loopier/clip/clip/remove"]             = &loopier::osc::MessageMapper::removeClip;
    messageMap["/loopier/clip/clip/reset"]              = &loopier::osc::MessageMapper::resetClip;
    messageMap["/loopier/clip/clip/select"]             = &loopier::osc::MessageMapper::selectClip;
    messageMap["/loopier/clip/clip/next"]               = &loopier::osc::MessageMapper::selectNextClip;
    messageMap["/loopier/clip/clip/deselect"]           = &loopier::osc::MessageMapper::deselectClip;
    messageMap["/loopier/clip/clip/selectall"]          = &loopier::osc::MessageMapper::selectAllClips;
    messageMap["/loopier/clip/clip/deselectall"]        = &loopier::osc::MessageMapper::deselectAllClips;
    messageMap["/loopier/clip/clip/listinfo"]           = &loopier::osc::MessageMapper::listClipInfo;
    // parent
    messageMap["/loopier/clip/clip/addchild"]           = &loopier::osc::MessageMapper::addClipChild;
    messageMap["/loopier/clip/clip/removechild"]        = &loopier::osc::MessageMapper::removeClipChild;
    messageMap["/loopier/clip/clip/clearchildren"]  = &loopier::osc::MessageMapper::clearClipChildren;
    messageMap["/loopier/clip/clip/listchildren"]       = &loopier::osc::MessageMapper::listClipChildren;
    // Arrange
    messageMap["/loopier/clip/clip/depth"]          = &loopier::osc::MessageMapper::setClipDrawOrder;
    messageMap["/loopier/clip/clip/front"]          = &loopier::osc::MessageMapper::bringClipToFront;
    messageMap["/loopier/clip/clip/forward"]        = &loopier::osc::MessageMapper::bringClipForward;
    messageMap["/loopier/clip/clip/backward"]       = &loopier::osc::MessageMapper::sendClipBackward;
    messageMap["/loopier/clip/clip/back"]           = &loopier::osc::MessageMapper::sendClipToBack;
    messageMap["/loopier/clip/clip/background"]     = &loopier::osc::MessageMapper::setBackgroundClip;
    messageMap["/loopier/clip/clip/public"]         = &loopier::osc::MessageMapper::setPublicClip;
    messageMap["/loopier/clip/clip/private"]        = &loopier::osc::MessageMapper::setPrivateClip;
    // Size
    messageMap["/loopier/clip/clip/scaleup"]            = &loopier::osc::MessageMapper::scaleUpClip;
    messageMap["/loopier/clip/clip/scaledown"]          = &loopier::osc::MessageMapper::scaleDownClip;
    messageMap["/loopier/clip/clip/scale"]              = &loopier::osc::MessageMapper::scaleClip;
    messageMap["/loopier/clip/clip/xscale"]             = &loopier::osc::MessageMapper::setClipWidth;
    messageMap["/loopier/clip/clip/yscale"]             = &loopier::osc::MessageMapper::setClipHeight;
    messageMap["/loopier/clip/clip/resetscale"]         = &loopier::osc::MessageMapper::resetClipScale;
    messageMap["/loopier/clip/clip/fullscreen"]         = &loopier::osc::MessageMapper::toggleFullscreenClip;
    // Orientation
    messageMap["/loopier/clip/clip/flipv"]              = &loopier::osc::MessageMapper::setClipVFlip;
    messageMap["/loopier/clip/clip/fliph"]              = &loopier::osc::MessageMapper::setClipHFlip;
    // Visibility
    messageMap["/loopier/clip/clip/togglevisibility"]   = &loopier::osc::MessageMapper::toggleClipVisibility;
    messageMap["/loopier/clip/clip/show"]               = &loopier::osc::MessageMapper::showClip;
    messageMap["/loopier/clip/clip/hide"]               = &loopier::osc::MessageMapper::hideClip;
    // Visibility
    messageMap["/loopier/clip/clip/togglename"]   = &loopier::osc::MessageMapper::toggleClipName;
    messageMap["/loopier/clip/clip/showname"]               = &loopier::osc::MessageMapper::showClipName;
    messageMap["/loopier/clip/clip/hidename"]               = &loopier::osc::MessageMapper::hideClipName;
    // FX
    messageMap["/loopier/clip/clip/mask"]               = &loopier::osc::MessageMapper::setClipMask;
    messageMap["/loopier/clip/clip/maskon"]             = &loopier::osc::MessageMapper::enableClipMask;
    messageMap["/loopier/clip/clip/maskoff"]            = &loopier::osc::MessageMapper::disableClipMask;
    messageMap["/loopier/clip/clip/holesmask"]          = &loopier::osc::MessageMapper::setClipHolesMask;
    // play
    messageMap["/loopier/clip/clip/play"]           = &loopier::osc::MessageMapper::playClip;
    messageMap["/loopier/clip/clip/stop"]           = &loopier::osc::MessageMapper::stopClip;
    messageMap["/loopier/clip/clip/pause"]          = &loopier::osc::MessageMapper::pauseClip;
    messageMap["/loopier/clip/clip/loop"]           = &loopier::osc::MessageMapper::setClipLoopState;
    messageMap["/loopier/clip/clip/playdirection"]  = &loopier::osc::MessageMapper::setClipPlayDirection;
    messageMap["/loopier/clip/clip/speed"]          = &loopier::osc::MessageMapper::setClipSpeed;
    // edit
    messageMap["/loopier/clip/clip/addframe"]           = &loopier::osc::MessageMapper::addFrame;
    messageMap["/loopier/clip/clip/insertframe"]        = &loopier::osc::MessageMapper::insertFrame;
    messageMap["/loopier/clip/clip/removeframe"]        = &loopier::osc::MessageMapper::removeFrame;
    messageMap["/loopier/clip/clip/clearframes"]        = &loopier::osc::MessageMapper::clearFrames;
    messageMap["/loopier/clip/clip/saveframes"]         = &loopier::osc::MessageMapper::saveFrames;
    messageMap["/loopier/clip/clip/loadframes"]         = &loopier::osc::MessageMapper::loadFrames;
    messageMap["/loopier/clip/clip/firstframe"]         = &loopier::osc::MessageMapper::firstFrame;
    messageMap["/loopier/clip/clip/nextframe"]          = &loopier::osc::MessageMapper::nextFrame;
    messageMap["/loopier/clip/clip/previousframe"]      = &loopier::osc::MessageMapper::previousFrame;
    messageMap["/loopier/clip/clip/lastframe"]          = &loopier::osc::MessageMapper::lastFrame;
    messageMap["/loopier/clip/clip/gotoframe"]          = &loopier::osc::MessageMapper::goToFrame;
    messageMap["/loopier/clip/clip/save"]               = &loopier::osc::MessageMapper::saveClip;
    // move
    messageMap["/loopier/clip/clip/moveto"] = &loopier::osc::MessageMapper::moveClipTo;
    messageMap["/loopier/clip/clip/center"] = &loopier::osc::MessageMapper::centerClip;
    // color
    messageMap["/loopier/clip/clip/color"]  = &loopier::osc::MessageMapper::setClipColor;
    messageMap["/loopier/clip/clip/alpha"]  = &loopier::osc::MessageMapper::setClipAlpha;
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::setupClipCollectionCommandsMap()
{
    
    // Clip collection commands
    messageMap["/loopier/clip/clips/loadlibrary"]   = &loopier::osc::MessageMapper::loadClipLibrary; // TODO: REMOVE
    messageMap["/loopier/clip/clearallclips"]      = &loopier::osc::MessageMapper::clearClips;
    messageMap["/loopier/clip/listclips"]     = &loopier::osc::MessageMapper::listClipNames;
    messageMap["/loopier/clip/listresources"] = &loopier::osc::MessageMapper::listResourceNames;
    messageMap["/loopier/clip/clips/listlibraries"] = &loopier::osc::MessageMapper::listClipLibraryNames;// TODO: REMOVE
    messageMap["/loopier/clip/listcameras"]   = &loopier::osc::MessageMapper::listCameraNames;
    messageMap["/loopier/clip/togglenames"]   = &loopier::osc::MessageMapper::toggleClipNames;
    messageMap["/loopier/clip/shownames"]     = &loopier::osc::MessageMapper::showClipNames;
    messageMap["/loopier/clip/hidenames"]     = &loopier::osc::MessageMapper::hideClipNames;
    
    messageMap["/loopier/clip/selection"] = &loopier::osc::MessageMapper::listClipNames;
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::setupSyphonCommandsMap()
{
    // Syphon
    messageMap["/loopier/clip/syphon/servername"]   = &loopier::osc::MessageMapper::setSyphonServerName;
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::setupCvCommandsMap()
{
    // CV commands
    messageMap["/loopier/clip/cv/setinput"]         = &loopier::osc::MessageMapper::setCvInputClip;
    messageMap["/loopier/clip/cv/color"]            = &loopier::osc::MessageMapper::setCvColor;
    messageMap["/loopier/clip/cv/threshold"]        = &loopier::osc::MessageMapper::setCvThreshold;
    messageMap["/loopier/clip/cv/minArea"]          = &loopier::osc::MessageMapper::setCvMinArea;
    messageMap["/loopier/clip/cv/maxArea"]          = &loopier::osc::MessageMapper::setCvMaxArea;
    messageMap["/loopier/clip/cv/holes"]            = &loopier::osc::MessageMapper::setCvHoles;
    messageMap["/loopier/clip/cv/holesmask"]        = &loopier::osc::MessageMapper::setCvHolesMask;
    messageMap["/loopier/clip/cv/toggle"]           = &loopier::osc::MessageMapper::toggleCvVisibility;
    messageMap["/loopier/clip/cv/show"]             = &loopier::osc::MessageMapper::showCv;
    messageMap["/loopier/clip/cv/hide"]             = &loopier::osc::MessageMapper::hideCv;
    messageMap["/loopier/clip/cv/detectionarea"]    = &loopier::osc::MessageMapper::setCvDetectionArea;
    messageMap["/loopier/clip/cv/maxblobs"]         = &loopier::osc::MessageMapper::setCvMaxBlobs;
    messageMap["/loopier/clip/cv/select"]           = &loopier::osc::MessageMapper::selectBlob;
    messageMap["/loopier/clip/cv/deselect"]         = &loopier::osc::MessageMapper::deselectBlob;
    messageMap["/loopier/clip/cv/selectall"]        = &loopier::osc::MessageMapper::selectAllBlobs;
    messageMap["/loopier/clip/cv/deselectall"]      = &loopier::osc::MessageMapper::deselectAllBlobs;
    messageMap["/loopier/clip/cv/first"]            = &loopier::osc::MessageMapper::firstBlob;
    messageMap["/loopier/clip/cv/next"]             = &loopier::osc::MessageMapper::nextBlob;
    messageMap["/loopier/clip/cv/previous"]         = &loopier::osc::MessageMapper::previousBlob;
    messageMap["/loopier/clip/cv/last"]             = &loopier::osc::MessageMapper::lastBlob;
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::setupConsoleCommandsMap()
{
    // Console commands
    messageMap["/loopier/clip/console/color"]       = &loopier::osc::MessageMapper::setConsoleColor;
    messageMap["/loopier/clip/console/alpha"]       = &loopier::osc::MessageMapper::setConsoleAlpha;
    messageMap["/loopier/clip/console/prompt"]      = &loopier::osc::MessageMapper::setConsolePrompt;
    messageMap["/loopier/clip/console/print"]       = &loopier::osc::MessageMapper::printToConsole;
    messageMap["/loopier/clip/console/lines"]       = &loopier::osc::MessageMapper::setConsoleLinesNum;
    messageMap["/loopier/clip/console/toggle"]      = &loopier::osc::MessageMapper::toggleConsole;
    messageMap["/loopier/clip/console/show"]        = &loopier::osc::MessageMapper::showConsole;
    messageMap["/loopier/clip/console/hide"]        = &loopier::osc::MessageMapper::hideConsole;
    messageMap["/loopier/clip/console/moveto"]      = &loopier::osc::MessageMapper::moveConsole;
    messageMap["/loopier/clip/console/font"]        = &loopier::osc::MessageMapper::setConsoleFont;
    messageMap["/loopier/clip/console/fontsize"]    = &loopier::osc::MessageMapper::setConsoleFontSize;
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::setupUvcCommandsMap()
{
    messageMap["/loopier/clip/uvc/add"]          = &loopier::osc::MessageMapper::addUvcCamera;
    messageMap["/loopier/clip/uvc/use"]          = &loopier::osc::MessageMapper::useUvcCamera;
    messageMap["/loopier/clip/uvc/autoexposure"] = &loopier::osc::MessageMapper::setUvcAutoExposure;
    messageMap["/loopier/clip/uvc/exposure"]     = &loopier::osc::MessageMapper::setUvcExposure;
    messageMap["/loopier/clip/uvc/autofocus"]    = &loopier::osc::MessageMapper::setUvcAutoFocus;
    messageMap["/loopier/clip/uvc/focus"]        = &loopier::osc::MessageMapper::setUvcFocus;
    messageMap["/loopier/clip/uvc/autowhitebalance"] = &loopier::osc::MessageMapper::setUvcAutoWhiteBalance;
    messageMap["/loopier/clip/uvc/whitebalance"] = &loopier::osc::MessageMapper::setUvcWhiteBalance;
    messageMap["/loopier/clip/uvc/gain"]         = &loopier::osc::MessageMapper::setUvcGain;
    messageMap["/loopier/clip/uvc/brightness"]   = &loopier::osc::MessageMapper::setUvcBrightness;
    messageMap["/loopier/clip/uvc/contrast"]     = &loopier::osc::MessageMapper::setUvcContrast;
    messageMap["/loopier/clip/uvc/saturation"]   = &loopier::osc::MessageMapper::setUvcSaturation;
    messageMap["/loopier/clip/uvc/sharpness"]    = &loopier::osc::MessageMapper::setUvcSharpness;
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::printMessage(Message & msg)
{
    osc::printMessage(msg, "OSC:");
    ConsoleUI::print(osc::getSimplifiedMessage(msg));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::mapMessageToFunc(Message & msg)
{
    // Look up the processor for this message address
    map<string, mappedFunc>::iterator iter = messageMap.find(msg.getAddress());
    if (iter != messageMap.end()) {
        (this->*(iter->second))(msg); // call the processor method for this message
        printMessage(msg);
    } else if (ofIsStringInString(msg.getAddress(), "selection")){
        fromSelectionToClip(msg);
    } else {
        ofLogWarning() << "Unhandled OSC message: " << msg.getAddress();
    }
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::fromSelectionToClip(Message & msg)
{
    // replace 'selection' by 'clip'
    string address = msg.getAddress();
    ofStringReplace(address, "selection", "clip");
    Message newMsg;
    // get names of selected clips
    vector<string> clipnames = clipManager->getSelectedClipnames();
    // iterate clipnames
    for (auto &clipname: clipnames) {
        newMsg.clear();
        newMsg.setAddress(address);
        // add clipname as first message argument
        newMsg.addStringArg(clipname);
        // add rest of original arguments
        for (int i = 0; i < msg.getNumArgs(); i++) {
            if (msg.getArgType(i) == OFXOSC_TYPE_INT32) {
                newMsg.addIntArg(msg.getArgAsInt(i));
            } else if (msg.getArgType(i) == OFXOSC_TYPE_FLOAT) {
                newMsg.addFloatArg(msg.getArgAsFloat(i));
            } else if (msg.getArgType(i) == OFXOSC_TYPE_TRUE || msg.getArgType(i) == OFXOSC_TYPE_FALSE ) {
                newMsg.addBoolArg(msg.getArgAsBool(i));
            } else if (msg.getArgType(i) == OFXOSC_TYPE_STRING) {
                newMsg.addStringArg(msg.getArgAsString(i));
            }
        }
        // map message again
        mapMessageToFunc(newMsg);
    }
}

//---------------------------------------------------------








//---------------------------------------------------------

//        TEST

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::osc::MessageMapper::test(const Message & msg)
{
    ClipPtr clip = clipManager->getClip(msg.getArgAsString(0));
    
}







//---------------------------------------------------------

//        APPLICATION

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::osc::MessageMapper::quit(const Message & msg)
{
    ofExit();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::fullscreen(const Message & msg)
{
    ofToggleFullscreen();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::move(const Message & msg)
{
    ofSetFullscreen(false);
    float x = msg.getArgAsFloat(1) * ofGetScreenWidth();
    float y = msg.getArgAsFloat(2) * ofGetScreenHeight();
    ofSetWindowPosition(x, y);
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::loadResources(const Message & msg)
{
    vector<string> resourcenames;
    for (int i = 0; i < msg.getNumArgs(); i++) {
        resourcenames.push_back(msg.getArgAsString(i));
    }
    
    resource::loadResources(resourcenames);
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::clearResources(const Message & msg)
{
    resource::clearResourceList();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::loadKeymap(const Message & msg)
{
    app::loadKeymap(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::loadScriptFile(const Message & msg)
{
    script::loadScriptFile(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::loadAllScripts(const Message & msg)
{
    script::loadScripts();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::clearScriptList(const Message & msg)
{
    script::clearScriptList();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::runScript(const Message & msg)
{
    script::runScript(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::loadAndRunScript(const Message & msg)
{
    script::loadScriptFile(msg.getArgAsString(0));
    script::runScript(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::listScriptNames(const Message & msg)
{
    //            command::getCommandLibraryNames(msg.getArgAsString(0));
    sendScriptNames();
}








//---------------------------------------------------------

//        ONE CLIP

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::osc::MessageMapper::newClip(const Message & msg)
{
    int n = msg.getNumArgs();
    if      (n == 1)    clipManager->newClip(msg.getArgAsString(0));
    else if (n == 2)    clipManager->newClip(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::newClipFromBlob(const Message & msg)
{
    int n = msg.getNumArgs();
    if      (n == 1)    clipManager->newClipFromBlob(msg.getArgAsString(0));
    else if (n == 2)    clipManager->newClipFromBlob(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::removeClip(const Message & msg)
{
    clipManager->removeClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::resetClip(const Message & msg)
{
    clipManager->resetClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::selectClip(const Message & msg)
{
    clipManager->selectClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::deselectClip(const Message & msg)
{
    clipManager->deselectClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::selectNextClip(const Message & msg)
{
    clipManager->selectNextClip();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::selectAllClips(const Message & msg)
{
    clipManager->selectAllClips();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::deselectAllClips(const Message & msg)
{
    clipManager->deselectAllClips();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::addClipChild(const Message & msg)
{
    clipManager->addClipChild(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::removeClipChild(const Message & msg)
{
    clipManager->removeClipChild(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::clearClipChildren(const Message & msg)
{
    clipManager->clearClipChildren(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::listClipChildren(const Message & msg)
{
    sendClipChildrenNames(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipDrawOrder(const Message & msg)
{
    clipManager->setClipDrawOrder(msg.getArgAsString(0), msg.getArgAsInt(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::bringClipToFront(const Message & msg)
{
    clipManager->bringClipToFront(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::bringClipForward(const Message & msg)
{
    clipManager->bringClipForward(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::sendClipBackward(const Message & msg)
{
    clipManager->sendClipBackward(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::sendClipToBack(const Message & msg)
{
    clipManager->sendClipToBack(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setBackgroundClip(const Message & msg)
{
    clipManager->setBackgroundClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setPublicClip(const Message & msg)
{
    clipManager->setPublicClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setPrivateClip(const Message & msg)
{
    clipManager->setPrivateClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::listLayers(const Message & msg)
{
    clipManager->listLayers();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::scaleUpClip(const Message & msg)
{
    clipManager->scaleUpClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::scaleDownClip(const Message & msg)
{
    clipManager->scaleDownClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::scaleClip(const Message & msg)
{
    clipManager->scaleClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipWidth(const Message & msg)
{
    clipManager->setClipWidth(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipHeight(const Message & msg)
{
    clipManager->setClipHeight(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::resetClipScale(const Message & msg)
{
    clipManager->resetClipScale(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipVFlip(const Message & msg)
{
    clipManager->setClipVFlip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipHFlip(const Message & msg)
{
    clipManager->setClipHFlip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::toggleFullscreenClip(const Message & msg)
{
    clipManager->toggleFullscreenClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::toggleClipVisibility(const Message & msg)
{
    clipManager->toggleClipVisibility(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::showClip(const Message & msg)
{
    clipManager->showClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::hideClip(const Message & msg)
{
    clipManager->hideClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::toggleClipName(const Message & msg)
{
    clipManager->toggleName(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::showClipName(const Message & msg)
{
    clipManager->showName(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::hideClipName(const Message & msg)
{
    clipManager->hideName(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipMask(const Message & msg)
{
    clipManager->setClipMask(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::enableClipMask(const Message & msg)
{
    clipManager->enableClipMask(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::disableClipMask(const Message & msg)
{
    clipManager->disableClipMask(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipHolesMask(const Message & msg)
{
    clipManager->setClipHolesMask(msg.getArgAsString(0));
}


// PLAY
//---------------------------------------------------------
void loopier::osc::MessageMapper::playClip(const Message & msg)
{
    clipManager->playClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::stopClip(const Message & msg)
{
    clipManager->stopClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::pauseClip(const Message & msg)
{
    clipManager->pauseClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipLoopState(const Message & msg)
{
    string arg = msg.getArgAsString(1);
    LoopType looptype = LoopType::normal;
    
    if      (arg == "palindrome")   looptype = LoopType::palindrome;
    else if (arg == "none" )        looptype = LoopType::none;
    else if (arg == "once" )        looptype = LoopType::once;
    
    clipManager->setClipLoopState(msg.getArgAsString(0), looptype);
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipPlayDirection(const Message & msg)
{
    string arg = msg.getArgAsString(1);
    PlayDirection direction = PlayDirection::normal;
    
    if (arg == "reverse")   direction = PlayDirection::reverse;
    
    clipManager->setClipPlayDirection(msg.getArgAsString(0), direction);
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipSpeed(const Message & msg)
{
    clipManager->setClipSpeed(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

// EDIT

//---------------------------------------------------------
void loopier::osc::MessageMapper::addFrame(const Message & msg)
{
    clipManager->addFrame(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::insertFrame(const Message & msg)
{
    clipManager->insertFrame(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::removeFrame(const Message & msg)
{
    clipManager->removeFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::clearFrames(const Message & msg)
{
    clipManager->clearFrames(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::saveFrames(const Message & msg)
{
    clipManager->saveFrames(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::loadFrames(const Message & msg)
{
    clipManager->loadFrames(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::firstFrame(const Message & msg)
{
    clipManager->firstFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::nextFrame(const Message & msg)
{
    clipManager->nextFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::previousFrame(const Message & msg)
{
    clipManager->previousFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::lastFrame(const Message & msg)
{
    clipManager->lastFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::goToFrame(const Message & msg)
{
    clipManager->goToFrame(msg.getArgAsString(0), msg.getArgAsInt(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::saveClip(const Message & msg)
{
    clipManager->saveClip(msg.getArgAsString(0));
}

// MOVE
//---------------------------------------------------------
void loopier::osc::MessageMapper::moveClipTo(const Message & msg)
{
    clipManager->moveClipTo(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::centerClip(const Message & msg)
{
    clipManager->centerClip(msg.getArgAsString(0));
}


// COLOR
//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipColor(const Message & msg)
{
    //    ofColor color = loopier::osc::MessageMapper::getColorFromMessage(msg);
    //    clipManager->setClipColor(msg.getArgAsString(0), color);
    if (msg.getNumArgs() == 2) clipManager->setClipColor(msg.getArgAsString(0), msg.getArgAsFloat(1));
    if (msg.getNumArgs() == 3) clipManager->setClipColor(msg.getArgAsString(0),
                                                  msg.getArgAsFloat(1),
                                                  msg.getArgAsFloat(2));
    if (msg.getNumArgs() == 4) clipManager->setClipColor(msg.getArgAsString(0),
                                                  msg.getArgAsFloat(1),
                                                  msg.getArgAsFloat(2),
                                                  msg.getArgAsFloat(3));
    if (msg.getNumArgs() == 5) clipManager->setClipColor(msg.getArgAsString(0),
                                                  msg.getArgAsFloat(1),
                                                  msg.getArgAsFloat(2),
                                                  msg.getArgAsFloat(3),
                                                  msg.getArgAsFloat(4));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setClipAlpha(const Message & msg)
{
    clipManager->setClipAlpha(msg.getArgAsString(0), msg.getArgAsFloat(1));
}







//---------------------------------------------------------

//        CLIP COLLECTIONS

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::osc::MessageMapper::loadClipLibrary(const Message & msg)
{
    clipManager->loadClipLibrary(msg.getArgAsString(0));
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::clearClips(const Message & msg)
{
    clipManager->clearAll();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::listClipNames(const Message & msg)
{
    clipManager->listAll();
    sendClipNames();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::listResourceNames(const Message & msg)
{
    //    listResourceNames();
    resource::listAllResources();
    sendResourceNames();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::listCameraNames(const Message & msg)
{
    resource::listCameras();
    sendCameraNames();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::listClipLibraryNames(const Message & msg)
{
    clipManager->listClipLibraryNames();
    sendLibraryNames();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::toggleClipNames(const Message & msg)
{
    clipManager->toggleNames();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::showClipNames(const Message & msg)
{
    clipManager->showNames();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::hideClipNames(const Message & msg)
{
    clipManager->hideNames();
}







//---------------------------------------------------------

//        Syphon

//---------------------------------------------------------

//---------------------------------------------------------
void loopier::osc::MessageMapper::setSyphonServerName(const Message & msg)
{
    resource::setSyphonServerName(msg.getArgAsString(0),
                                  msg.getArgAsString(1),
                                  msg.getArgAsString(2));
}







//---------------------------------------------------------

//        CV

//---------------------------------------------------------

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvColor(const Message & msg)
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
void loopier::osc::MessageMapper::setCvThreshold(const Message & msg)
{
    cv::setThreshold(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvMinArea(const Message & msg)
{
    cv::setMinArea(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvMaxArea(const Message & msg)
{
    cv::setMaxArea(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvHoles(const Message & msg)
{
    cv::setFindHoles(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvHolesMask(const Message & msg)
{
    cv::setHolesMask(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvMaxBlobs(const Message & msg)
{
    cv::setMaxBlobs(msg.getArgAsInt(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvInputClip(const Message & msg)
{
    cv::setInputClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvDeviceId(const Message & msg)
{
    cv::setDeviceId(msg.getArgAsInt(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::toggleCvVisibility(const Message & msg)
{
    cv::toggleVisibility();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::showCv(const Message & msg)
{
    cv::show();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::hideCv(const Message & msg)
{
    cv::hide();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setCvDetectionArea(const Message & msg)
{
    ofRectangle rect(msg.getArgAsFloat(0), msg.getArgAsFloat(1),
                     msg.getArgAsFloat(2), msg.getArgAsFloat(3));
    cv::setDetectionArea(rect);
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::selectBlob(const Message & msg)
{
    cv::selectBlob();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::deselectBlob(const Message & msg)
{
    cv::deselectBlob();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::selectAllBlobs(const Message & msg)
{
    cv::selectAllBlobs();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::deselectAllBlobs(const Message & msg)
{
    cv::deselectAllBlobs();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::firstBlob(const Message & msg)
{
    cv::firstBlob();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::nextBlob(const Message & msg)
{
    cv::nextBlob();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::previousBlob(const Message & msg)
{
    cv::previousBlob();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::lastBlob(const Message & msg)
{
    cv::lastBlob();
}






//---------------------------------------------------------

//        CONSOLE

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::osc::MessageMapper::setConsoleColor(const Message & msg)
{
    ConsoleUI::setColor(loopier::osc::MessageMapper::getColorFromMessage(msg));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setConsoleAlpha(const Message & msg)
{
    ConsoleUI::setAlpha(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setConsolePrompt(const Message & msg)
{
    ConsoleUI::setPrompt(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::printToConsole(const Message & msg)
{
    ConsoleUI::print(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setConsoleLinesNum(const Message & msg)
{
    ConsoleUI::setMaxLines(msg.getArgAsInt(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::toggleConsole(const Message & msg)
{
    ConsoleUI::toggle();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::showConsole(const Message & msg)
{
    ConsoleUI::show();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::hideConsole(const Message & msg)
{
    ConsoleUI::hide();
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::moveConsole(const Message & msg)
{
    ConsoleUI::setPosition(msg.getArgAsFloat(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setConsoleFont(const Message & msg)
{
    ConsoleUI::setFont(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setConsoleFontSize(const Message & msg)
{
    ConsoleUI::setFontSize(msg.getArgAsInt(0));
}







//---------------------------------------------------------

//        UVC

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::osc::MessageMapper::addUvcCamera(const Message & msg)
{
    int     vendorId        = msg.getArgAsInt(0);
    int     productId       = msg.getArgAsInt(1);
    int     interfaceNum    = msg.getArgAsInt(2);
    string  name            = msg.getArgAsString(3);
    uvc::addCamera(vendorId, productId, interfaceNum, name);
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::useUvcCamera(const Message & msg)
{
    uvc::useCamera(msg.getArgAsString(0)); // camera name
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcAutoExposure(const Message & msg)
{
    uvc::setAutoExposure(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcExposure(const Message & msg)
{
    uvc::setExposure(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcAutoFocus(const Message & msg)
{
    uvc::setAutoFocus(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcFocus(const Message & msg)
{
    uvc::setFocus(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcAutoWhiteBalance(const Message & msg)
{
    uvc::setAutoWhiteBalance(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcWhiteBalance(const Message & msg)
{
    uvc::setWhiteBalance(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcGain(const Message & msg)
{
    uvc::setGain(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcBrightness(const Message & msg)
{
    uvc::setBrightness(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcContrast(const Message & msg)
{
    uvc::setContrast(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcSaturation(const Message & msg)
{
    uvc::setSaturation(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::osc::MessageMapper::setUvcSharpness(const Message & msg)
{
    uvc::setSharpness(msg.getArgAsFloat(0));
}






//---------------------------------------------------------

//        SENDERS

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::osc::MessageMapper::sendClipNames()
{
    vector<string> names = clipManager->getNamesList();
    Message msg;
    
    msg.setAddress("/loopier/clip/clipnames");
    
    for (const auto &item : names) {
        //                if (item == "cv" || item == "syphon") continue; // skip cv and syphon clips
        msg.addStringArg(item);
    };
    
    osc.sendMessage(msg);
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::sendResourceNames()
{
    vector<string> names = loopier::resource::getResourceNames();
    Message msg;
    
    msg.setAddress("/loopier/clip/resourcenames");
    
    for (const auto &item : names) {  msg.addStringArg(item); };
    
    osc.sendMessage(msg);
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::sendCameraNames()
{
    vector<string> names = loopier::resource::getCameraNames();
    Message msg;
    
    msg.setAddress("/loopier/clip/cameranames");
    
    for (const auto &item : names) {  msg.addStringArg(item); };
    
    osc.sendMessage(msg);
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::sendLibraryNames()
{
    vector<string> names = clipManager->getClipLibraryNames();
    Message msg;
    
    msg.setAddress("/loopier/clip/clips/librarynames");
    
    for (const auto &item : names) {
        msg.addStringArg(item);
    };
    
    osc.sendMessage(msg);
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::listClipInfo(const Message &msg)
{
    sendClipInfo(msg.getArgAsString(0));
}


//---------------------------------------------------------
void loopier::osc::MessageMapper::sendClipInfo(const string clipname)
{
    if (!clipManager->exists(clipname)) return;
    ClipPtr clip = clipManager->getClip(clipname);
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
    //            msg.addStringArg(clip->getParentName());
    msg.addFloatArg(clip->getOffset().x);
    msg.addFloatArg(clip->getOffset().y);
    
    osc.sendMessage(msg);
}




//---------------------------------------------------------
void loopier::osc::MessageMapper::sendScriptNames()
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
void loopier::osc::MessageMapper::sendClipChildrenNames(const string clipname)
{
    vector<string> names = clipManager->getClipChildrenNames(clipname);
    Message msg;
    
    msg.setAddress("/loopier/clip/clip/children");
    
    for (const auto &item : names) {
        msg.addStringArg(item);
    };
    
    
    osc.sendMessage(msg);
}




//---------------------------------------------------------

//        CONSOLE

//---------------------------------------------------------


//---------------------------------------------------------
ofColor loopier::osc::MessageMapper::getColorFromMessage(const Message & msg)
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
