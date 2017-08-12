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
}

void ofApp::processOscMessage(ofxOscMessage & msg)
{
    loopier::printOscMessage(msg, "OSC:");
    
    // messages have the format /loopier/clip "name" "command" [arg1, ... , argN]
    if (msg.getAddress() == "/loopier/clip") {
        
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
        if (command == "changeloopstate")  loopier::toggleClipLoopState(name);
        
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
        ofLogError()  << dir.getAbsolutePath() << " doesn't exist.\n"
                        << "\tPlease create it and put the resources and config files in there.\n"
                        << "\tYou can find default directory structure and files in the !!! TODO !!!.";
        ofLogNotice() << __FUNCTION__ << ":\tQuit application.";
        ofExit();
    }
    
    // create folder if it doesn't exist
    // load config/settings
}
