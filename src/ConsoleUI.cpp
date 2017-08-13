//
//  ConsoleUI.cpp
//  clip
//
//  Created by roger on 12/08/2017.
//
//

#include "ConsoleUI.h"

string          loopier::ConsoleUI::prompt = "> ";
vector<string>  loopier::ConsoleUI::msg;
int             loopier::ConsoleUI::maxLines = 50;
float   loopier::ConsoleUI::x = 10;
float   loopier::ConsoleUI::y = 10;
float   loopier::ConsoleUI::lineseparation = loopier::ConsoleUI::y/2;
ofColor loopier::ConsoleUI::color = ofColor(255);
bool    loopier::ConsoleUI::bHide = false;

void loopier::ConsoleUI::draw()
{
    if (bHide) return;
    
    ofSetColor(color);
    for (int i=0; i < msg.size(); i++) {
        ofDrawBitmapString( prompt + msg[i], x, (y + lineseparation) * (i+1) );
    }
}

void loopier::ConsoleUI::print(const string & s)
{
    if (msg.size() > maxLines){
        msg.erase(msg.begin());
    }
    
    msg.push_back(s);
    
}

void loopier::ConsoleUI::setPrompt(const string & p)
{
    prompt = p;
}

void loopier::ConsoleUI::setColor(const ofColor & c)
{
    color = c;
}

void loopier::ConsoleUI::setMaxLines(const int max)
{
    if (max < maxLines) msg.resize(max);
    maxLines = max;
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