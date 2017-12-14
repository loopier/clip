//
//  SyphonPlayer.cpp
//  clip
//
//  Created by roger on 13/12/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#include "SyphonPlayer.h"


//---------------------------------------------------------
loopier::SyphonPlayer::SyphonPlayer()
{
    client.setup();
    client.set("", "Jitter");
    width = ofGetWidth();
    height = ofGetHeight();
}

//---------------------------------------------------------
loopier::SyphonPlayer::~SyphonPlayer()
{
    
}

//---------------------------------------------------------
void loopier::SyphonPlayer::setup()
{
}

//---------------------------------------------------------
void loopier::SyphonPlayer::update()
{
    
}

//---------------------------------------------------------
void loopier::SyphonPlayer::draw()
{
    client.draw(0,0, width, height);
}

//---------------------------------------------------------
void loopier::SyphonPlayer::exit(){
    
}

//---------------------------------------------------------
ofTexture & loopier::SyphonPlayer::getTexture()
{
    return client.getTexture();
}

//---------------------------------------------------------
ofPixels & loopier::SyphonPlayer::getPixels()
{
//    return client.getPixels();
}

//---------------------------------------------------------
ofImage & loopier::SyphonPlayer::getImage()
{
    
}
