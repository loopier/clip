//
//  Recorder.h
//  clip
//
//  Created by roger on 03/04/2018.
//
//

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
            
            void setup(shared_ptr<ofFbo> fbo);
            void update();
            void draw();
            void update(ofEventArgs& e); // automatic update
            void draw(ofEventArgs& e);  // automatic draw
            
            ofxVideoRecorder vidRecorder;
            bool    bRecording;
            string  fileName;
            string  fileExt;
            
            void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
            
            void start();
            void stop();
            void toggle();
            
            shared_ptr<ofFbo>   recordFbo;
            ofPixels            recordPixels;
        };
        
        void setup(shared_ptr<ofFbo> fbo);
        void update();
        void draw();
        void start();
        void stop();
        void toggle();
    } // namespace recorder
} // namespace loopier

#endif /* Recorder_hpp */
