#include "CCBReaderParams.h"
#include "platform/CCFileUtils.h"
#include "CCApplication.h"
#include "CCDirector.h"
#include "CCSpriteFrameCache.h"
#include <unordered_set>

using namespace cocos2d;

namespace cocosbuilder {

CCBReaderParams::CCBReaderParams():_loaded(false) {
}

CCBReaderParams::~CCBReaderParams() {
}
    
bool CCBReaderParams::initWithPath(const std::string &path)
{
    _loaded = loadParams(path);
    loadLocalization(path);
    FileUtils::getInstance()->loadFilenameLookupDictionaryFromFile(path+"fileLookup.plist");
    SpriteFrameCache::getInstance()->loadSpriteFrameLookupDictionaryFromFile(path+"spriteFrameFileList.plist");
    return true;
}
    
bool CCBReaderParams::isLoaded() const
{
    return _loaded;
}
    
bool CCBReaderParams::loadParams(const std::string &path)
{
    std::string fullConfigPath = FileUtils::getInstance()->fullPathForFilename(path+"configCocos2d.plist");
    ValueMap configDict = FileUtils::getInstance()->getValueMapFromFile(fullConfigPath);
    
    if(configDict.empty())
        return false;
    
    auto scale = configDict.find("CCSetupDesignResourceScale");
    if (scale != configDict.end())
        _designResolutionscale = scale->second.asDouble();
    else
        _designResolutionscale = 1.0f;
    
    auto height = configDict.find("CCSetupDesignSizeHeight");
    if (height != configDict.end())
        _designResolution.height = height->second.asInt();
    else
        _designResolution.height = Director::getInstance()->getWinSize().height;
    
    auto width = configDict.find("CCSetupDesignSizeWidth");
    if (width != configDict.end())
        _designResolution.width = width->second.asInt();
    else
        _designResolution.width = Director::getInstance()->getWinSize().width;
    
    return true;
}
    

bool CCBReaderParams::loadLocalization(const std::string &path)
{
    std::string fullTranslationPath = FileUtils::getInstance()->fullPathForFilename(path+"Strings.ccbLang");
    ValueMap translationDict = FileUtils::getInstance()->getValueMapFromFile(fullTranslationPath);
    
    auto fileVersion = translationDict.find("fileVersion");
    if(fileVersion ==translationDict.end() )
        return false;
    if(fileVersion->second.asInt() != 1)
        return false;
    auto activeLanguages = translationDict.find("activeLanguages");
    if (activeLanguages != translationDict.end()) {
        std::unordered_set<std::string> languages;
        for(auto language : activeLanguages->second.asValueVector())
            languages.insert(language.asString());
        _curentLanguage = Application::getInstance()->getCurrentLanguageCode();
        if(languages.find(_curentLanguage) == languages.end())
            _curentLanguage = *languages.begin();
    }
    auto translations = translationDict.find("translations");
    if (translations != translationDict.end()) {
        const ValueVector &valueVector = translations->second.asValueVector();
        for(auto value: valueVector)
        {
            const ValueMap &valueMap = value.asValueMap();
            auto key = valueMap.find("key");
            if(key!= valueMap.end())
            {
                auto strings = valueMap.find("translations");
                for(auto localizedString : strings->second.asValueMap())
                {
                    _languages[localizedString.first][key->second.asString()] = localizedString.second.asString();
                }
            }
        }
    }
    return true;
}
    
const std::string &CCBReaderParams::getLocalizedString(const std::string &key) const
{
    auto language = _languages.find(_curentLanguage);
    if(language == _languages.end())
        return key;
    auto recordIt = language->second.find(key);
    if(recordIt == language->second.end())
        return key;
    return recordIt->second;
}
    
static CCBReaderParams * sSharedReaderParams = NULL;

CCBReaderParams * CCBReaderParams::getInstance()
{
    if(sSharedReaderParams == NULL)
    {
        sSharedReaderParams = new CCBReaderParams();
        sSharedReaderParams->initWithPath();
    }
    return sSharedReaderParams;
}
    
void CCBReaderParams::destroyInstance()
{
    CC_SAFE_DELETE(sSharedReaderParams);
}
    
}