//
//  LevelInfoScene.h
//  SquirrelReborn
//
//  Created by David Wang on 8/22/14.
//
//

#ifndef __SquirrelReborn__LevelInfoScene__
#define __SquirrelReborn__LevelInfoScene__

#include <iostream>
#include "cocos2d.h"
#include "LoadLevelInfo.h"
USING_NS_CC;

class LevelInfoScene : public Layer
{
public:
    
	LevelInfoScene();
    CREATE_FUNC(LevelInfoScene);
    static Scene * createScene();
	bool init();
    void addBackGround();
    
    void initLoadInfo(int bigLevel,int smallLevel);
	void menuBackCallback(Ref* pSender);
	void menuStartCallback(Ref* pSender);
    
private:
	LoadLevelInfo* info;
	std::string fileName;
};

#endif /* defined(__SquirrelReborn__LevelInfoScene__) */
