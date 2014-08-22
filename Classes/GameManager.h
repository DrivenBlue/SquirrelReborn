//
//  GameManager.h
//  SquirrelReborn
//
//  Created by David Wang on 8/22/14.
//
//

#ifndef __SquirrelReborn__GameManager__
#define __SquirrelReborn__GameManager__

#include <iostream>
#include "cocos2d.h"



USING_NS_CC;

class GameManager
{
public:
    
	CC_SYNTHESIZE(std::string, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(std::string, curBgName, CurBgName);
    
    bool init();
	void clear();
    
	static GameManager* getInstance();
    
private:
	static GameManager * instance;
};


#endif /* defined(__SquirrelReborn__GameManager__) */
