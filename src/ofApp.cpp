#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0,0,0);
    ofSetVerticalSync(true);
    
    applicationSupportPath = ofFilePath::getUserHomeDir() + "/Library/Application Support/Clip/";
    init();
    
//    osc.listenToPort(54321);
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &ofApp::processOscMessage);
    
    string moviespath = applicationSupportPath + "resources/movies/";
    loopier::newClip("default.mov", moviespath);
}

//--------------------------------------------------------------
void ofApp::update(){
    loopier::updateClips();
}

//--------------------------------------------------------------
void ofApp::draw(){
    loopier::drawClips();
    console.draw();
}

void ofApp::processOscMessage(ofxOscMessage & msg)
{
    loopier::printOscMessage(msg, "OSC:");
    console.print(loopier::getPrintableOscMessage(msg));
    
    // console commands
    if (msg.getAddress() == "/loopier/clip/console") {
        string command = msg.getArgAsString(0);
        
        if (command == "color") {
            ofColor c;
            if (msg.getNumArgs() == 2)  c = ofColor(msg.getArgAsFloat(1) * 255);
            if (msg.getNumArgs() == 3)  c = ofColor(msg.getArgAsFloat(1) * 255, msg.getArgAsFloat(2) * 255);
            if (msg.getNumArgs() == 4)  c = ofColor(msg.getArgAsFloat(1) * 255, msg.getArgAsFloat(2) * 255,
                                                    msg.getArgAsFloat(3) * 255);
            // RGBA doesn't work (?)
//            if (msg.getNumArgs() == 5)  c = ofColor(msg.getArgAsFloat(1) * 255, msg.getArgAsFloat(2) * 255,
//                                                    msg.getArgAsFloat(3) * 255, msg.getArgAsFloat(4)) * 255;
            loopier::ConsoleUI::setColor(c);
        }
        
        if (command == "prompt")    loopier::ConsoleUI::setPrompt(msg.getArgAsString(1));
        if (command == "print")     loopier::ConsoleUI::print(msg.getArgAsString(1));
        if (command == "lines")     loopier::ConsoleUI::setMaxLines(msg.getArgAsInt(1));
    }
    
    // commands affecting all clips
    if (msg.getAddress() == "/loopier/clip/clips") {
        string command = msg.getArgAsString(0);
        
        if (command == "clearall")  loopier::clearClips();
        if (command == "listnames") loopier::listClipNames();
        
        if (command == "togglenames")   loopier::toggleClipNames();
        if (command == "shownames")     loopier::showClipNames();
        if (command == "hidenames")     loopier::hideClipNames();
    }
    
    // messages have the format /loopier/clip "name" "command" [arg1, ... , argN]
    if (msg.getAddress() == "/loopier/clip/clip") {
        
        string name = msg.getArgAsString(0);
        string command = msg.getArgAsString(1);
        
        if (command == "new")               loopier::newClip(name);
        
        if (command == "reset")             loopier::resetClip(name);
        if (command == "scaleup")           loopier::scaleUpClip(name, msg.getArgAsFloat(2));
        if (command == "scaledown")         loopier::scaleDownClip(name, msg.getArgAsFloat(2));
        if (command == "scale")             loopier::scaleClip(name, msg.getArgAsFloat(2));
        if (command == "resetscale")        loopier::resetClipScale(name);
        if (command == "togglefullscreen")  loopier::toggleFullscreenClip(name);
        
        // PLAY
        
        if (command == "play")             loopier::playClip(name);
        if (command == "stop")             loopier::stopClip(name);
        if (command == "pause")            loopier::pauseClip(name);
        if (command == "loop") {
            string state = msg.getArgAsString(2);
            if (state == "none")        loopier::setClipLoopState(name, OF_LOOP_NONE);
            if (state == "normal")      loopier::setClipLoopState(name, OF_LOOP_NORMAL);
            if (state == "palindrome")  loopier::setClipLoopState(name, OF_LOOP_PALINDROME);
        }
        
        // ATTRIBUTES
        
        if (command == "moveto")    loopier::moveClipTo(name, msg.getArgAsFloat(2), msg.getArgAsFloat(3));
        if (command == "alpha")     loopier::setClipAlpha(name, msg.getArgAsFloat(2));
    }
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
    float fx = float(x)/float(ofGetWidth());
    float fy = float(y)/float(ofGetHeight());
    clips["default"]->setPosition(fx, fy);
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
        ofSystemAlertDialog(msg);
        ofExit();
    }
    
    // create folder if it doesn't exist
    // load config/settings
}
