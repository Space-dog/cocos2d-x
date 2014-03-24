#include "CCPhysicsNodeLoader.h"

using namespace cocos2d;

namespace cocosbuilder {
    
#define PROPERTY_GRAVITY "gravity"
#define PROPERTY_SLEEPTIMETHRESHOLD "sleepTimeThreshold"
    
void PhysicsNodeLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char* pPropertyName, Point pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_GRAVITY) == 0) {
        ((PhysicsNode*)pNode)->getPhysicsWorld()->setGravity(pPoint);
    } else {
        NodeLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}
    
void PhysicsNodeLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader)
{
    if(strcmp(pPropertyName, PROPERTY_SLEEPTIMETHRESHOLD) == 0) {
        //((PhysicsNode*)pNode)->getPhysicsWorld()->setGravity(pPoint);
    } else {
        NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, ccbReader);
    }
}

}