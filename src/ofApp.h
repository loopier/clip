#pragma once

#include "ofMain.h"
#include "OscManager.h"
#include "Clip.h"
#include "ConsoleUI.h"
#include "Movie.h"
#include "VideoInput.h"

using namespace loopier;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

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

private:
    ConsoleUI   console;
    OscManager  osc;
    string  applicationSupportPath; ///< Path to the directory with resources and config files

    /// \brief  Creates a folder in ~/Library/Application Support/Clip/
    ///     for all the resources and config files.
    void init();

    /// \brief  Maps OSC messages to behavieours (commands).
    /// \description    This is what allows the application to be controlled via OSC. If
    ///     you need to add more controls, this is where you should add them.
    ///     It maps OSC messages to function calls or groups of function calls
    void processOscMessage(ofxOscMessage & msg);
    /// \brief  Prints a message to the console if there's a typo
    void printOscMessageMisstypingWarning();
};
