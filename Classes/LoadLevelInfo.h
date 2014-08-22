//
//  LoadLevelInfo.h
//  SquirrelReborn
//
//  Created by David Wang on 8/21/14.
//
//

#ifndef __SquirrelReborn__LoadLevelInfo__
#define __SquirrelReborn__LoadLevelInfo__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class LoadLevelInfo: public Ref
{
public:
    
    ~LoadLevelInfo();
    static LoadLevelInfo * createLoadLevelInfo(const std::string& plistpath);
    
    bool initPlist(const std::string& plistpath);
	void readLevelInfo();
    void clearAll();
    
private:
    ValueMap resources;
    ValueMap levelInfo;
};

#endif /* defined(__SquirrelReborn__LoadLevelInfo__) */
