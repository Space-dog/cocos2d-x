#ifndef _CCB_CCLAYERCOLORLOADER_H_
#define _CCB_CCLAYERCOLORLOADER_H_

#include "CCLayerLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class LayerColorLoader : public LayerLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayerColorLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerColorLoader, loader);

protected:
    virtual cocos2d::LayerColor * createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * ccbReader) {
        cocos2d::LayerColor *layer = cocos2d::LayerColor::create();
        layer->ignoreAnchorPointForPosition(false);
        return layer;
    }

    virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color3B pColor3B, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader) override;
};

}

#endif
