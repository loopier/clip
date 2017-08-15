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
        static string           errorPrompt;
        static vector<string>   msg;
        static int              maxLines;
        static int      x, y;
        static float    lineX, lineY;
        static float    lineseparation;
        static ofColor  color;
        static int      alpha;
        static ofColor  defaultColor;
        static ofColor  errorColor;
        static bool     bHide;
        static ofTrueTypeFont   font;
        static int              fontSize;
        static string           fontName;
        
    public:
        static void setup();
        static void draw();
        static void print(const string & s);
        static void printError(const string & s);
        static void setPrompt(const string & p);
        static void setColor(const ofColor & c);
        static void setAlpha(const float & a);
        static void setMaxLines(const int max);
        static void toggle();
        static void show();
        static void hide();
        static void setPosition(const float & newX, const float & newY);
        static void setFont(const string & newFontName);
        static void setFontSize(const int & newSize);
    };
}

#endif /* ConsoleUI_h */
