#ifndef _CCB_CCLAYERGRADIENTLOADER_H_
#define _CCB_CCLAYERGRADIENTLOADER_H_

#include "CCLayerLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class LayerGradientLoader : public LayerLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayerGradientLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerGradientLoader, loader);

protected:
    virtual cocos2d::LayerGradient * createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * ccbReader) {
        cocos2d::LayerGradient *layer = cocos2d::LayerGradient::create();
        layer->ignoreAnchorPointForPosition(false);
        return layer;
    }

    virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color3B pColor3B, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader) override;
    virtual void onHandlePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Point pPoint, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader) override;
};

}

#endif
