#include "CCNode+CCBRelativePositioning.h"
#include "CCBReader.h"

using namespace cocos2d;

namespace cocosbuilder {

Point getAbsolutePosition(const Point &pt, CCBReader::PositionType type, const Size &containerSize, const std::string& propName)
{
    Point absPt = Point(0,0);
    if (type == CCBReader::PositionType::RELATIVE_BOTTOM_LEFT)
    {
        absPt = pt;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_LEFT)
    {
        absPt.x = pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_RIGHT)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_BOTTOM_RIGHT)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = pt.y;
    }
    else if (type == CCBReader::PositionType::PERCENT)
    {
        absPt.x = (int)(containerSize.width * pt.x / 100.0f);
        absPt.y = (int)(containerSize.height * pt.y / 100.0f);
    }
    else if (type == CCBReader::PositionType::MULTIPLY_RESOLUTION)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        absPt.x = pt.x * resolutionScale;
        absPt.y = pt.y * resolutionScale;
    }
    
    return absPt;
}

cocos2d::Size getRelativeScale(float scaleX, float scaleY, unsigned int type, const std::string& propName)
{
    
    float scaleXCoef = 1.0;
    float scaleYCoef = 1.0;
    
    if (type & static_cast<int>(CCBReader::ScaleType::MULTIPLY_RESOURCES_SCALE))
    {
        scaleXCoef *= CCBReader::getResolutionScale();
        scaleYCoef *= CCBReader::getResolutionScale();
    }
    
    if (type & static_cast<int>(CCBReader::ScaleType::MULTIPLY_MAIN_SCALE))
    {
        scaleXCoef *= CCBReader::getMainScale();
        scaleYCoef *= CCBReader::getMainScale();
    }
    
    if (type & static_cast<int>(CCBReader::ScaleType::MULTIPLY_ADDITION_SCALE))
    {
        scaleXCoef *= CCBReader::getResolutionScaleX();
        scaleYCoef *= CCBReader::getResolutionScaleY();
    }
    
    if (type & static_cast<int>(CCBReader::ScaleType::INVERT_SCALE))
    {
        scaleXCoef = 1.0f/scaleXCoef;
        scaleYCoef = 1.0f/scaleYCoef;
    }
    
    return Size(scaleX*scaleXCoef,scaleY*scaleYCoef);
}

Point getAbsolutePosition(const Point &pt, CCBReader::PositionReferenceCorner corner, CCBReader::PositionUnit xUnit, CCBReader::PositionUnit yUnit, const Size &containerSize, const char *pPropName)
{
    Point positionInPoints=Point(0,0);
    float x = 0;
    float y = 0;
    
    // Convert position to points
    if (xUnit == CCBReader::PositionUnit::POINTS) x = pt.x;
    else if (xUnit == CCBReader::PositionUnit::UIPOINTS) x = pt.x * CCBReader::getResolutionScale() * CCBReader::getMainScale();
    else if (xUnit == CCBReader::PositionUnit::NORMALIZED) x = pt.x * containerSize.width;
    
    if (yUnit == CCBReader::PositionUnit::POINTS) y = pt.y;
    else if (yUnit == CCBReader::PositionUnit::UIPOINTS) y = pt.y * CCBReader::getResolutionScale() * CCBReader::getMainScale();
    else if (yUnit == CCBReader::PositionUnit::NORMALIZED) y = pt.y * containerSize.height;
    
    // Account for reference corner
    //CCPositionReferenceCorner corner = type.corner;
    if (corner == CCBReader::PositionReferenceCorner::BOTTOMLEFT)
    {
        // Nothing needs to be done
    }
    else if (corner == CCBReader::PositionReferenceCorner::TOPLEFT)
    {
        // Reverse y-axis
        y = containerSize.height - y;
    }
    else if (corner == CCBReader::PositionReferenceCorner::TOPRIGHT)
    {
        // Reverse x-axis and y-axis
        x = containerSize.width - x;
        y = containerSize.height - y;
    }
    else if (corner == CCBReader::PositionReferenceCorner::BOTTOMRIGHT)
    {
        // Reverse x-axis
        x = containerSize.width - x;
    }
    
    positionInPoints.x = x;
    positionInPoints.y = y;
    
    return positionInPoints;
}

Size getAbsoluteSize(const Size &contentSize, CCBReader::SizeUnit widthUnit, CCBReader::SizeUnit heightUnit, const Size &containerSize)
{
    Size size = Size::ZERO;
    
    // Width
    if (widthUnit == CCBReader::SizeUnit::POINTS)
    {
        size.width = contentSize.width;
    }
    else if (widthUnit == CCBReader::SizeUnit::UIPOINTS)
    {
        size.width = CCBReader::getResolutionScale() * CCBReader::getMainScale() * contentSize.width;
    }
    else if (widthUnit == CCBReader::SizeUnit::NORMALIZED)
    {
        size.width = contentSize.width * containerSize.width;
    }
    else if (widthUnit == CCBReader::SizeUnit::INSETPOINTS)
    {
        size.width = containerSize.width - contentSize.width;
    }
    else if (widthUnit == CCBReader::SizeUnit::INSETUIPOINTS)
    {
        size.width = containerSize.width - contentSize.width * CCBReader::getResolutionScale() * CCBReader::getMainScale();
    }
        
    // Height
    if (heightUnit == CCBReader::SizeUnit::POINTS)
    {
        size.height = contentSize.height;
    }
    else if (heightUnit == CCBReader::SizeUnit::UIPOINTS)
    {
        size.height = CCBReader::getResolutionScale() * CCBReader::getMainScale() * contentSize.height;
    }
    else if (heightUnit == CCBReader::SizeUnit::NORMALIZED)
    {
        size.height = contentSize.height * containerSize.height;
    }
    else if (heightUnit == CCBReader::SizeUnit::INSETPOINTS)
    {
        size.height = containerSize.height - contentSize.height;
    }
    else if (heightUnit == CCBReader::SizeUnit::INSETUIPOINTS)
    {
        size.height = containerSize.height - contentSize.height * CCBReader::getResolutionScale() * CCBReader::getMainScale();
    }
    
    return size;
}

}
