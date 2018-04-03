//
//  Recorder.h
//  clip
//
//  Created by roger on 03/04/2018.
//
//  Records any output to a movie file

#ifndef Recorder_h
#define Recorder_h

#include "ofMain.h"
#include "ofxVideoRecorder.h"

namespace loopier {
    namespace recorder {
        class Recorder {
        public:
            Recorder();
            virtual ~Recorder();
            
            /// \brief
            /// \param  fbo shared_ptr<ofFbo>   FBO to record from
            void setup(shared_ptr<ofFbo> fbo);
            void update();
            void draw();
            void update(ofEventArgs& e); // automatic update
            void draw(ofEventArgs& e);  // automatic draw
            
            ofxVideoRecorder vidRecorder;
            bool    bRecording;
            string  path;
            string  fileName;
            string  fileExt;
            
            void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
            
            void start();
            void stop();
            void toggle();
            void setInputFbo(shared_ptr<ofFbo> fbo);
            void setVideoCodec(const string codec);
            void setVideoBitrate(const string bitrate);
            void setPath(const string newPath);
            void setFileName(const string name);
            void setFileExtension(const string ext);
            
            shared_ptr<ofFbo>   recordFbo;
            ofPixels            recordPixels;
        };
        
        void setup(shared_ptr<ofFbo> fbo);
        void update();
        void draw();
        void start();
        void stop();
        void toggle();
        void setInputFbo(shared_ptr<ofFbo> fbo);
        void setVideoCodec(const string codec);
        void setVideoBitrate(const string bitrate);
        void setPath(const string path);
        void setFileName(const string name);
        void setFileExtension(const string ext);
    } // namespace recorder
} // namespace loopier

#endif /* Recorder_hpp */
