/*
 * Copyright (c) 2014      Perepelitsa Sergey
 * Copyright (c) 2014      cocos2d-x.org
 *
 * http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef __MISCNODE_CCLAYOUT_H__
#define __MISCNODE_CCLAYOUT_H__

#include "CCNode.h"

NS_CC_BEGIN

/**
 *  A LayoutNode will take control of its childrens' positions. Any node added as a child will be position according to the rules of the specific layout type. If you are using a layout you should not set the position of the children manually.
 
 ### Subclassing
 
 LayoutNode is an abstract super class of all layouts. You should subclass this class and implement the layout method if you want to create your own layout.
 */
class  LayoutNode : public Node
{
public:
    /**
     *  Called whenever the node needs to layout its children again. Normally, there is no need to call this method directly.
     */
    virtual void needsLayout();
    /**
     *  The layout method layouts the children according to the rules of the specific layout.
     */
    virtual void layout();
    virtual void visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated) override;
    virtual void addChild(Node *child, int zOrder, int tag) override;
    virtual void removeChild(Node* child, bool cleanup = true) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;

protected:
    LayoutNode();
    virtual ~LayoutNode();
    virtual bool init() override;
    
private:
    mutable bool _needsLayout;
    CC_DISALLOW_COPY_AND_ASSIGN(LayoutNode);
};

NS_CC_END

#endif // __MISCNODE_CCLAYOUT_H__
