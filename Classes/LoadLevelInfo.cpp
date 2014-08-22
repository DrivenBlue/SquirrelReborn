//
//  LoadLevelInfo.cpp
//  SquirrelReborn
//
//  Created by David Wang on 8/21/14.
//
// This class loads and searches through the plists in order to obtain map etc.
// It also checks the current level and what the next level is going to be.

#include "LoadLevelInfo.h"
#include "GameManager.h"

LoadLevelInfo::~LoadLevelInfo()
{
    clearAll();
}

LoadLevelInfo *LoadLevelInfo::createLoadLevelInfo(const std::string& plistpath)
{
    //must delete whenever new is used if not autoreleased
    LoadLevelInfo *pRet = new LoadLevelInfo();
    if (pRet && pRet->initPlist(plistpath))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool LoadLevelInfo::initPlist(const std::string& plistpath)
{
    bool bRet = false;
    do
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plistpath);
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        
        resources = dict["resources"].asValueMap();
        levelInfo = dict["levelInfo"].asValueMap();
        
        bRet = true;
    }
    while (0);
    return bRet;
}

void LoadLevelInfo::clearAll()
{
    resources.clear();
    levelInfo.clear();
}

//reading and obtaining plists
void LoadLevelInfo::readLevelInfo()
{
	GameManager *instance = GameManager::getInstance();
    
	auto currlevel =   levelInfo["currlevel"].asString();
	instance->setCurrLevelFile(currlevel);
	auto nextlevel =   levelInfo["nextlevel"].asString();
	instance->setNextLevelFile(nextlevel);

    //error created when deleting group off of plist
    //could use this for grabbing enemy objects
    //ValueMap& groupDict = levelInfo["group"].asValueMap();
    
	//auto groupTotle = groupDict.size();
	//instance->setGroupNum(groupTotle);
    
    
	auto curMapName =   resources["map"].asString();
	instance->setCurMapName(curMapName);
	auto curBgName =   resources["image"].asString();
	instance->setCurBgName(curBgName);
    
}


