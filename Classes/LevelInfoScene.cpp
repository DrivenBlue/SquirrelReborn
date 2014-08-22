//
//  LevelInfoScene.cpp
//  SquirrelReborn
//
//  Created by David Wang on 8/22/14.
//
//

#include "LevelInfoScene.h"
#include "WorldLayer.h"
#include "LevelScene.h"
#include "GameManager.h"
//#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


LevelInfoScene::LevelInfoScene()
:info(NULL)
,fileName("")
{
}

Scene* LevelInfoScene::createScene()
{
    Scene *scene = Scene::create();
    LevelInfoScene *layer = LevelInfoScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelInfoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    auto instance = GameManager::getInstance();
    instance->clear();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
	fileName =  UserDefault::getInstance()->getStringForKey("nextLevelFile");
	if( fileName ==""){
		fileName = "levelInfo_0.plist";
	}
	
	addBackGround();
	
	return true;
}

void LevelInfoScene::addBackGround()
{
	Size size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(sprite, -1);
    
	auto spritePanel = Sprite::create("HelloWorld.png");
    spritePanel->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(spritePanel, -1);
    
    Sprite *start = CCSprite::createWithSpriteFrameName("btnStart.png");
    MenuItemSprite *startItem = MenuItemSprite::create(start, start, CC_CALLBACK_1(LevelInfoScene::menuStartCallback, this));
    Sprite *back= CCSprite::createWithSpriteFrameName("btnBack.png");
    MenuItemSprite *backItem = MenuItemSprite::create(back, back, CC_CALLBACK_1(LevelInfoScene::menuBackCallback, this));
    
    auto menu = Menu::create(startItem, backItem, NULL);
	menu->alignItemsHorizontally();
    
    menu->setPosition(Point(size.width / 2,size.height / 6));
    
    
    this->addChild(menu);
}

//Back button in transition page
void LevelInfoScene::menuBackCallback(Ref* pSender)
{
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, LevelScene::create()));
    
}

void LevelInfoScene::menuStartCallback(Ref* pSender)
{
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	info = LoadLevelInfo::createLoadLevelInfo(fileName.c_str());
	info->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, WorldLayer::createScene()));
    
}
