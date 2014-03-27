/*
 * Copyright (c) 2014 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2013 Apportable Inc.
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
 */

#include "CCButton.h"
#include "CCLabel.h"
#include "CCScale9Sprite.h"
#include "CCAction.h"
#include "CCActionInterval.h"

NS_CC_EXT_BEGIN

Button::Button():_background(Scale9Sprite::create()),_label(Label::create()),_zoomWhenHighlighted(false),_horizontalPadding(0),_verticalPadding(0),_togglesSelectedState(false),_preferredSize(0,0),_maxSize(0,0),_needLaout(true)
{
    _ignoreAnchorPointForPosition = false;
    addChild(_background);
    addChild(_label);
    _label->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    _label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
}
Button::~Button()
{
    
}

Button *Button::create()
{
    Button *ret = new Button();
    
    if (!ret)
        return nullptr;
    
    if(!ret->init())
    {
        delete ret;
        return nullptr;
    }
    
    ret->autorelease();
    
    return ret;
}
Button *Button::create(const std::string &title, const std::string &fontName, float size, SpriteFrame* normal, SpriteFrame* highlighted, SpriteFrame* disabled, SpriteFrame* selected)
{
    Button *ret = new Button();
    
    if (ret)
    {
        if(!ret->init())
        {
            delete ret;
            return nullptr;
        }
        ret->_title = title;
        ret->setFontName(fontName);
        ret->setFontSize(size);
        ret->_backgroundSpriteFrames.insert(static_cast<int>(Control::State::NORMAL), normal);
        ret->_backgroundSpriteFrames.insert(static_cast<int>(Control::State::HIGH_LIGHTED), highlighted);
        ret->_backgroundSpriteFrames.insert(static_cast<int>(Control::State::DISABLED), disabled);
        ret->_backgroundSpriteFrames.insert(static_cast<int>(Control::State::SELECTED), selected);
        ret->autorelease();
    }
    
    return ret;
}

bool Button::onTouchBegan(Touch *touch, Event *event)
{
    if (!isTouchInside(touch) || !isEnabled() || !isVisible() || !hasVisibleParents() )
    {
        return false;
    }
    this->setHighlighted(true);
    sendActionsForControlEvents(Control::EventType::TOUCH_DOWN);
    return true;
}
void Button::onTouchMoved(Touch *touch, Event *event)
{
    if (!isEnabled())
    {
        return;
    }
    
    bool isTouchMoveInside = isTouchInside(touch);
    if (isTouchMoveInside && !isHighlighted())
    {
        setHighlighted(true);
        sendActionsForControlEvents(Control::EventType::DRAG_ENTER);
    }
    else if (isTouchMoveInside && isHighlighted())
    {
        sendActionsForControlEvents(Control::EventType::DRAG_INSIDE);
    }
    else if (!isTouchMoveInside && isHighlighted())
    {
        setHighlighted(false);
        
        sendActionsForControlEvents(Control::EventType::DRAG_EXIT);
    }
    else if (!isTouchMoveInside && !isHighlighted())
    {
        sendActionsForControlEvents(Control::EventType::DRAG_OUTSIDE);
    }

}
void Button::onTouchEnded(Touch *touch, Event *event)
{
    setHighlighted(false);
    if (isTouchInside(touch))
    {
        if (_togglesSelectedState)
        {
            setSelected(!_selected);
        }
        sendActionsForControlEvents(Control::EventType::TOUCH_UP_INSIDE);
    }
    else
    {
        sendActionsForControlEvents(Control::EventType::TOUCH_UP_OUTSIDE);
    }
}
void Button::onTouchCancelled(Touch *touch, Event *event)
{
    setHighlighted(false);
    sendActionsForControlEvents(Control::EventType::TOUCH_CANCEL);
}

void Button::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    stateChanged();
}

void Button::setSelected(bool enabled)
{
    Control::setSelected(enabled);
    stateChanged();
}

void Button::setHighlighted(bool enabled)
{
    Control::setHighlighted(enabled);
    stateChanged();
}

void Button::visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated)
{
    if (!_visible)
        return;
    
    if(_needLaout)
        layout();
    
    Control::visit(renderer, parentTransform, parentTransformUpdated);
}

const Size& Button::getContentSize() const
{
    if (_needLaout)
    {
        const_cast<Button*>(this)->layout();
    }
    return Node::getContentSize();
}

void Button::updatePropertiesForState(Control::State state)
{
    // Update background
    _background->setColor(getBackgroundColorForState(state));
    _background->setOpacity(getBackgroundOpacityForState(state));
    
    SpriteFrame* spriteFrame = getBackgroundSpriteFrameForState(state);
    if (!spriteFrame)
        spriteFrame = getBackgroundSpriteFrameForState(Control::State::NORMAL);
    if (spriteFrame)
    {
        _background->setSpriteFrame(spriteFrame);
        Size size = _background->getOriginalSize();
        _background->setCapInsets(Rect(_margin.left*size.width,_margin.top*size.height,(1.0f-_margin.right-_margin.left)*size.width,(1.0f-_margin.bottom-_margin.top)*size.height));
    }
    
    // Update label
    _label->setColor(getLabelColorForState(state));
    _label->setOpacity(getLabelOpacityForState(state));
    
    needsLayout();
}

void Button::stateChanged()
{
    if (isEnabled())
    {
        // Button is enabled
        if (isHighlighted())
        {
            updatePropertiesForState(Control::State::HIGH_LIGHTED);
            
            if (_zoomWhenHighlighted)
            {
                _label->runAction(ScaleTo::create(0.1, 1.2));
                _background->runAction(ScaleTo::create(0.1, 1.2));
            }
        }
        else
        {
            if (isSelected())
            {
                updatePropertiesForState(Control::State::SELECTED);
            }
            else
            {
                updatePropertiesForState(Control::State::NORMAL);
            }
            
            _label->stopAllActions();
            _background->stopAllActions();
            if (_zoomWhenHighlighted)
            {
                _label->setScaleX(1.0f);
                _label->setScaleY(1.0f);
                
                _background->setScaleX(1.0f);
                _background->setScaleY(1.0f);
            }
        }
    }
    else
    {
        // Button is disabled
        updatePropertiesForState(Control::State::DISABLED);
    }
}

void Button::needsLayout()
{
    _needLaout = true;
    Control::needsLayout();
}

void Button::layout()
{
    _label->setDimensions(0,0);
    Size originalLabelSize = _label->getContentSize();
    Size paddedLabelSize = originalLabelSize;
    paddedLabelSize.width += _horizontalPadding * 2;
    paddedLabelSize.height += _verticalPadding * 2;
    
    bool shrunkSize = false;
    Size size = _preferredSize;
    
    Size maxSize = _maxSize;
    
    if (size.width < paddedLabelSize.width)
        size.width = paddedLabelSize.width;
    if (size.height < paddedLabelSize.height)
        size.height = paddedLabelSize.height;
    
    if (maxSize.width > 0 && maxSize.width < size.width)
    {
        size.width = maxSize.width;
        shrunkSize = true;
    }
    if (maxSize.height > 0 && maxSize.height < size.height)
    {
        size.height = maxSize.height;
        shrunkSize = true;
    }
    
    if (shrunkSize)
    {
        Size labelSize = Size(clampf(size.width - _horizontalPadding * 2, 0, originalLabelSize.width),
                                      clampf(size.height - _verticalPadding * 2, 0, originalLabelSize.height));
        _label->setDimensions(labelSize.width, labelSize.height);
    }
    
    _background->setContentSize(size);
    _background->setAnchorPoint(Point(0.5f,0.5f));
    _background->setPosition(Point(size.width/2,size.height/2));
    
    _label->setPosition(Point(size.width/2,size.height/2));
    
    setContentSize(size);
    
    _needLaout = false;
}

void Button::setPreferredSize(const Size& value)
{
    _preferredSize = value;
    needsLayout();
}

const Size& Button::getPreferredSize() const
{
    return _preferredSize;
}

void Button::setMaxSize(const Size& value)
{
    _maxSize = value;
    needsLayout();
}

const Size& Button::getMaxSize() const
{
    return _maxSize;
}

Scale9Sprite* Button::getBackground() const
{
    return _background;
}
Label* Button::getLabel() const
{
    return _label;
}

void Button::setZoomWhenHighlighted(bool value)
{
    _zoomWhenHighlighted = value;
}
const bool Button::getZoomWhenHighlighted() const
{
    return _zoomWhenHighlighted;
}

void Button::setHorizontalPadding(float value)
{
    _horizontalPadding = value;
    needsLayout();
}
const float Button::getHorizontalPadding() const
{
    return _horizontalPadding;
}

void Button::setVerticalPadding(float value)
{
    _verticalPadding = value;
    needsLayout();
}

const float Button::getVerticalPadding() const
{
    return _verticalPadding;
}

void Button::setTogglesSelectedState(bool value)
{
    _togglesSelectedState = true;
}

const bool Button::getTogglesSelectedState() const
{
    return _togglesSelectedState;
}

void Button::setTitle(const std::string& value)
{
    _title = value;
    _label->setString(value);
    needsLayout();
}
const std::string& Button::getTitle() const
{
    return _title;
}

void Button::setFontName(const std::string& value)
{
    _label->setFontName(value);
    needsLayout();
}

const std::string& Button::getFontName() const
{
    return _label->getFontName();
}

void Button::setFontSize(float value)
{
    _label->setFontSize(value);
    needsLayout();
}
const float Button::getFontSize() const
{
    return _label->getFontSize();
}

void Button::setMargine(const ui::Margin& value)
{
    _margin = value;
    stateChanged();
}

const ui::Margin& Button::getMargine() const
{
    return _margin;
}

void Button::setBackgroundColor(const Color3B& color, Control::State state)
{
    _backgroundColors[state] = color;
    stateChanged();
}

const Color3B& Button::getBackgroundColorForState(Control::State state) const
{
    auto it = _backgroundColors.find(state);
    if(it != _backgroundColors.end())
        return it->second;
    else
        return Color3B::WHITE;
}

void Button::setBackgroundOpacity(GLubyte opacity, Control::State state)
{
    _backgroundOpacities[state] = opacity;
    stateChanged();
}

GLubyte Button::getBackgroundOpacityForState(Control::State state) const
{
    auto it = _backgroundOpacities.find(state);
    if(it != _backgroundOpacities.end())
        return it->second;
    else
        return 255;
}


void Button::setLabelColor(const Color3B& color, Control::State state)
{
    _labelColors[state] = color;
    stateChanged();
}


const Color3B& Button::getLabelColorForState(Control::State state) const
{
    auto it = _labelColors.find(state);
    if(it != _labelColors.end())
        return it->second;
    else
        return Color3B::WHITE;
}


void Button::setLabelOpacity(GLubyte opacity, Control::State state)
{
    _labelOpacities[state] = opacity;
    stateChanged();
}


GLubyte Button::getLabelOpacityForState(Control::State state) const
{
    auto it = _labelOpacities.find(state);
    if(it != _labelOpacities.end())
        return it->second;
    else
        return 255;
}


void Button::setBackgroundSpriteFrame(SpriteFrame* spriteFrame, Control::State state)
{
    auto it=_backgroundSpriteFrames.find(static_cast<int>(state));
    if(it!=_backgroundSpriteFrames.end())
        _backgroundSpriteFrames.erase(it);
    _backgroundSpriteFrames.insert(static_cast<int>(state), spriteFrame);
    stateChanged();
}


SpriteFrame* Button::getBackgroundSpriteFrameForState(Control::State state) const
{
    auto it=_backgroundSpriteFrames.find(static_cast<int>(state));
    if(it!=_backgroundSpriteFrames.end())
        return it->second;
    else
        return nullptr;
}

NS_CC_EXT_END
