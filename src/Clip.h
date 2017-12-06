//
//  Clip.h
//  clip
//
//  Created by roger on 26/11/2017.
//  Copyright 2017 __MyCompanyName__. All rights reserved.
//

#ifndef _Clip
#define _Clip


#include "ofMain.h"
#include "Types.h"
#include "FramePlayer.h"
#include "MoviePlayer.h"
#include "CameraPlayer.h"
#include "CvPlayer.h"

namespace loopier {
    
    class Clip{
        
    public:
        
        //        Clip(); -- DISABLED (Private)
        Clip (string & clipname, string & resourcename);
        virtual ~Clip();
        
        void setup(PlayerPtr aplayer);
        void update();
        void draw();
        void exit();
        void update(ofEventArgs& e); // automatic update
        void draw(ofEventArgs& e);  // automatic draw
        
        /// \brief  Resets clip to the default state
        void reset();
        
        void setName(const string& newName);
        string getName() const;
        
        void play();
        void stop();
        void pause(bool bPause=true);
        void setLoopState(const LoopType state);
        void setSpeed(const float newSpeed);
        
        void setScale(const float newScale);
        void setScaleX(const float newScale);
        void setScaleY(const float newScale);
        float getScale() const;
        
        void setPosition(const float newX, const float newY);
        void setPosition(const ofPoint& newPos);
        ofPoint getPosition() const;
        
        void toggleFullscreen();
        void toggleVisibility();
        void show();
        void hide();
        
        void setColor(const ofColor& newColor);
        void setAlpha(const float newAlpha);
        
        void setMask(PlayerPtr aPlayer);
        void maskOn();
        void maskOff();
        
        void toggleName();
        void showName();
        void hideName();
        
        //------------------------------------------------------------------------------------------
        //  Transforms
        void flipV();
        void flipH();
        
        void        setPlayer(PlayerPtr aPlayer);
        PlayerPtr   getPlayer() const;
        
        ofTexture & getTexture() const;
        ofPixels &   getPixels();
        ofImage &   getImage() const;
        
        // \brief   Sets the drawing order -- 0 = at the top.  Big numbers are drawn at the bottom
        void        setDepth(int order);
        int         getDepth() const;
        
    private:
        PlayerPtr   player;     // TODO: Should be a vector of players
        PlayerPtr   maskPlayer; // a player used as a mask
        ofFbo       outputFbo; // final image to be drawn
        ofPixels    outputPixels;
        bool        bMask;  // turn mask on and off
        
        string  name;
        float   x, y;
        float   width, height;
        float   scale, scaleX, scaleY;
        float   anchorPercentX, anchorPercentY;
        ofColor color; ///< Tint
        float   alpha; ///< Transparency of the clip
        
        int     depth; // used in drawing order. 0 at top, bigger numbers are at the bottom
        
        bool    bFullscreen;
        bool    bDrawName;
        bool    bVisible;
        
        // transforms
        bool    bFlipV; ///< Flip vertically
        bool    bFlipH; ///< Flip horizontally
        
        LoopType    loopState;    ///< See ofSetLoopState(...)
        bool        bPlaySequence; ///< If true, all movies are played in sequence order.
        int         sequenceIndex; ///< Used to keep track of the sequence order.
        vector<int> sequenceOrder; ///< Each element is a movie index.  They'll be played in order.
        
        Clip(); // Disable default constructor.  All clips must have a name
        
        /// \brief
        
    };
    
    typedef shared_ptr<Clip>        ClipPtr;
    typedef vector<ClipPtr>         ClipList;
    typedef map<string, ClipPtr>    ClipMap;    
    
}

#endif