#include "CCLayoutBoxLoader.h"

using namespace cocos2d;

namespace cocosbuilder {
    
#define PROPERTY_SPACING "spacing"
#define PROPERTY_DIRECTION "direction"
    
void LayoutBoxLoader::onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader)
{
    if(strcmp(pPropertyName, PROPERTY_SPACING) == 0) {
        ((LayoutBox *)pNode)->setSpacing(pFloatScale);
    } else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }

}
void LayoutBoxLoader::onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader)
{
    if(strcmp(pPropertyName, PROPERTY_DIRECTION) == 0) {
        ((LayoutBox *)pNode)->setDirection(static_cast<cocos2d::LayoutBoxDirection>(pIntegerLabeled));
    } else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
    }
}

}