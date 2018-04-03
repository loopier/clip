//
//  Recorder.cpp
//  clip
//
//  Created by roger on 03/04/2018.
//
//

#include "Recorder.h"
//--------------------------------------------------------------
loopier::recorder::Recorder::Recorder()
: fileName("testMovie")
, fileExt(".mov")
{
    
}

//--------------------------------------------------------------
loopier::recorder::Recorder::~Recorder()
{
    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &loopier::recorder::Recorder::recordingComplete);
    ofRemoveListener(ofEvents().update, this, &Recorder::update);
    ofRemoveListener(ofEvents().draw, this, &Recorder::draw);
    vidRecorder.close();
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::setup(shared_ptr<ofFbo> fbo)
{
    
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("800k");
    vidRecorder.setPixelFormat("rgba");
    
    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &loopier::recorder::Recorder::recordingComplete);
    ofAddListener(ofEvents().update, this, &Recorder::update);
    ofAddListener(ofEvents().draw, this, &Recorder::draw);
    
    recordFbo.allocate(fbo->getWidth(), fbo->getHeight(), GL_RGBA);
    inputFbo = fbo;
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::update()
{
    if (bRecording) {
        recordFbo.begin();
        ofEnableAlphaBlending();
        inputFbo->draw(0, 0);
        ofDisableAlphaBlending();
        recordFbo.end();
        
        inputFbo->readToPixels(recordPixels);
        bool success = vidRecorder.addFrame(recordPixels);
        if (!success) {
            ofLogWarning() << "This frame was not added!";
        }
    }
    
    if (vidRecorder.hasVideoError()) {
        ofLogWarning() << "The video recorder failed to write some frames!";
    }
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::draw()
{
    if (!bRecording) return;
    ofPushStyle();
    ofSetColor(255,0,0);
    ofFill();
    ofDrawCircle(ofGetWidth() - 50, 20, 10);
    ofDrawBitmapString("REC", ofGetWidth() -35, 25);
    ofPopStyle();
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::update(ofEventArgs& e)
{
    update();
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::draw(ofEventArgs& e)
{
    draw();
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs &args)
{
    cout << "The recorded video file is now complete" << endl;
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::start()
{
    bRecording = true;
    cout << "Started recording to '" << fileName << fileExt << "'" << endl;
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::stop()
{
    bRecording = false;
    vidRecorder.close();
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::toggle()
{
    bRecording = !bRecording;
    if (bRecording && !vidRecorder.isInitialized()) {
        vidRecorder.setup(fileName+fileExt, recordFbo.getWidth(), recordFbo.getHeight(), 30);
        vidRecorder.start();
        ofLog() << "Started recording to '" << fileName << fileExt << "'" << endl;
    } else if (!bRecording && vidRecorder.isInitialized()) {
        vidRecorder.setPaused(true);
        ofLog() << "Started recording '" << fileName << fileExt << "'" << endl;
    } else if (bRecording && vidRecorder.isInitialized()) {
        vidRecorder.setPaused(false);
        ofLog() << "Resumed recording to '" << fileName << fileExt << "'" << endl;
    }
}

//--------------------------------------------------------------
//  PUBLIC INTERFACE
//--------------------------------------------------------------
namespace {
    loopier::recorder::Recorder rec;
}

//--------------------------------------------------------------
void loopier::recorder::setup(shared_ptr<ofFbo> fbo)
{
    rec.setup(fbo);
}

//--------------------------------------------------------------
void loopier::recorder::update()
{
    rec.update();
}

//--------------------------------------------------------------
void loopier::recorder::draw()
{
    rec.draw();
}

//--------------------------------------------------------------
void loopier::recorder::start()
{
    rec.start();
}

//--------------------------------------------------------------
void loopier::recorder::stop()
{
    rec.stop();
}

//--------------------------------------------------------------
void loopier::recorder::toggle()
{
    rec.toggle();
}