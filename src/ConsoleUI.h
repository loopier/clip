//
//  ConsoleUI.h
//  clip
//
//  Created by roger on 12/08/2017.
//
//  This class is used to print messages to the screen.

#ifndef ConsoleUI_h
#define ConsoleUI_h

#include "ofMain.h"

namespace loopier {
    class ConsoleUI
    {
    private:
        static string           prompt;
        static vector<string>   msg;
        static int              maxLines;
        static float    x, y;
        static float    lineseparation;
        static ofColor  color;
        static bool     bHide;
        
    public:
        static void draw();
        static void print(const string & s);
        static void setPrompt(const string & p);
        static void setColor(const ofColor & c);
        static void setMaxLines(const int max);
        static void toggle();
        static void show();
        static void hide();
    };
}

#endif /* ConsoleUI_h */
