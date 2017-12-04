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
    setupMap();

    loopier::ConsoleUI::setup();
}

//---------------------------------------------------------
void loopier::MessageMapper::setupMap()
{
    // Application commands
    messageMap["/loopier/clip/app/quit"]        = &loopier::MessageMapper::quit;
    messageMap["/loopier/clip/app/fullscreen"]  = &loopier::MessageMapper::fullscreen;
    messageMap["/loopier/clip/app/move"]        = &loopier::MessageMapper::move;

    // One Clip commands
    messageMap["/loopier/clip/clip/new"]                = &loopier::MessageMapper::newClip;
    messageMap["/loopier/clip/clip/remove"]             = &loopier::MessageMapper::removeClip;
    messageMap["/loopier/clip/clip/reset"]              = &loopier::MessageMapper::resetClip;
    messageMap["/loopier/clip/clip/depth"]              = &loopier::MessageMapper::setClipDrawOrder;
    messageMap["/loopier/clip/clip/scaleup"]            = &loopier::MessageMapper::scaleUpClip;
    messageMap["/loopier/clip/clip/scaledown"]          = &loopier::MessageMapper::scaleDownClip;
    messageMap["/loopier/clip/clip/scale"]              = &loopier::MessageMapper::scaleClip;
    messageMap["/loopier/clip/clip/xscale"]             = &loopier::MessageMapper::setClipWidth;
    messageMap["/loopier/clip/clip/yscale"]             = &loopier::MessageMapper::setClipHeight;
    messageMap["/loopier/clip/clip/resetscale"]         = &loopier::MessageMapper::resetClipScale;
    messageMap["/loopier/clip/clip/vflip"]              = &loopier::MessageMapper::setClipVFlip;
    messageMap["/loopier/clip/clip/hflip"]              = &loopier::MessageMapper::setClipHFlip;
    messageMap["/loopier/clip/clip/fullscreen"]         = &loopier::MessageMapper::toggleFullscreenClip;
    messageMap["/loopier/clip/clip/togglevisibility"]   = &loopier::MessageMapper::toggleClipVisibility;
    messageMap["/loopier/clip/clip/show"]               = &loopier::MessageMapper::showClip;
    messageMap["/loopier/clip/clip/hide"]               = &loopier::MessageMapper::hideClip;
    messageMap["/loopier/clip/clip/setmask"]            = &loopier::MessageMapper::setClipMask;
    messageMap["/loopier/clip/clip/maskon"]             = &loopier::MessageMapper::enableClipMask;
    messageMap["/loopier/clip/clip/maskoff"]            = &loopier::MessageMapper::disableClipMask;
    // play
    messageMap["/loopier/clip/clip/play"]   = &loopier::MessageMapper::playClip;
    messageMap["/loopier/clip/clip/stop"]   = &loopier::MessageMapper::stopClip;
    messageMap["/loopier/clip/clip/pause"]  = &loopier::MessageMapper::pauseClip;
    messageMap["/loopier/clip/clip/loop"]   = &loopier::MessageMapper::setClipLoopState;
    messageMap["/loopier/clip/clip/speed"]  = &loopier::MessageMapper::setClipSpeed;
    // attributes
    messageMap["/loopier/clip/clip/moveto"] = &loopier::MessageMapper::moveClipTo;
    messageMap["/loopier/clip/clip/color"]  = &loopier::MessageMapper::setClipColor;
    messageMap["/loopier/clip/clip/alpha"]  = &loopier::MessageMapper::setClipAlpha;

    // Clip collection commands
    messageMap["/loopier/clip/clips/clearall"]      = &loopier::MessageMapper::clearClips;
    messageMap["/loopier/clip/clips/listnames"]     = &loopier::MessageMapper::listClipNames;
    messageMap["/loopier/clip/clips/listresources"] = &loopier::MessageMapper::listResourceNames;
    messageMap["/loopier/clip/clips/togglenames"]   = &loopier::MessageMapper::toggleClipNames;
    messageMap["/loopier/clip/clips/shownames"]     = &loopier::MessageMapper::showClipNames;
    messageMap["/loopier/clip/clips/hidenames"]     = &loopier::MessageMapper::hideClipNames;

    // CV commands
    messageMap["/loopier/clip/cv/threshold"]        = &loopier::MessageMapper::setCvThreshold;
    messageMap["/loopier/clip/cv/minArea"]          = &loopier::MessageMapper::setCvMinArea;
    messageMap["/loopier/clip/cv/maxArea"]          = &loopier::MessageMapper::setCvMaxArea;
    messageMap["/loopier/clip/cv/holes"]            = &loopier::MessageMapper::setCvHoles;
    messageMap["/loopier/clip/cv/setinput"]         = &loopier::MessageMapper::setCvInputClip;
    // !!!: REMOVE -- temporary
    messageMap["/loopier/clip/cv/deviceid"]         = &loopier::MessageMapper::setCvDeviceId;
    
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
void loopier::MessageMapper::setClipDrawOrder(const Message & msg)
{
    loopier::clip::setClipDrawOrder(msg.getArgAsString(0), msg.getArgAsInt(1));
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

// ATTRIBUTES
//---------------------------------------------------------
void loopier::MessageMapper::moveClipTo(const Message & msg)
{
    loopier::clip::moveClipTo(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
}

//---------------------------------------------------------
void loopier::MessageMapper::setClipColor(const Message & msg)
{
    ofColor color = loopier::MessageMapper::getColorFromMessage(msg);
    loopier::clip::setClipColor(msg.getArgAsString(0), color);
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

//        CV

//---------------------------------------------------------

//---------------------------------------------------------
void loopier::MessageMapper::setCvThreshold(const Message & msg)
{
//    loopier::cv::setThreshold(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvMinArea(const Message & msg)
{
//    loopier::cv::setMinArea(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvMaxArea(const Message & msg)
{
//    loopier::cv::setMaxArea(msg.getArgAsFloat(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvHoles(const Message & msg)
{
//    loopier::cv::setFindHoles(msg.getArgAsBool(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvInputClip(const Message & msg)
{
    loopier::clip::setCvInput(msg.getArgAsString(0));
}

//---------------------------------------------------------
void loopier::MessageMapper::setCvDeviceId(const Message & msg)
{
    loopier::clip::setCvDeviceId(msg.getArgAsInt(0));
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
