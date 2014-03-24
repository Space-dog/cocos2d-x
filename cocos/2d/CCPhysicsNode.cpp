/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCPhysicsNode.h"
#include "CCDirector.h"
#include "CCLayer.h"
#include "CCSprite.h"
#include "CCSpriteBatchNode.h"
#include "CCPhysicsWorld.h"

NS_CC_BEGIN

PhysicsNode::PhysicsNode()
#if CC_USE_PHYSICS
: _physicsWorld(nullptr)
#endif
{
}

PhysicsNode::~PhysicsNode()
{
#if CC_USE_PHYSICS
    CC_SAFE_DELETE(_physicsWorld);
#endif
}

bool PhysicsNode::init()
{
    return true;
}

PhysicsNode *PhysicsNode::create()
{
    PhysicsNode *ret = new PhysicsNode();
#if CC_USE_PHYSICS
    if (ret && ret->initWithPhysics())
#else
    if (ret && ret->init())
#endif
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

std::string PhysicsNode::getDescription() const
{
    return StringUtils::format("<Scene | tag = %d>", _tag);
}

#if CC_USE_PHYSICS
void PhysicsNode::addChild(Node* child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    addChildToPhysicsWorld(child);
}

void PhysicsNode::update(float delta)
{
    Node::update(delta);
    if (nullptr != _physicsWorld)
    {
        _physicsWorld->update(delta);
    }
}

bool PhysicsNode::initWithPhysics()
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(! (_physicsWorld = PhysicsWorld::construct(*this)));
        this->scheduleUpdate();
        // success
        ret = true;
    } while (0);
    return ret;
}

void PhysicsNode::addChildToPhysicsWorld(Node* child)
{
    if (_physicsWorld)
    {
        std::function<void(Node*)> addToPhysicsWorldFunc = nullptr;
        addToPhysicsWorldFunc = [this, &addToPhysicsWorldFunc](Node* node) -> void
        {
            if (node->getPhysicsBody())
            {
                kmMat4 transform;
                kmMat4Identity(&transform);
                if(node->getParent())
                {
                    transform = node->getParent()->getNodeToPhysicsTransform();
                    kmVec3 vec3 = {node->getPosition().x, node->getPosition().y, 0};
                    kmVec3 ret;
                    kmVec3Transform(&ret, &vec3, &transform);
                    node->getPhysicsBody()->setPosition(Point(ret.x, ret.y));
                    node->getPhysicsBody()->setRotation(node->getParent()->getNodeToPhysicsRotation() + node->getRotation());
                }
                if(transform.mat[1] != -transform.mat[4])
                    CCLOGWARN("PhysicsNode::addChildToPhysicsWorld skew not supported for physics nodes");
                node->getPhysicsBody()->rescale(Size(transform.mat[0] * node->getScaleX(), transform.mat[5] * node->getScaleY()));
                _physicsWorld->addBody(node->getPhysicsBody());
            }
            
            auto& children = node->getChildren();
            for( const auto &n : children) {
                addToPhysicsWorldFunc(n);
            }
        };
        
        addToPhysicsWorldFunc(child);
    }
}
#endif

NS_CC_END
