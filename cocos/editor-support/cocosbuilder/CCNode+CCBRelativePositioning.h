#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "CCBReader.h"

namespace cocosbuilder {

extern cocos2d::Point getAbsolutePosition(const cocos2d::Point &pt, CCBReader::PositionType type, const cocos2d::Size &containerSize, const std::string&propName);

extern cocos2d::Size getRelativeScale(float scaleX, float scaleY, unsigned int type, const std::string& propName);
    
extern cocos2d::Point getAbsolutePosition(const cocos2d::Point &pt, CCBReader::PositionReferenceCorner corner, CCBReader::PositionUnit xUnit, CCBReader::PositionUnit yUnit, const cocos2d::Size &containerSize, const char *pPropName);
    
extern cocos2d::Size getAbsoluteSize(const cocos2d::Size &contentSize, CCBReader::SizeUnit widthUnit, CCBReader::SizeUnit heightUnit, const cocos2d::Size &containerSize);

}

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
