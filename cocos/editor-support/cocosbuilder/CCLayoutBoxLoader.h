#ifndef _CCB_CCLAYOUTBOXLOADER_H_
#define _CCB_CCLAYOUTBOXLOADER_H_

#include "CCNodeLoader.h"
#include "CCLayoutBox.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class LayoutBoxLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayoutBoxLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayoutBoxLoader, loader);
    //CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayoutBoxLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::LayoutBox);
    virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) override;
};

}

#endif
