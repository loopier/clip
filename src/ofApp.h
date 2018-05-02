#pragma once

#include "ofMain.h"
#include "MessageMapper.h"
#include "ClipController.h"
#include "Clip.h"
#include "ConsoleUI.h"
#include "Types.h"
#include "Uvc.h"

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
    ConsoleUI       console;
    loopier::osc::MessageMapper   msgMapper;
};
