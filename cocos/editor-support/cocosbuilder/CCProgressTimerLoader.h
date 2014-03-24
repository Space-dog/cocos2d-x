#ifndef _CCB_CCPROGRESSTIMERLOADER_H_
#define _CCB_CCPROGRESSTIMERLOADER_H_

#include "CCNodeLoader.h"
#include "CCProgressTimer.h"

namespace cocosbuilder {
    
/* Forward declaration. */
class CCBReader;

class ProgressTimerLoader : public NodeLoader {
public:
    virtual ~ProgressTimerLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ProgressTimerLoader, loader);
    
protected:
    //CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCSprite);
    
    virtual cocos2d::ProgressTimer* createNode(cocos2d::Node * pParent, CCBReader * pCCBReader) override
    {
        return cocos2d::ProgressTimer::create(cocos2d::Sprite::create());
    }
    
    virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color3B pCCColor3B, CCBReader * pCCBReader);
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pCCBBlendFunc, CCBReader * pCCBReader);
    virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader);
    virtual void onHandlePropTypeFlip(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, bool * pFlip, CCBReader * pCCBReader);
    virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node *pNode, cocos2d::Node *pParent, const char *pPropertyName, int pIntegerLabeled, CCBReader *pCCBReader);
    virtual void onHandlePropTypePoint(cocos2d::Node *pNode, cocos2d::Node * pParent, const char *pPropertyName, cocos2d::Point pPoint, CCBReader * pCCBReader);
    virtual void onHandlePropTypeFloat(cocos2d::Node *pNode, cocos2d::Node *pParent, const char *pPropertyName, float pFloat, CCBReader *pCCBReader);
    virtual void onHandlePropTypeCheck(cocos2d::Node *pNode, cocos2d::Node *pParent, const char *pPropertyName, bool pCheck, CCBReader *pCCBReader);
};
    
}

#endif
