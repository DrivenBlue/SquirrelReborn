//
//  LoadingResScene.cpp
//  SquirrelReborn
//
//  Created by David Wang on 8/21/14.
//
//All of the individual resources not in plists will be stored in here. The progress bar is beneficial
//as it prevents lag when loading the screen and uses up less memory when resources are loaded in the
//beginning instead of runtime. We can later replace the progress bar with a company logo or whatever.

#include "LoadingResScene.h"
#include "TitleScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

LoadingResScene::LoadingResScene()
:numberOfLoadedRes(0)
,totalOfLoadedRes(12)
,progressBar(NULL)
{
}

Scene* LoadingResScene::createScene()
{
    Scene *scene = Scene::create();
    LoadingResScene *layer = LoadingResScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool LoadingResScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    progressBar = addProgress();
	loadResources();
    schedule(schedule_selector(LoadingResScene::logic));
    
	return true;
}

void LoadingResScene::transitionScene()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, TitleScene::createScene()));
}

ProgressTimer * LoadingResScene::addProgress()
{
	Size size = Director::getInstance()->getWinSize();
	auto progressBarBg = Sprite::create("load.png");
	progressBarBg->setPosition(Point(size.width / 2,  size.height / 2 ));
	addChild(progressBarBg);
    
	progressBar = ProgressTimer::create(Sprite::create("loadBar.png"));
	progressBar->setType(ProgressTimer::Type::BAR);
	progressBar->setMidpoint(Point(0, 0.5f));
	progressBar->setBarChangeRate(Point(1, 0));
	progressBar->setPercentage(0);
	progressBar->setAnchorPoint(Point(0.5f, 0.5f));
    progressBar->setPosition(Point(progressBarBg->getContentSize().width / 2,  progressBarBg->getContentSize().height /6 ));
	progressBarBg->addChild(progressBar);
    return progressBar;
}

void LoadingResScene::loadResources()
{
//    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/music.mp3").c_str() );
//    numberOfLoadedRes++;
//    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.wav" ).c_str());
//    numberOfLoadedRes++;
 
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
    numberOfLoadedRes++;
    
    Director::getInstance()->getTextureCache()->addImageAsync("HelloWorld.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("CloseNormal.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("CloseSelected.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_1.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_2.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_3.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("start_1.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("start_2.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("btn_back.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("btn_back_press.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("BC_War.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("pixuirrel.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
}

void LoadingResScene::loadingCallBack(cocos2d::Texture2D *texture)
{
    numberOfLoadedRes++;
}

void LoadingResScene::logic(float dt)
{
    float percent = (float)numberOfLoadedRes / (float)totalOfLoadedRes * 100;
    
    progressBar->setPercentage(percent);
    
    if (numberOfLoadedRes == totalOfLoadedRes)
    {
        transitionScene();
        //SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/music.mp3").c_str(), true);
        //SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
    }
}