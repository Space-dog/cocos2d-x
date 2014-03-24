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

#ifndef __MISCNODE_CCLAYOUTBOX_H__
#define __MISCNODE_CCLAYOUTBOX_H__

#include "CCLayoutNode.h"

NS_CC_BEGIN

enum class LayoutBoxDirection
{
    /// The children will be layout out in a horizontal line.
    Horizontal,
    
    /// The children will be layout out in a vertical line.
    Vertical,
};

/**
 *  The box layout lays out its children in a horizontal or vertical row. Optionally you can set a spacing between the child nodes.
 */
class  LayoutBox : public LayoutNode
{
public:
    /** creates and initialize a LayoutBox */
    static LayoutBox* create();
    /**
     *  The layout method layouts the children according to the rules of the specific layout.
     */
    virtual void layout() override;
    
    /**
     *  The direction is either horizontal or vertical.
     */
    LayoutBoxDirection getDirection() const;
    void setDirection(LayoutBoxDirection direction);
    
    /**
     *  The spacing in points between the child nodes.
     */
    float getSpacing() const;
    void setSpacing(float spacing);

protected:
    LayoutBox();
    virtual ~LayoutBox();
    
private:
    LayoutBoxDirection _direction;
    float _spacing;
    
    CC_DISALLOW_COPY_AND_ASSIGN(LayoutBox);
};

NS_CC_END

#endif // __MISCNODE_CCLAYOUTBOX_H__
