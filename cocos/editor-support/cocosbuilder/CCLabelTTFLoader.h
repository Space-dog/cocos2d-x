#ifndef _CCB_CCLABELTTFLOADER_H_
#define _CCB_CCLABELTTFLOADER_H_

#include "CCRef.h"
#include "CCLabel.h"

#include "CCNodeLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class LabelTTFLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelTTFLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LabelTTFLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Label);

    virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color3B pColor3B, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader);
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeFontTTF(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeText(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pText, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader) override;
    virtual void onHandlePropTypePosition(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * pCCBReader) override;
};

}

#endif
