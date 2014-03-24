#include "CCProgressTimerLoader.h"

#define PROPERTY_FLIP "flip"
#define PROPERTY_DISPLAYFRAME "spriteFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_TYPE       "type"
#define PROPERTY_MIDPOINT   "midpoint"
#define PROPERTY_BARCHANGERATE "barChangeRate"
#define PROPERTY_PERCENTAGE "percentage"
#define PROPERTY_REVERSEDIR "reverseDirection"

USING_NS_CC;

namespace cocosbuilder {

void ProgressTimerLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_DISPLAYFRAME) == 0) {
        if(pCCSpriteFrame != NULL) {
            Sprite *temp=((ProgressTimer *)pNode)->getSprite();
            temp->retain();
            ((ProgressTimer *)pNode)->setSprite(NULL);
            temp->setDisplayFrame(pCCSpriteFrame);
            ((ProgressTimer *)pNode)->setSprite(temp);
            temp->release();
        } else {
            CCLOG("ERROR: SpriteFrame NULL");
        }
    } else {
        NodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypeFlip(Node * pNode, Node * pParent, const char * pPropertyName, bool * pFlip, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FLIP) == 0) {
        ((ProgressTimer *)pNode)->getSprite()->setFlippedX(pFlip[0]);
        ((ProgressTimer *)pNode)->getSprite()->setFlippedY(pFlip[1]);
        ((ProgressTimer *)pNode)->setSprite(((ProgressTimer *)pNode)->getSprite());
    } else {
        NodeLoader::onHandlePropTypeFlip(pNode, pParent, pPropertyName, pFlip, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pCCColor3B, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((ProgressTimer *)pNode)->setColor(pCCColor3B);
    } else {
        NodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((ProgressTimer *)pNode)->setOpacity(pByte);
    } else {
        NodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((ProgressTimer *)pNode)->getSprite()->setBlendFunc(pCCBlendFunc);
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypeIntegerLabeled(Node *pNode, Node *pParent, const char *pPropertyName, int pIntegerLabeled, CCBReader *pCCBReader)
{
    if (strcmp(pPropertyName, PROPERTY_TYPE) == 0) {
        ((ProgressTimer *)pNode)->setType((ProgressTimer::Type)pIntegerLabeled);
    } else {
        NodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypePoint(Node *pNode, Node *pParent, const char *pPropertyName, Point pPoint, CCBReader *pCCBReader)
{
    if (strcmp(pPropertyName, PROPERTY_MIDPOINT) == 0) {
        ((ProgressTimer *)pNode)->setMidpoint(pPoint);
    } else if (strcmp(pPropertyName, PROPERTY_BARCHANGERATE) == 0) {
        ((ProgressTimer *)pNode)->setBarChangeRate(pPoint);
    } else if (strcmp(pPropertyName, "anchorPoint") == 0) {
        ((ProgressTimer *)pNode)->setAnchorPoint(pPoint);
    }
    else {
        NodeLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypeFloat(Node *pNode, Node *pParent, const char *pPropertyName, float pFloat, CCBReader *pCCBReader)
{
    if (strcmp(pPropertyName, PROPERTY_PERCENTAGE) == 0) {
        ((ProgressTimer *)pNode)->setPercentage(pFloat);
    }
    else {
        NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void ProgressTimerLoader::onHandlePropTypeCheck(Node *pNode, Node *pParent, const char *pPropertyName, bool pCheck, CCBReader *pCCBReader)
{
    if (strcmp(pPropertyName, PROPERTY_REVERSEDIR) == 0) {
        ((ProgressTimer *)pNode)->setReverseDirection(pCheck);
    }
    else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

}
