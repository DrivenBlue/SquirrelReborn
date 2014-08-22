//
//  TitleScene.h
//  SquirrelReborn
//
//  Created by David Wang on 8/21/14.
//
//

#ifndef __SquirrelReborn__TitleScene__
#define __SquirrelReborn__TitleScene__

#include <iostream>
#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(TitleScene);
	cocos2d::RepeatForever* MyPathFun(float controlX, float controlY, float w);
};


#endif /* defined(__SquirrelReborn__TitleScene__) */
