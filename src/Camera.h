//
//  Camera.h
//  clip
//
//  Created by roger on 26/09/2017.
//  Copyright 2017 Loopier. All rights reserved.
//
//  Manages 

#ifndef _Camera
#define _Camera


#include "ofMain.h"

class Camera{
	
public:
    
    void setup();
    void update();
    void draw();
    void exit();
	void keyPressed  (int key);
	void keyReleased  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
    
private:
    ofVideoGrabber cam;
};

#endif