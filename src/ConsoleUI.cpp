//
//  ConsoleUI.cpp
//  clip
//
//  Created by roger on 12/08/2017.
//
//

#include "ConsoleUI.h"

string          loopier::ConsoleUI::prompt      = "> ";
string          loopier::ConsoleUI::errorPrompt = "[ERROR]";
vector<string>  loopier::ConsoleUI::msg;
int             loopier::ConsoleUI::maxLines    = 50;
int     loopier::ConsoleUI::x                   = 10;
int     loopier::ConsoleUI::y                   = 10;
float   loopier::ConsoleUI::lineX               = 10;
float   loopier::ConsoleUI::lineY               = 10;
float   loopier::ConsoleUI::lineseparation      = loopier::ConsoleUI::y/2;
ofColor loopier::ConsoleUI::color               = ofColor(255);
ofColor loopier::ConsoleUI::defaultColor        = ofColor(255);
ofColor loopier::ConsoleUI::errorColor          = ofColor(255,0,0);
int     loopier::ConsoleUI::alpha               = 255;
bool    loopier::ConsoleUI::bHide               = false;
ofTrueTypeFont  loopier::ConsoleUI::font;
int     loopier::ConsoleUI::fontSize            = 16;
string  loopier::ConsoleUI::fontName            = "fonts/OCRAStd.otf";

void loopier::ConsoleUI::setup()
{
    font.load(fontName, fontSize);
}

void loopier::ConsoleUI::draw()
{
    if (bHide) return;
    
    ofSetColor(color);
    for (int i=0; i < msg.size(); i++) {
        // 
        if (ofIsStringInString(msg[i], errorPrompt)) ofSetColor(errorColor);
        
        font.drawString( prompt + msg[i], x + lineX, y + (lineY + lineseparation + fontSize) * (i+1) );
        // reset color
        ofSetColor(color);
    }
}

void loopier::ConsoleUI::print(const string & s)
{
    if (msg.size() > maxLines){
        msg.erase(msg.begin());
    }
    
    msg.push_back(s);
    
    if (ofIsStringInString(s, "\n")) {
        vector<string> lines = ofSplitString(s, "\n", true, true);
        for (int i=1; i < lines.size(); i++) {
            msg.push_back("");
        }
    }
}

void loopier::ConsoleUI::printError(const string & s)
{
    string message = errorPrompt + "\t" + s;
    print(message);
}

void loopier::ConsoleUI::setPrompt(const string & p)
{
    prompt = p;
}

void loopier::ConsoleUI::setColor(const ofColor & c)
{
    color = c;
    color.a = alpha;
}

void loopier::ConsoleUI::setAlpha(const float & a)
{
    alpha = a * 255;
    color.a = alpha;
    errorColor.a = alpha;
}

void loopier::ConsoleUI::setMaxLines(const int max)
{
    if (max < maxLines) msg.resize(max);
    maxLines = max-1;
}

void loopier::ConsoleUI::toggle()
{
    bHide = !bHide;
}

void loopier::ConsoleUI::show() {
    bHide = false;
}

void loopier::ConsoleUI::hide() {
    bHide = true;
}

void loopier::ConsoleUI::setPosition(const float & newX, const float & newY)
{
    x = newX * ofGetWidth();
    y = newY * ofGetHeight();
    
    ofLogVerbose() << __PRETTY_FUNCTION__ << "\t" << x << "\t" << y;
}

void loopier::ConsoleUI::setFont(const string & newFontName)
{
    fontName = "fonts/" + newFontName;
    
    if (!font.load(fontName, fontSize)) {
        printError("Font not found: " + fontName);
    }
}

void loopier::ConsoleUI::setFontSize(const int & newSize)
{
    fontSize = newSize;
    font.load(fontName, fontSize);
}
