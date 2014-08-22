//
//  LoadingResScene.h
//  SquirrelReborn
//
//  Created by David Wang on 8/21/14.
//
//

#ifndef SquirrelReborn_LoadingResScene_h
#define SquirrelReborn_LoadingResScene_h

#include <iostream>
#include "cocos2d.h"
#include "LoadLevelInfo.h"
USING_NS_CC;

class LoadingResScene : public Layer
{
public:
    
	LoadingResScene();
    CREATE_FUNC(LoadingResScene);
    static Scene * createScene();
	virtual bool init();
    
    ProgressTimer *addProgress();
    void loadResources();
	void transitionScene();
	void loadingCallBack(cocos2d::Texture2D *texture);
    void logic(float dt);
    
private:
    
	ProgressTimer* progressBar;
	int numberOfLoadedRes;
	int totalOfLoadedRes;
};
#endif /* defined(__LoadingResScene__) */


