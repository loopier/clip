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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_BACKSPACE) {
        loopier::resetClip("democlip");
    }
    if (key == '+') {
        loopier::scaleUpClip("democlip");
    }
    if (key == '-') {
        loopier::scaleDownClip("democlip", 0.2);
    }
    if (key == '2') {
        loopier::scaleClip("democlip", 2.0);
    }
    if (key == '0') {
        loopier::resetClipScale("democlip");
    }
    if (key == 'f') {
        loopier::toggleFullscreenClip("democlip");
    }
    
    // PLAY
    
    if (key == 'p') {
        loopier::playClip("democlip");
    }
    if (key == 's') {
        loopier::stopClip("democlip");
    }
    if (key == 'P') {
        loopier::pauseClip("democlip");
    }
    if (key == 'l') {
        loopier::toggleClipLoopState("democlip");
    }
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
