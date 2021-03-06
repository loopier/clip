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

#ifdef TARGET_OSX
#include "SyphonPlayer.h"
#endif

namespace loopier {
    
    class Clip;
    
    typedef shared_ptr<Clip>        ClipPtr;
    typedef vector<ClipPtr>         ClipList;
    typedef map<string, ClipPtr>    ClipMap;
    
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
        void drawOrigin(const ofColor & c = ofColor(255,255,0, 100));  // draws the anchor of the clip
        void drawName(const ofColor & c = ofColor(255,255,0, 100));  //
        
        /// \brief  Resets clip to the default state
        void reset();
        
        void    setName(const string& newName);
        string  getName() const;
        void    setResourceName(const string & newName);
        string  getResourceName() const;
        
        void        play();
        void        stop();
        void        pause(bool bPause=true);
        bool        isPlaying();
        void        setLoopState(const LoopType state);
        LoopType &  getLoopState();
        void        setPlayDirection(const PlayDirection direction);
        PlayDirection & getPlayDirection();
        void        changePlayDirection();
        void        setSpeed(const float newSpeed);
        float       getSpeed();
        
        void setScale(const float newScale);
        void setScaleX(const float newScale);
        void setScaleY(const float newScale);
        float getScale() const;
        float getScaleX() const;
        float getScaleY() const;
        
        void setAnchorPercent(const float anchorX, const float anchorY);
        void setAnchorPercent(const ofPoint & newAnchorPercent);
        void setAnchor(const ofPoint & newAnchor);
        ofPoint & getAnchor();
        
        void    setPosition(const float x, const float y);
        void    setPosition(const ofPoint& newPos);
        /// \brief  Returns the position modified by the anchor
        ofPoint getPosition() const;
        /// \brief  Returns the topleft corner of the clip
        ofPoint getAbsolutePosition() const;
        /// \brief
        ofPoint getOrigin() const;
        /// \brief  Sets the offset in relation to parent's position
        void        setOffset(const ofPoint & point);
        /// \brief  Sets the offset in relation to parent's position
        void        setOffset(const float x, const float y);
        /// \brief  Returns the offset in relation to parent's position
        ofPoint &   getOffset();
        void        setWidth(const float w);
        void        setHeight(const float h);
        /// \brief  Returns the scaled width of the clip
        float       getWidth() const;
        /// \brief  Returns the scaled height of the clip
        float       getHeight() const;
        /// \brief  Returns a rectangle representing the clip's bounding box
        ofRectangle getBoundingBox() const;
        /// \brief  Returns a rectangle representing the origin (anchor) of the clip
        ofRectangle getOriginRectangle() const;
        
        void toggleFullscreen();
        bool isFullscreen();
        void toggleVisibility();
        bool isVisible();
        void show();
        void hide();
        
        void        setColor(const ofColor& newColor);
        ofColor &   getColor();
        void        setAlpha(const float newAlpha);
        float       getAlpha();
        
        void setMask(ClipPtr aPlayer);
        void setMask(PlayerPtr aPlayer);
        void maskOn();
        void maskOff();
        /// \brief  Returns a pointer to the clipping mask
        ClipPtr getMaskClip();
        
        void toggleName();
        void showName();
        void hideName();
        
        void select(bool b = true);
        void deselect();
        bool isSelected();
        
        //------------------------------------------------------------------------------------------
        //  Transforms
        void flipV();
        bool isFlippedV();
        void flipH();
        bool isFlippedH();
        
        void        setPlayer(PlayerPtr aPlayer);
        PlayerPtr   getPlayer() const;
        /// \brief  Returns the position of the player RELATIVE to the anchor of the
        ///         clip containing it
        ofPoint     getPlayerRelativePosition() const;
        
        void        setInputClip(ClipPtr aClip);
        
        ofTexture & getTexture() ;
        ofPixels &   getPixels();
        ofImage &   getImage() const;
        
        // \brief   Sets the drawing order -- 0 = at the top.  Big numbers are drawn at the bottom
        void        setDepth(int order);
        int         getDepth() const;
        
        /// \brief  Adds the given as a child of this clip.
        void    addChild(const ClipPtr clip);
        void    removeChild(const ClipPtr clip);
        void    clearChildren();
        void    updateChildren();
        vector<string> getChildrenNames();
        
    private:
        PlayerPtr   player;     // TODO: Should be a vector of players
        ClipPtr     maskClip;
        PlayerPtr   maskPlayer; // a player used as a mask
        ofFbo       maskFbo;
        ofFbo       outputFbo; // final image to be drawn
        ofPixels    outputPixels;
        bool        bMask;  // turn mask on and off
        
        string  name;
        string  resourceName;
        ofPoint position;
        ofPoint absolutePosition;
        ofPoint offset; // offset to parent position
        float   width, height;
        float   scale, scaleX, scaleY;
        float   anchorPercentX, anchorPercentY;
        ofPoint anchor;
        ofColor color; ///< Tint
        float   alpha; ///< Transparency of the clip
        
        int     depth; // used in drawing order. 0 at top, bigger numbers are at the bottom
        
        bool    bFullscreen;
        bool    bDrawName;
        bool    bSelected;
        bool    bVisible;
        
        // transforms
        bool    bFlipV; ///< Flip vertically
        bool    bFlipH; ///< Flip horizontally
        
        LoopType    loopState;    ///< See ofSetLoopState(...)
        bool        bPlaySequence; ///< If true, all movies are played in sequence order.
        int         sequenceIndex; ///< Used to keep track of the sequence order.
        vector<int> sequenceOrder; ///< Each element is a movie index.  They'll be played in order.
        
        ClipPtr parent;
        vector<ClipPtr> children;
        
        Clip(); // Disable default constructor.  All clips must have a name
        
        /// \brief
        
    };
    
}

#endif