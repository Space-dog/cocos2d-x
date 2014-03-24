#include "CCButtonLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace cocosbuilder {;

#define PROPERTY_ZOOMONTOUCHDOWN "zoomOnTouchDown"
#define PROPERTY_LABELANCHORPOINT "labelAnchorPoint"
#define PROPERTY_PREFERREDSIZE "preferredSize"
#define PROPERTY_MAXSIZE "maxSize"
    
#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|Normal"
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|Highlighted"
#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|Disabled"
#define PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED "backgroundSpriteFrame|Selected"
    
#define PROPERTY_BACKGROUNDOPACITY_NORMAL "backgroundOpacity|Normal"
#define PROPERTY_BACKGROUNDOPACITY_HIGHLIGHTED "backgroundOpacity|Highlighted"
#define PROPERTY_BACKGROUNDOPACITY_DISABLED "backgroundOpacity|Disabled"
#define PROPERTY_BACKGROUNDOPACITY_SELECTED "backgroundOpacity|Selected"
    
#define PROPERTY_LABELOPACITY_NORMAL "labelOpacity|Normal"
#define PROPERTY_LABELOPACITY_HIGHLIGHTED "labelOpacity|Highlighted"
#define PROPERTY_LABELOPACITY_DISABLED "labelOpacity|Disabled"
#define PROPERTY_LABELOPACITY_SELECTED "labelOpacity|Selected"
    
#define PROPERTY_TITLE "title"
    
#define PROPERTY_TITLECOLOR_NORMAL "labelColor|Normal"
#define PROPERTY_TITLECOLOR_HIGHLIGHTED "labelColor|Highlighted"
#define PROPERTY_TITLECOLOR_DISABLED "labelColor|Disabled"
#define PROPERTY_TITLECOLOR_SELECTED "labelColor|Selected"
    
#define PROPERTY_BACKGROUNDCOLOR_NORMAL "backgroundColor|Normal"
#define PROPERTY_BACKGROUNDCOLOR_HIGHLIGHTED "backgroundColor|Highlighted"
#define PROPERTY_BACKGROUNDCOLOR_DISABLED "backgroundColor|Disabled"
#define PROPERTY_BACKGROUNDCOLOR_SELECTED "backgroundColor|Selected"
    
#define PROPERTY_HORIZONTALPADDING "horizontalPadding"
#define PROPERTY_VERTICALPADDING "verticalPadding"
    
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
    
#define PROPERTY_FONTCOLOR "fontColor"
#define PROPERTY_OUTLINECOLOR "outlineColor"
#define PROPERTY_OUTLINEWIDTH "outlineWidth"
    
#define PROPERTY_SHADOWBLURRADIUS "shadowBlurRadius"
#define PROPERTY_SHADOWWIDTH "shadowWidth"
#define PROPERTY_SHADOWCOLOR "shadowColor"
    
#define PROPERTY_SHADOWOFFSET "shadowOffset"
    
#define PROPERTY_MARGIN_LEFT "marginLeft"
#define PROPERTY_MARGIN_TOP "marginTop"
#define PROPERTY_MARGIN_RIGHT "marginRight"
#define PROPERTY_MARGIN_BOTTOM "marginBottom"


void ButtonLoader::onStarPropertiesParsing()
{
    _margins=Rect::ZERO;
}
    
void setScale9SpriteMargins(Node * pNode, Control::State state, const Rect &margins)
{
    Scale9Sprite *sprite = ((ControlButton *)pNode)->getBackgroundSpriteForState(state);
    Size size = sprite->getOriginalSize();
    sprite->setCapInsets(Rect(margins.origin.x*size.width,margins.origin.y*size.height,(1.0f-margins.size.width)*size.width,(1.0f-margins.size.height)*size.height));
}

void ButtonLoader::onEndPropertiesParsing()
{
    setScale9SpriteMargins(_currentNode,Control::State::NORMAL,_margins);
    setScale9SpriteMargins(_currentNode,Control::State::HIGH_LIGHTED,_margins);
    setScale9SpriteMargins(_currentNode,Control::State::DISABLED,_margins);
    setScale9SpriteMargins(_currentNode,Control::State::SELECTED,_margins);
    Size preferedSize = ((ControlButton *)_currentNode)->getPreferredSize();
    ((ControlButton *)_currentNode)->setPreferredSize(preferedSize);
}

void ButtonLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ZOOMONTOUCHDOWN) == 0) {
        ((ControlButton *)pNode)->setZoomOnTouchDown(pCheck);
    } else {
        ControlLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

void ButtonLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char * pPropertyName, const char * pString, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLE) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::NORMAL);
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::HIGH_LIGHTED);
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::DISABLED);
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::SELECTED);
    } else {
        ControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, ccbReader);
    }
}

void ButtonLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTNAME) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::NORMAL);
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::HIGH_LIGHTED);
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::DISABLED);
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::SELECTED);
    } else {
        ControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}
    
void ButtonLoader::onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader)
{
    if(strcmp(pPropertyName, PROPERTY_MARGIN_LEFT) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_MARGIN_TOP) == 0) {
        _margins.origin.y = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_MARGIN_RIGHT) == 0) {
        _margins.size.width = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_MARGIN_BOTTOM) == 0) {
        _margins.size.height = pFloat;
    }
    if(strcmp(pPropertyName, PROPERTY_BACKGROUNDOPACITY_NORMAL) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDOPACITY_HIGHLIGHTED) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDOPACITY_DISABLED) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDOPACITY_SELECTED) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_LABELOPACITY_NORMAL) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_LABELOPACITY_HIGHLIGHTED) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_LABELOPACITY_DISABLED) == 0) {
        _margins.origin.x = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_LABELOPACITY_SELECTED) == 0) {
        _margins.origin.x = pFloat;
    } else {
        ControlLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, ccbReader);
    }
}

void ButtonLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTSIZE) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::NORMAL);
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::HIGH_LIGHTED);
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::DISABLED);
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::SELECTED);
    } else if(strcmp(pPropertyName, PROPERTY_HORIZONTALPADDING) == 0) {
        
    } else if(strcmp(pPropertyName, PROPERTY_VERTICALPADDING) == 0) {
        
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINEWIDTH) == 0) {
        //((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
    } else if(strcmp(pPropertyName, PROPERTY_SHADOWBLURRADIUS) == 0) {
        //((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
    } else {
        ControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}

void ButtonLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_LABELANCHORPOINT) == 0) {
        ((ControlButton *)pNode)->setLabelAnchorPoint(pPoint);
    } else {
        ControlLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

void ButtonLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PREFERREDSIZE) == 0) {
        ((ControlButton *)pNode)->setPreferredSize(pSize);
    } else if(strcmp(pPropertyName, PROPERTY_MAXSIZE) == 0) {
        ((ControlButton *)pNode)->setMaxSize(pSize);
    } else {
        ControlLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}

void ButtonLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::NORMAL);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::HIGH_LIGHTED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::DISABLED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::SELECTED);
        }
    } else {
        ControlLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

void ButtonLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_SELECTED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::SELECTED);
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDCOLOR_NORMAL) == 0) {
        //((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDCOLOR_HIGHLIGHTED) == 0) {
        //((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDCOLOR_DISABLED) == 0) {
        //((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDCOLOR_SELECTED) == 0) {
        //((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::SELECTED);
    } else if(strcmp(pPropertyName, PROPERTY_FONTCOLOR) == 0) {
        //
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINECOLOR) == 0) {
        //
    } else if(strcmp(pPropertyName, PROPERTY_SHADOWCOLOR) == 0) {
        //
    } else {
        ControlLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}
    
void ButtonLoader::onHandlePropTypePosition(Node * pNode, Node * pParent, const char* pPropertyName, Point pPosition, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SHADOWOFFSET) == 0) {
    } else {
        NodeLoader::onHandlePropTypePosition(pNode, pParent, pPropertyName, pPosition, pCCBReader);
    }
}

};