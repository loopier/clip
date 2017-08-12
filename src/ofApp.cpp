#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(255, 255, 255);
    ofSetVerticalSync(true);
    
    movie.load("movies/stress.mov");
    movie.setLoopState(OF_LOOP_NORMAL);
    movie.play();
    
//    osc.listenToPort(54321);
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &ofApp::processOscMessage);
    
//    clip.setup("movies/stress.mov");
//    clip.setPosition(ofGetWidth()/2, ofGetHeight()/2);
//    clip.setScale(1.5);
    loopier::newClip("movies/stress.mov", "democlip");
}

//--------------------------------------------------------------
void ofApp::update(){
//    movie.update();
//    clip.update();
    loopier::updateClips();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    movie.draw(0,0);
//    clip.draw();
    loopier::drawClips();
}

void ofApp::processOscMessage(ofxOscMessage & msg)
{
    loopier::printOscMessage(msg, "ofApp: processing OSC message:");
    
    // messages have the format /loopier/clip "name" "command" [arg1, ... , argN]
    if (msg.getAddress() == "/loopier/clip") {
        
        string name = msg.getArgAsString(0);
        string command = msg.getArgAsString(1);
        
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
    loopier::moveClipTo("democlip", x, y);
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
