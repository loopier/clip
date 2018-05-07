#include "ofApp.h"

void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    //    ofSetLogLevel(OF_LOG_NOTICE);
    
    ofSetWindowPosition(ofGetScreenWidth(), 0);
//    ofSetWindowPosition(0, 0);
    ofSetFrameRate(30);
//    ofSetFullscreen(true);
    ofBackground(0,0,0);
    ofSetVerticalSync(true);
    
//    loopier::resource::setPath(applicationSupportPath + "resources/");
    loopier::app::init();
    loopier::uvc::init();
    
    msgMapper.setup();
    
    loopier::command::loadCommands("commands-example");
}

//--------------------------------------------------------------
void ofApp::update(){
    loopier::app::update();
    loopier::uvc::update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    loopier::app::draw();
}

void ofApp::exit()
{
    
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
    loopier::app::mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    loopier::app::mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    loopier::app::mouseReleased(x,y,button);
    
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


