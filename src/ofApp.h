#pragma once

#include "ofMain.h"
#include "OscManager.h"
#include "Clip.h"

using namespace loopier;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void processOscMessage(ofxOscMessage & msg);
		
    OscManager osc;
    string  applicationSupportPath; ///< Path to the directory with resources and config files
    
private:
    /// \brief Creates a folder in ~/Library/Application Support/Clip/
    ///     for all the resources and config files.
    void init();
};
