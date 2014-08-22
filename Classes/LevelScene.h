//
//  LevelScene.h
//  SquirrelReborn
//
//  Created by David Wang on 8/21/14.
//
//

#ifndef __SquirrelReborn__LevelScene__
#define __SquirrelReborn__LevelScene__

#include <iostream>
#include "cocos2d.h"

class LevelScene : public cocos2d::Scene
{
public:
    
    virtual bool init();
    CREATE_FUNC(LevelScene);
    void menuCloseCallback(Ref* pSender);
    static LevelScene *getInstance();
    
private:
    static LevelScene *instance;
}; 

#endif /* defined(__SquirrelReborn__LevelScene__) */
