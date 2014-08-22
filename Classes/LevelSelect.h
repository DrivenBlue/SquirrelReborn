//
//  LevelSelect.h
//  SquirrelReborn
//
//  Created by David Wang on 8/21/14.
//
//

#ifndef __SquirrelReborn__LevelSelect__
#define __SquirrelReborn__LevelSelect__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class LevelSelectPage: public Node
{
public:
    
    bool initLevelPage(const std::string& bgName, int level);
    static LevelSelectPage* create(const std::string& bgName, int level);
    void menuStartCallback(Ref* pSender);
};

#endif /* defined(__SquirrelReborn__LevelSelect__) */
