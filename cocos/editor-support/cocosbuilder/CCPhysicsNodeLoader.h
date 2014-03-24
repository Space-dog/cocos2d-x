#ifndef _CCB_CCPHYSICSNODELOADER_H_
#define _CCB_CCPHYSICSNODELOADER_H_

#include "CCNodeLoader.h"
#include "CCPhysicsNode.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class PhysicsNodeLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~PhysicsNodeLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PhysicsNodeLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::PhysicsNode);
    virtual void onHandlePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Point pPoint, CCBReader * ccbReader) override;
    virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader) override;
};

}

#endif
