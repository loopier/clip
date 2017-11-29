#include "ofApp.h"

void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    //    ofSetLogLevel(OF_LOG_NOTICE);
    
//    ofExit();
    
//    ofSetWindowPosition(ofGetScreenWidth(), 0);
//    ofSetFullscreen(true);
    ofBackground(0,0,0);
    ofSetVerticalSync(true);

    loopier::ConsoleUI::setup();

    applicationSupportPath = ofFilePath::getUserHomeDir() + "/Library/Application Support/Clip/";
    init();
    
    loopier::initResources(applicationSupportPath + "resources/");

    msgMapper.setup();
    
//    loopier::newVideoInput();
}

//--------------------------------------------------------------
void ofApp::update(){
    loopier::updateClips();
//    loopier::updateVideoInput();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    loopier::drawVideoInput();
    loopier::drawClips();
    console.draw();
}

void ofApp::exit()
{
//    ofLogVerbose() << "!!! REMOVE return FROM ofApp::setup()!!!";
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
