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
: path("") // will save to bin/data by default
, fileName("testMovie")
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
    
    recordFbo = fbo;
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::update()
{
    if (bRecording) {
        recordFbo->readToPixels(recordPixels);
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
    ofLogWarning() << __PRETTY_FUNCTION__ << " needs implementation.";
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
        vidRecorder.setup(path + fileName + "_" +  ofGetTimestampString("%Y%m%d%H%M%S%i") + fileExt,
                          recordFbo->getWidth(),
                          recordFbo->getHeight(),
                          ofGetFrameRate());
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
void loopier::recorder::Recorder::setInputFbo(shared_ptr<ofFbo> fbo)
{
    recordFbo = fbo;
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::setVideoCodec(const string codec)
{
    vidRecorder.setVideoCodec(codec);
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::setVideoBitrate(const string bitrate)
{
    vidRecorder.setVideoBitrate(bitrate);
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::setPath(const string newPath)
{
    path = newPath;
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::setFileName(const string name)
{
    fileName = name;
}

//--------------------------------------------------------------
void loopier::recorder::Recorder::setFileExtension(const string ext)
{
    fileExt = ext;
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

//--------------------------------------------------------------
void loopier::recorder::setInputFbo(shared_ptr<ofFbo> fbo)
{
    rec.setInputFbo(fbo);
}

//--------------------------------------------------------------
void loopier::recorder::setVideoCodec(const string codec)
{
    rec.setVideoCodec(codec);
}

//--------------------------------------------------------------
void loopier::recorder::setVideoBitrate(const string bitrate)
{
    rec.setVideoBitrate(bitrate);
}

//--------------------------------------------------------------
void loopier::recorder::setPath(const string path)
{
    rec.setPath(path);
}

//--------------------------------------------------------------
void loopier::recorder::setFileName(const string name)
{
    rec.setFileName(name);
}

//--------------------------------------------------------------
void loopier::recorder::setFileExtension(const string ext)
{
    rec.setFileExtension(ext);
}