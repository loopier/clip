//
//  MessageMapper.cpp
//  clip
//
//  Created by roger on 28/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "MessageMapper.h"


//---------------------------------------------------------
//loopier::MessageMapper::MessageMapper()
//{
//
//}
//
////---------------------------------------------------------
//loopier::MessageMapper::~MessageMapper()
//{
//
//}

//---------------------------------------------------------
void loopier::MessageMapper::setup()
{
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &loopier::MessageMapper::mapMessageToFunc);
    setupAppCommandsMap();
    setupRecorderCommandsMap();
    setupClipCommandsMap();
    setupClipCollectionCommandsMap();
    setupSyphonCommandsMap();
    setupCvCommandsMap();
    setupConsoleCommandsMap();
    setupUvcCommandsMap();

    loopier::ConsoleUI::setup();
}


//---------------------------------------------------------
void loopier::MessageMapper::setupAppCommandsMap()
{
    // Application commands
    messageMap["/loopier/clip/app/test"]       = &loopier::MessageMapper::test;
    
    // Application commands
    messageMap["/loopier/clip/app/quit"]        = &loopier::MessageMapper::quit;
    messageMap["/loopier/clip/app/fullscreen"]  = &loopier::MessageMapper::fullscreen;
    messageMap["/loopier/clip/app/move"]        = &loopier::MessageMapper::move;
}


//---------------------------------------------------------
void loopier::MessageMapper::setupRecorderCommandsMap()
{
    // Application commands
    messageMap["/loopier/clip/app/rec"]     = &loopier::MessageMapper::toggleRecording;
    messageMap["/loopier/clip/app/record"]  = &loopier::MessageMapper::toggleRecording;
    messageMap["/loopier/clip/rec"]         = &loopier::MessageMapper::toggleRecording;
    messageMap["/loopier/clip/rec/start"]   = &loopier::MessageMapper::startRecording;
    messageMap["/loopier/clip/rec/stop"]    = &loopier::MessageMapper::stopRecording;
}


//---------------------------------------------------------
void loopier::MessageMapper::setupClipCommandsMap()
{

    // One Clip commands
    messageMap["/loopier/clip/clip/new"]                = &loopier::MessageMapper::newClip;
    messageMap["/loopier/clip/clip/replace"]            = &loopier::MessageMapper::newClip;
    messageMap["/loopier/clip/clip/replaceblob"]        = &loopier::MessageMapper::newClipFromBlob;
    messageMap["/loopier/clip/clip/remove"]             = &loopier::MessageMapper::removeClip;
    messageMap["/loopier/clip/clip/reset"]              = &loopier::MessageMapper::resetClip;
    messageMap["/loopier/clip/clip/select"]             = &loopier::MessageMapper::selectClip;
    // parent
    messageMap["/loopier/clip/clip/parent"]         = &loopier::MessageMapper::setParent;
    messageMap["/loopier/clip/clip/removeparent"]   = &loopier::MessageMapper::removeParent;
    messageMap["/loopier/clip/clip/offset"]         = &loopier::MessageMapper::setOffset;
    // Arrange
    messageMap["/loopier/clip/clip/depth"]          = &loopier::MessageMapper::setClipDrawOrder;
    messageMap["/loopier/clip/clip/front"]          = &loopier::MessageMapper::bringClipToFront;
    messageMap["/loopier/clip/clip/forward"]        = &loopier::MessageMapper::bringClipForward;
    messageMap["/loopier/clip/clip/backward"]       = &loopier::MessageMapper::sendClipBackward;
    messageMap["/loopier/clip/clip/back"]           = &loopier::MessageMapper::sendClipToBack;
    messageMap["/loopier/clip/clip/background"]     = &loopier::MessageMapper::setBackgroundClip;
    messageMap["/loopier/clip/clip/public"]         = &loopier::MessageMapper::setPublicClip;
    messageMap["/loopier/clip/clip/private"]        = &loopier::MessageMapper::setPrivateClip;
    // TODO: Move to ../app/.. or ../clips/..
    messageMap["/loopier/clip/clip/layers"]         = &loopier::MessageMapper::listLayers;
    // Size
    messageMap["/loopier/clip/clip/scaleup"]            = &loopier::MessageMapper::scaleUpClip;
    messageMap["/loopier/clip/clip/scaledown"]          = &loopier::MessageMapper::scaleDownClip;
    messageMap["/loopier/clip/clip/scale"]              = &loopier::MessageMapper::scaleClip;
    messageMap["/loopier/clip/clip/xscale"]             = &loopier::MessageMapper::setClipWidth;
    messageMap["/loopier/clip/clip/yscale"]             = &loopier::MessageMapper::setClipHeight;
    messageMap["/loopier/clip/clip/resetscale"]         = &loopier::MessageMapper::resetClipScale;
    messageMap["/loopier/clip/clip/fullscreen"]         = &loopier::MessageMapper::toggleFullscreenClip;
    // Orientation
    messageMap["/loopier/clip/clip/vflip"]              = &loopier::MessageMapper::setClipVFlip;
    messageMap["/loopier/clip/clip/hflip"]              = &loopier::MessageMapper::setClipHFlip;
    // Visibility
    messageMap["/loopier/clip/clip/togglevisibility"]   = &loopier::MessageMapper::toggleClipVisibility;
    messageMap["/loopier/clip/clip/show"]               = &loopier::MessageMapper::showClip;
    messageMap["/loopier/clip/clip/hide"]               = &loopier::MessageMapper::hideClip;
    // FX
    messageMap["/loopier/clip/clip/mask"]               = &loopier::MessageMapper::setClipMask;
    messageMap["/loopier/clip/clip/maskon"]             = &loopier::MessageMapper::enableClipMask;
    messageMap["/loopier/clip/clip/maskoff"]            = &loopier::MessageMapper::disableClipMask;
    // play
    messageMap["/loopier/clip/clip/play"]       = &loopier::MessageMapper::playClip;
    messageMap["/loopier/clip/clip/stop"]       = &loopier::MessageMapper::stopClip;
    messageMap["/loopier/clip/clip/pause"]      = &loopier::MessageMapper::pauseClip;
    messageMap["/loopier/clip/clip/loop"]       = &loopier::MessageMapper::setClipLoopState;
    messageMap["/loopier/clip/clip/speed"]      = &loopier::MessageMapper::setClipSpeed;
    // edit
    messageMap["/loopier/clip/clip/addframe"]           = &loopier::MessageMapper::addFrame;
    messageMap["/loopier/clip/clip/insertframe"]        = &loopier::MessageMapper::insertFrame;
    messageMap["/loopier/clip/clip/removeframe"]        = &loopier::MessageMapper::removeFrame;
    messageMap["/loopier/clip/clip/clearframes"]        = &loopier::MessageMapper::clearFrames;
    messageMap["/loopier/clip/clip/saveframes"]         = &loopier::MessageMapper::saveFrames;
    messageMap["/loopier/clip/clip/loadframes"]         = &loopier::MessageMapper::loadFrames;
    messageMap["/loopier/clip/clip/firstframe"]         = &loopier::MessageMapper::firstFrame;
    messageMap["/loopier/clip/clip/nextframe"]          = &loopier::MessageMapper::nextFrame;
    messageMap["/loopier/clip/clip/previousframe"]      = &loopier::MessageMapper::previousFrame;
    messageMap["/loopier/clip/clip/lastframe"]          = &loopier::MessageMapper::lastFrame;
    messageMap["/loopier/clip/clip/gotoframe"]          = &loopier::MessageMapper::goToFrame;
    messageMap["/loopier/clip/clip/save"]               = &loopier::MessageMapper::saveClip;
    // move
    messageMap["/loopier/clip/clip/moveto"] = &loopier::MessageMapper::moveClipTo;
    messageMap["/loopier/clip/clip/center"] = &loopier::MessageMapper::centerClip;
    // color
    messageMap["/loopier/clip/clip/color"]  = &loopier::MessageMapper::setClipColor;
    messageMap["/loopier/clip/clip/alpha"]  = &loopier::MessageMapper::setClipAlpha;
}


//---------------------------------------------------------
void loopier::MessageMapper::setupClipCollectionCommandsMap()
{

    // Clip collection commands
    messageMap["/loopier/clip/clips/clearall"]      = &loopier::MessageMapper::clearClips;
    messageMap["/loopier/clip/clips/listnames"]     = &loopier::MessageMapper::listClipNames;
    messageMap["/loopier/clip/clips/listresources"] = &loopier::MessageMapper::listResourceNames;
    messageMap["/loopier/clip/clips/togglenames"]   = &loopier::MessageMapper::toggleClipNames;
    messageMap["/loopier/clip/clips/shownames"]     = &loopier::MessageMapper::showClipNames;
    messageMap["/loopier/clip/clips/hidenames"]     = &loopier::MessageMapper::hideClipNames;
    
}


//---------------------------------------------------------
void loopier::MessageMapper::setupSyphonCommandsMap()
{
    // Syphon
    messageMap["/loopier/clip/syphon/servername"]   = &loopier::MessageMapper::setSyphonServerName;
}


//---------------------------------------------------------
void loopier::MessageMapper::setupCvCommandsMap()
{
    // CV commands
    messageMap["/loopier/clip/cv/setinput"]         = &loopier::MessageMapper::setCvInputClip;
    messageMap["/loopier/clip/cv/color"]            = &loopier::MessageMapper::setCvColor;
    messageMap["/loopier/clip/cv/threshold"]        = &loopier::MessageMapper::setCvThreshold;
    messageMap["/loopier/clip/cv/minArea"]          = &loopier::MessageMapper::setCvMinArea;
    messageMap["/loopier/clip/cv/maxArea"]          = &loopier::MessageMapper::setCvMaxArea;
    messageMap["/loopier/clip/cv/holes"]            = &loopier::MessageMapper::setCvHoles;
    messageMap["/loopier/clip/cv/show"]             = &loopier::MessageMapper::showCv;
    messageMap["/loopier/clip/cv/hide"]             = &loopier::MessageMapper::hideCv;
    messageMap["/loopier/clip/cv/detectionarea"]    = &::loopier::MessageMapper::setCvDetectionArea;
    messageMap["/loopier/clip/cv/maxblobs"]         = &loopier::MessageMapper::setCvMaxBlobs;
    messageMap["/loopier/clip/cv/select"]           = &loopier::MessageMapper::selectBlob;
    messageMap["/loopier/clip/cv/deselect"]         = &loopier::MessageMapper::deselectBlob;
    messageMap["/loopier/clip/cv/first"]            = &loopier::MessageMapper::firstBlob;
    messageMap["/loopier/clip/cv/next"]             = &loopier::MessageMapper::nextBlob;
    messageMap["/loopier/clip/cv/previous"]         = &loopier::MessageMapper::previousBlob;
    messageMap["/loopier/clip/cv/last"]             = &loopier::MessageMapper::lastBlob;
}


//---------------------------------------------------------
void loopier::MessageMapper::setupConsoleCommandsMap()
{
    // Console commands
    messageMap["/loopier/clip/console/color"]       = &loopier::MessageMapper::setConsoleColor;
    messageMap["/loopier/clip/console/alpha"]       = &loopier::MessageMapper::setConsoleAlpha;
    messageMap["/loopier/clip/console/prompt"]      = &loopier::MessageMapper::setConsolePrompt;
    messageMap["/loopier/clip/console/print"]       = &loopier::MessageMapper::printToConsole;
    messageMap["/loopier/clip/console/lines"]       = &loopier::MessageMapper::setConsoleLinesNum;
    messageMap["/loopier/clip/console/toggle"]      = &loopier::MessageMapper::toggleConsole;
    messageMap["/loopier/clip/console/show"]        = &loopier::MessageMapper::showConsole;
    messageMap["/loopier/clip/console/hide"]        = &loopier::MessageMapper::hideConsole;
    messageMap["/loopier/clip/console/moveto"]      = &loopier::MessageMapper::moveConsole;
    messageMap["/loopier/clip/console/font"]        = &loopier::MessageMapper::setConsoleFont;
    messageMap["/loopier/clip/console/fontsize"]    = &loopier::MessageMapper::setConsoleFontSize;
}


//---------------------------------------------------------
void loopier::MessageMapper::setupUvcCommandsMap()
{
    messageMap["/loopier/uvc/add"]          = &loopier::MessageMapper::addUvcCamera;
    messageMap["/loopier/uvc/use"]          = &loopier::MessageMapper::useUvcCamera;
    messageMap["/loopier/uvc/autoexposure"] = &loopier::MessageMapper::setUvcAutoExposure;
    messageMap["/loopier/uvc/exposure"]     = &loopier::MessageMapper::setUvcExposure;
    messageMap["/loopier/uvc/autofocus"]    = &loopier::MessageMapper::setUvcAutoFocus;
    messageMap["/loopier/uvc/focus"]        = &loopier::MessageMapper::setUvcFocus;
    messageMap["/loopier/uvc/autowhitebalance"] = &loopier::MessageMapper::setUvcAutoWhiteBalance;
    messageMap["/loopier/uvc/whitebalance"] = &loopier::MessageMapper::setUvcWhiteBalance;
    messageMap["/loopier/uvc/gain"]         = &loopier::MessageMapper::setUvcGain;
    messageMap["/loopier/uvc/brightness"]   = &loopier::MessageMapper::setUvcBrightness;
    messageMap["/loopier/uvc/contrast"]     = &loopier::MessageMapper::setUvcContrast;
    messageMap["/loopier/uvc/saturation"]   = &loopier::MessageMapper::setUvcSaturation;
    messageMap["/loopier/uvc/sharpness"]    = &loopier::MessageMapper::setUvcSharpness;
}


//---------------------------------------------------------
void loopier::MessageMapper::printMessage(Message & msg)
{
    loopier::printOscMessage(msg, "OSC:");
    loopier::ConsoleUI::print(loopier::getSimplifiedOscMessage(msg));
}

//---------------------------------------------------------
void loopier::MessageMapper::mapMessageToFunc(Message & msg)
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
void loopier::MessageMapper::test(const Message & msg)
{
    loopier::ClipPtr clip = loopier::clip::getClip(msg.getArgAsString(0));
    
}







//---------------------------------------------------------

//        APPLICATION

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::quit(const Message & msg)
{
    ofExit();
}

//---------------------------------------------------------
void loopier::MessageMapper::fullscreen(const Message & msg)
{
    ofToggleFullscreen();
}

//---------------------------------------------------------
void loopier::MessageMapper::move(const Message & msg)
{
    ofSetFullscreen(false);
    float x = msg.getArgAsFloat(1) * ofGetScreenWidth();
    float y = msg.getArgAsFloat(2) * ofGetScreenHeight();
    ofSetWindowPosition(x, y);
}







//---------------------------------------------------------

//        RECORDING

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::startRecording(const Message & msg)
{
    loopier::recorder::start();
}

//---------------------------------------------------------
void loopier::MessageMapper::stopRecording(const Message & msg)
{
    loopier::recorder::stop();
}

//---------------------------------------------------------
void loopier::MessageMapper::toggleRecording(const Message & msg)
{
    loopier::recorder::toggle();
}








//---------------------------------------------------------

//        ONE CLIP

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::newClip(const Message & msg)
{
    int n = msg.getNumArgs();
    if      (n == 1)    loopier::clip::newClip(msg.getArgAsString(0));
    else if (n == 2)    loopier::clip::newClip(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::newClipFromBlob(const Message & msg)
{
    int n = msg.getNumArgs();
    if      (n == 1)    loopier::clip::newClipFromBlob(msg.getArgAsString(0));
    else if (n == 2)    loopier::clip::newClipFromBlob(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::removeClip(const Message & msg)
{
    loopier::clip::removeClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::resetClip(const Message & msg)
{
    loopier::clip::resetClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::selectClip(const Message & msg)
{
    loopier::clip::selectClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setParent(const Message & msg)
{
    loopier::clip::setParentClip(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::removeParent(const Message & msg)
{
    loopier::clip::removeParentClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setOffset(const Message & msg)
{
    loopier::clip::setOffsetToParentClip(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipDrawOrder(const Message & msg)
{
    loopier::clip::setClipDrawOrder(msg.getArgAsString(0), msg.getArgAsInt(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::bringClipToFront(const Message & msg)
{
    loopier::clip::bringClipToFront(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::bringClipForward(const Message & msg)
{
    loopier::clip::bringClipForward(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::sendClipBackward(const Message & msg)
{
    loopier::clip::sendClipBackward(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::sendClipToBack(const Message & msg)
{
    loopier::clip::sendClipToBack(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setBackgroundClip(const Message & msg)
{
    loopier::clip::setBackgroundClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setPublicClip(const Message & msg)
{
    loopier::clip::setPublicClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setPrivateClip(const Message & msg)
{
    loopier::clip::setPrivateClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::listLayers(const Message & msg)
{
    loopier::clip::listLayers();
}

//---------------------------------------------------------
void loopier::MessageMapper::scaleUpClip(const Message & msg)
{
    loopier::clip::scaleUpClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::scaleDownClip(const Message & msg)
{
    loopier::clip::scaleDownClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::scaleClip(const Message & msg)
{
    loopier::clip::scaleClip(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipWidth(const Message & msg)
{
    loopier::clip::setClipWidth(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipHeight(const Message & msg)
{
    loopier::clip::setClipHeight(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::resetClipScale(const Message & msg)
{
    loopier::clip::resetClipScale(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipVFlip(const Message & msg)
{
    loopier::clip::setClipVFlip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipHFlip(const Message & msg)
{
    loopier::clip::setClipHFlip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::toggleFullscreenClip(const Message & msg)
{
    loopier::clip::toggleFullscreenClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::toggleClipVisibility(const Message & msg)
{
    loopier::clip::toggleClipVisibility(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::showClip(const Message & msg)
{
    loopier::clip::showClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::hideClip(const Message & msg)
{
    loopier::clip::hideClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipMask(const Message & msg)
{
    loopier::clip::setClipMask(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::enableClipMask(const Message & msg)
{
    loopier::clip::enableClipMask(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::disableClipMask(const Message & msg)
{
    loopier::clip::disableClipMask(msg.getArgAsString(0));
}


// PLAY
//---------------------------------------------------------
void loopier::MessageMapper::playClip(const Message & msg)
{
    loopier::clip::playClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::stopClip(const Message & msg)
{
    loopier::clip::stopClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::pauseClip(const Message & msg)
{
    loopier::clip::pauseClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipLoopState(const Message & msg)
{
    string arg = msg.getArgAsString(1);
    loopier::LoopType looptype = loopier::LoopType::normal;
    
    if      (arg == "palindrome")   looptype = loopier::LoopType::palindrome;
    else if (arg == "none" )        looptype = loopier::LoopType::none;
    else if (arg == "once" )        looptype = loopier::LoopType::once;
    
    loopier::clip::setClipLoopState(msg.getArgAsString(0), looptype);
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipSpeed(const Message & msg)
{
    loopier::clip::setClipSpeed(msg.getArgAsString(0), msg.getArgAsFloat(1));
}

// EDIT

//---------------------------------------------------------
void loopier::MessageMapper::addFrame(const Message & msg)
{
    loopier::clip::addFrame(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::insertFrame(const Message & msg)
{
    loopier::clip::insertFrame(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::removeFrame(const Message & msg)
{
    loopier::clip::removeFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::clearFrames(const Message & msg)
{
    loopier::clip::clearFrames(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::saveFrames(const Message & msg)
{
    loopier::clip::saveFrames(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::loadFrames(const Message & msg)
{
    loopier::clip::loadFrames(msg.getArgAsString(0), msg.getArgAsString(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::firstFrame(const Message & msg)
{
    loopier::clip::firstFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::nextFrame(const Message & msg)
{
    loopier::clip::nextFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::previousFrame(const Message & msg)
{
    loopier::clip::previousFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::lastFrame(const Message & msg)
{
    loopier::clip::lastFrame(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::goToFrame(const Message & msg)
{
    loopier::clip::goToFrame(msg.getArgAsString(0), msg.getArgAsInt(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::saveClip(const Message & msg)
{
    loopier::clip::saveClip(msg.getArgAsString(0));
}

// MOVE
//---------------------------------------------------------
void loopier::MessageMapper::moveClipTo(const Message & msg)
{
    loopier::clip::moveClipTo(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
}

//---------------------------------------------------------
void loopier::MessageMapper::centerClip(const Message & msg)
{
    loopier::clip::centerClip(msg.getArgAsString(0));
}


// COLOR
//---------------------------------------------------------
void loopier::MessageMapper::setClipColor(const Message & msg)
{
//    ofColor color = loopier::MessageMapper::getColorFromMessage(msg);
//    loopier::clip::setClipColor(msg.getArgAsString(0), color);
    if (msg.getNumArgs() == 2) loopier::clip::setClipColor(msg.getArgAsString(0), msg.getArgAsFloat(1));
    if (msg.getNumArgs() == 3) loopier::clip::setClipColor(msg.getArgAsString(0),
                                                           msg.getArgAsFloat(1),
                                                           msg.getArgAsFloat(2));
    if (msg.getNumArgs() == 4) loopier::clip::setClipColor(msg.getArgAsString(0),
                                                           msg.getArgAsFloat(1),
                                                           msg.getArgAsFloat(2),
                                                           msg.getArgAsFloat(3));
    if (msg.getNumArgs() == 5) loopier::clip::setClipColor(msg.getArgAsString(0),
                                                           msg.getArgAsFloat(1),
                                                           msg.getArgAsFloat(2),
                                                           msg.getArgAsFloat(3),
                                                           msg.getArgAsFloat(4));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipAlpha(const Message & msg)
{
    loopier::clip::setClipAlpha(msg.getArgAsString(0), msg.getArgAsFloat(1));
}







//---------------------------------------------------------

//        CLIP COLLECTIONS

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::clearClips(const Message & msg)
{
    loopier::clip::clearAll();
}

//---------------------------------------------------------
void loopier::MessageMapper::listClipNames(const Message & msg)
{
    loopier::clip::listAll();
}

//---------------------------------------------------------
void loopier::MessageMapper::listResourceNames(const Message & msg)
{
//    loopier::listResourceNames();
    loopier::resource::listAll();
}

//---------------------------------------------------------
void loopier::MessageMapper::toggleClipNames(const Message & msg)
{
    loopier::clip::toggleNames();
}

//---------------------------------------------------------
void loopier::MessageMapper::showClipNames(const Message & msg)
{
    loopier::clip::showNames();
}

//---------------------------------------------------------
void loopier::MessageMapper::hideClipNames(const Message & msg)
{
    loopier::clip::hideNames();
}







//---------------------------------------------------------

//        Syphon

//---------------------------------------------------------

//---------------------------------------------------------
void loopier::MessageMapper::setSyphonServerName(const Message & msg)
{
    loopier::resource::setSyphonServerName(msg.getArgAsString(0),
                                           msg.getArgAsString(1),
                                           msg.getArgAsString(2));
}







//---------------------------------------------------------

//        CV

//---------------------------------------------------------

//---------------------------------------------------------
void loopier::MessageMapper::setCvColor(const Message & msg)
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
void loopier::MessageMapper::setCvThreshold(const Message & msg)
{
    loopier::cv::setThreshold(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvMinArea(const Message & msg)
{
    loopier::cv::setMinArea(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvMaxArea(const Message & msg)
{
    loopier::cv::setMaxArea(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvHoles(const Message & msg)
{
    loopier::cv::setFindHoles(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvMaxBlobs(const Message & msg)
{
    loopier::cv::setMaxBlobs(msg.getArgAsInt(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvInputClip(const Message & msg)
{
    loopier::cv::setInputClip(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvDeviceId(const Message & msg)
{
    loopier::cv::setDeviceId(msg.getArgAsInt(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::showCv(const Message & msg)
{
    loopier::cv::show();
}

//---------------------------------------------------------
void loopier::MessageMapper::hideCv(const Message & msg)
{
    loopier::cv::hide();
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvDetectionArea(const Message & msg)
{
    ofRectangle rect(msg.getArgAsFloat(0), msg.getArgAsFloat(1),
                     msg.getArgAsFloat(2), msg.getArgAsFloat(3));
    loopier::cv::setDetectionArea(rect);
}

//---------------------------------------------------------
void loopier::MessageMapper::selectBlob(const Message & msg)
{
    loopier::cv::selectBlob();
}

//---------------------------------------------------------
void loopier::MessageMapper::deselectBlob(const Message & msg)
{
    loopier::cv::deselectBlob();
}

//---------------------------------------------------------
void loopier::MessageMapper::firstBlob(const Message & msg)
{
    loopier::cv::firstBlob();
}

//---------------------------------------------------------
void loopier::MessageMapper::nextBlob(const Message & msg)
{
    loopier::cv::nextBlob();
}

//---------------------------------------------------------
void loopier::MessageMapper::previousBlob(const Message & msg)
{
    loopier::cv::previousBlob();
}

//---------------------------------------------------------
void loopier::MessageMapper::lastBlob(const Message & msg)
{
    loopier::cv::lastBlob();
}






//---------------------------------------------------------

//        CONSOLE

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::setConsoleColor(const Message & msg)
{
    loopier::ConsoleUI::setColor(loopier::MessageMapper::getColorFromMessage(msg));
}

//---------------------------------------------------------
void loopier::MessageMapper::setConsoleAlpha(const Message & msg)
{
    loopier::ConsoleUI::setAlpha(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setConsolePrompt(const Message & msg)
{
    loopier::ConsoleUI::setPrompt(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::printToConsole(const Message & msg)
{
    loopier::ConsoleUI::print(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setConsoleLinesNum(const Message & msg)
{
    loopier::ConsoleUI::setMaxLines(msg.getArgAsInt(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::toggleConsole(const Message & msg)
{
    loopier::ConsoleUI::toggle();
}

//---------------------------------------------------------
void loopier::MessageMapper::showConsole(const Message & msg)
{
    loopier::ConsoleUI::show();
}

//---------------------------------------------------------
void loopier::MessageMapper::hideConsole(const Message & msg)
{
    loopier::ConsoleUI::hide();
}

//---------------------------------------------------------
void loopier::MessageMapper::moveConsole(const Message & msg)
{
    loopier::ConsoleUI::setPosition(msg.getArgAsFloat(0), msg.getArgAsFloat(1));
}

//---------------------------------------------------------
void loopier::MessageMapper::setConsoleFont(const Message & msg)
{
    loopier::ConsoleUI::setFont(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setConsoleFontSize(const Message & msg)
{
    loopier::ConsoleUI::setFontSize(msg.getArgAsInt(0));
}







//---------------------------------------------------------

//        UVC

//---------------------------------------------------------


//---------------------------------------------------------
void loopier::MessageMapper::addUvcCamera(const Message & msg)
{
    int     vendorId        = msg.getArgAsInt(0);
    int     productId       = msg.getArgAsInt(1);
    int     interfaceNum    = msg.getArgAsInt(2);
    string  name            = msg.getArgAsString(3);
    loopier::uvc::addCamera(vendorId, productId, interfaceNum, name);
}


//---------------------------------------------------------
void loopier::MessageMapper::useUvcCamera(const Message & msg)
{
    loopier::uvc::useCamera(msg.getArgAsString(0)); // camera name
}


//---------------------------------------------------------
void loopier::MessageMapper::setUvcAutoExposure(const Message & msg)
{
    loopier::uvc::setAutoExposure(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcExposure(const Message & msg)
{
    loopier::uvc::setExposure(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcAutoFocus(const Message & msg)
{
    loopier::uvc::setAutoFocus(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcFocus(const Message & msg)
{
    loopier::uvc::setFocus(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcAutoWhiteBalance(const Message & msg)
{
    loopier::uvc::setAutoWhiteBalance(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcWhiteBalance(const Message & msg)
{
    loopier::uvc::setWhiteBalance(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcGain(const Message & msg)
{
    loopier::uvc::setGain(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcBrightness(const Message & msg)
{
    loopier::uvc::setBrightness(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcContrast(const Message & msg)
{
    loopier::uvc::setContrast(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcSaturation(const Message & msg)
{
    loopier::uvc::setSaturation(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setUvcSharpness(const Message & msg)
{
    loopier::uvc::setSharpness(msg.getArgAsFloat(0));
}






//---------------------------------------------------------

//        CONSOLE

//---------------------------------------------------------


//---------------------------------------------------------
ofColor loopier::MessageMapper::getColorFromMessage(const Message & msg)
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
