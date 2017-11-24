#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);

    /// -------------------------------------------------------------------------------
    /// --------------  TESTING     --------------
    /// -------------------------------------------------------------------------------

//    framePlayer.setPath("/Users/roger/Library/Application Support/Clip/resources/frames/");
//    framePlayer.load("manwalk");
//    
//    ofLogVerbose() << "Total frames: " << framePlayer.getTotalNumFrames();
//
//    ofExit();
//    ofLogVerbose() << "!!! REMOVE RETURN FROM ofApp::setup()!!!";
//    return;
    /// -------------------------------------------------------------------------------
    /// --------------  END OF TEST --------------
    /// -------------------------------------------------------------------------------

//    ofSetWindowPosition(ofGetScreenWidth(), 0);
//    ofSetFullscreen(true);
    ofBackground(0,0,0);
    ofSetVerticalSync(true);

    loopier::ConsoleUI::setup();

    applicationSupportPath = ofFilePath::getUserHomeDir() + "/Library/Application Support/Clip/";
    init();

//    osc.listenToPort(54321);
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &ofApp::processOscMessage);

    loopier::Movie::preloadMovies();
    string moviespath = applicationSupportPath + "resources/movies/";
//    loopier::newClip("exampleclip");
    
    loopier::newVideoInput();
}

//--------------------------------------------------------------
void ofApp::update(){
    loopier::updateClips();
    loopier::updateVideoInput();
}

//--------------------------------------------------------------
void ofApp::draw(){
    loopier::drawVideoInput();
    loopier::drawClips();
    console.draw();
    
    framePlayer.draw();
}

void ofApp::exit()
{
//    ofLogVerbose() << "!!! REMOVE return FROM ofApp::setup()!!!";
}

void ofApp::processOscMessage(ofxOscMessage & msg)
{
    loopier::printOscMessage(msg, "OSC:");
    console.print(loopier::getSimplifiedOscMessage(msg));

    // console commands
    if (msg.getAddress() == "/loopier/clip/console") {
        string command = msg.getArgAsString(0);

        if (command == "color") {
            ofColor c;
            if (msg.getNumArgs() == 2)      c = ofColor(msg.getArgAsFloat(1) * 255);
            else if (msg.getNumArgs() == 3) c = ofColor(msg.getArgAsFloat(1) * 255, msg.getArgAsFloat(2) * 255);
            else if (msg.getNumArgs() == 4) c = ofColor(msg.getArgAsFloat(1) * 255, msg.getArgAsFloat(2) * 255,
                                                    msg.getArgAsFloat(3) * 255);
            // RGBA doesn't work (?)
//            if (msg.getNumArgs() == 5)  c = ofColor(msg.getArgAsFloat(1) * 255, msg.getArgAsFloat(2) * 255,
//                                                    msg.getArgAsFloat(3) * 255, msg.getArgAsFloat(4)) * 255;
            else { printOscMessageMisstypingWarning(); return; }

            loopier::ConsoleUI::setColor(c);
        }
        else if (command == "alpha")    loopier::ConsoleUI::setAlpha(msg.getArgAsFloat(1));

        else if (command == "prompt")   loopier::ConsoleUI::setPrompt(msg.getArgAsString(1));
        else if (command == "print")    loopier::ConsoleUI::print(msg.getArgAsString(1));
        else if (command == "lines")    loopier::ConsoleUI::setMaxLines(msg.getArgAsInt(1));
        else if (command == "toggle")   loopier::ConsoleUI::toggle();
        else if (command == "show")     loopier::ConsoleUI::show();
        else if (command == "hide")     loopier::ConsoleUI::hide();
        else if (command == "moveto")   loopier::ConsoleUI::setPosition(msg.getArgAsFloat(1), msg.getArgAsFloat(2));
        else if (command == "font")     loopier::ConsoleUI::setFont(msg.getArgAsString(1));
        else if (command == "fontsize") loopier::ConsoleUI::setFontSize(msg.getArgAsInt(1));

        else { printOscMessageMisstypingWarning(); return; }
    }

    // commands affecting all clips
    else if (msg.getAddress() == "/loopier/clip/clips") {
        string command = msg.getArgAsString(0);

        if      (command == "clearall")  loopier::clearClips();
        else if (command == "listnames") loopier::listClipNames();

        else if (command == "togglenames")  loopier::toggleClipNames();
        else if (command == "shownames")    loopier::showClipNames();
        else if (command == "hidenames")    loopier::hideClipNames();

        else { printOscMessageMisstypingWarning(); return; }
    }

    // messages have the format /loopier/clip "name" "command" [arg1, ... , argN]
    else if (msg.getAddress() == "/loopier/clip/clip") {

        string  name = msg.getArgAsString(0);
        string  command = msg.getArgAsString(1);
        int     numargs = msg.getNumArgs();

        if      (command == "new" && msg.getNumArgs() <= 2) loopier::newClip(name);
        else if (command == "new" && msg.getNumArgs() >= 3) loopier::newClip(name, msg.getArgAsString(2));
        else if (command == "remove")                       loopier::removeClip(name);

        else if (command == "reset")            loopier::resetClip(name);
        else if (command == "scaleup")          loopier::scaleUpClip(name, msg.getArgAsFloat(2));
        else if (command == "scaledown")        loopier::scaleDownClip(name, msg.getArgAsFloat(2));
        else if (command == "scale")            loopier::scaleClip(name, msg.getArgAsFloat(2));
        else if (command == "xscale")           loopier::setClipWidth(name, msg.getArgAsFloat(2));
        else if (command == "yscale")           loopier::setClipHeight(name, msg.getArgAsFloat(2));
        else if (command == "resetscale")       loopier::resetClipScale(name);
        else if (command == "vflip")            loopier::setClipVFlip(name);
        else if (command == "hflip")            loopier::setClipHFlip(name);
        else if (command == "fullscreen")       loopier::toggleFullscreenClip(name);
        else if (command == "togglevisibility") loopier::toggleClipVisibility(name);
        else if (command == "show")             loopier::showClip(name);
        else if (command == "hide")             loopier::hideClip(name);

        // PLAY

        else if (command == "play")             loopier::playClip(name);
        else if (command == "stop")             loopier::stopClip(name);
        else if (command == "pause")            loopier::pauseClip(name);
        else if (command == "loop") {
            string state = msg.getArgAsString(2);
            if      (state == "none")        loopier::setClipLoopState(name, OF_LOOP_NONE);
            else if (state == "normal")      loopier::setClipLoopState(name, OF_LOOP_NORMAL);
            else if (state == "palindrome")  loopier::setClipLoopState(name, OF_LOOP_PALINDROME);
            else { printOscMessageMisstypingWarning(); return; }
        }
        else if (command == "speed")            loopier::setClipSpeed(name, msg.getArgAsFloat(2));

        // attributes

        else if (command == "moveto")   loopier::moveClipTo(name, msg.getArgAsFloat(2), msg.getArgAsFloat(3));
        else if (command == "color")    loopier::setClipColor(name, msg.getArgAsString(2));
        else if (command == "alpha")    loopier::setClipAlpha(name, msg.getArgAsFloat(2));

        // managing movies

        else if (command == "listmovies")   loopier::listClipMovies(name);
        else if (command == "addmovie")     loopier::addMovieToClip(name, msg.getArgAsString(2));
        else if (command == "setmovie")     loopier::setClipMovie(name, msg.getArgAsInt(2));
        else if (command == "playsequence") loopier::playClipMovieSequence(name);
        else if (command == "sequence")     loopier::setClipMovieSequenceOrder(name, msg.getArgAsString(2));

        else { printOscMessageMisstypingWarning(); return; }
    }
    
    // messages have the format /loopier/clip/videoinput "command" [arg1, ... , argN]
    else if (msg.getAddress() == "/loopier/clip/videoinput") {
        string command = msg.getArgAsString(0);
        int numArgs = msg.getNumArgs();
        
        if (command == "threshold") loopier::setVideoInputThreshold(msg.getArgAsFloat(1));
        else if (command == "minArea") loopier::setVideoInputMinArea(msg.getArgAsFloat(1));
        else if (command == "maxArea") loopier::setVideoInputMaxArea(msg.getArgAsFloat(1));
        else if (command == "holes") loopier::setVideoInputHoles(msg.getArgAsBool(1));
        else if (command == "togglevisibility") loopier::toggleVideoInputVisibility();
        else if (command == "show") loopier::showVideoInput();
        else if (command == "hide") loopier::hideVideoInput();
        
        else { printOscMessageMisstypingWarning(); return; }
    }

    // application commands
    else if (msg.getAddress() == "/loopier/clip") {

        string command = msg.getArgAsString(0);

        if      (command == "fullscreen")   ofToggleFullscreen();
        else if (command == "move") {
            ofSetFullscreen(false);
            float x = msg.getArgAsFloat(1) * ofGetScreenWidth();
            float y = msg.getArgAsFloat(2) * ofGetScreenHeight();
            ofSetWindowPosition(x, y);
        }
        else if (command == "quit")         ofExit();

        else { printOscMessageMisstypingWarning(); return; }
    }

    else { printOscMessageMisstypingWarning(); return; }
}

void ofApp::printOscMessageMisstypingWarning()
{
    ofLogWarning() << "OSC message not found.  Double-check your message.";
    console.print("WARNING!:\t Check your message, there seems to be a typo and it wasn't processed.");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    float fx = float(x)/float(ofGetWidth());
//    float fy = float(y)/float(ofGetHeight());
//    clips["default"]->setPosition(fx, fy);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::init()
{
    // check if ~/Library/Application Support/Clip exists
    ofDirectory dir(applicationSupportPath);
    ofLogVerbose()  <<  __FUNCTION__
                    << ":\tLooking for " << dir.getAbsolutePath();
    if (dir.exists()) {
        ofLogVerbose() <<  __FUNCTION__ <<  ":\tDirectory found.";
    } else {
        string msg = "ERROR!!!\n\n";
        msg += dir.getAbsolutePath() + " doesn't exist.\n\n";
        msg += "Please create it and put the resources and config files in there.\n\n";
        msg += "You can find default directory structure and files in the README file.\n\n";
        msg += "Quitting application.";

        ofLogError()  << msg;
        loopier::ConsoleUI::printError(msg);
        ofSystemAlertDialog(msg);
        ofExit();
    }

    // create folder if it doesn't exist
    // load config/settings
}
