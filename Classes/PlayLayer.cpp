//
//  PlayLayer.cpp
//  SquirrelReborn
//
//  Created by David Wang on 8/22/14.
//
//


#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "PlayLayer.h"
#include "GameManager.h"
//#include "SuccessfulScene.h"
//#include "FailedScene.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
using namespace CocosDenshion;

PlayLayer::PlayLayer()
:isTouchEnable(false)
,spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
//,isSuccessful(false)
{}


PlayLayer::~PlayLayer()
{
    /*if (towerMatrix) {
     free(towerMatrix);
     }
     */
	pointsVector.clear();
}

Scene *PlayLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    return scene;
}

bool PlayLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    instance = GameManager::getInstance();
    
	auto gameBg = Sprite::create(instance->getCurBgName());
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);
    
    map = TMXTiledMap::create(instance->getCurMapName());
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
    
    this->addChild(map, -10);
    
    initToolLayer();
    
    offX = ( map->getContentSize().width - winSize.width )/ 2;
    initPointsVector(offX);
    //schedule(schedule_selector(PlayLayer::logic), 2.0f);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    
    /*
     int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
     towerMatrix = (TowerBase **)malloc(arraySize);
     memset((void*)towerMatrix, 0, arraySize);
     
     for (int row = 0; row < MAP_HEIGHT; row++) {
     for (int col = 0; col < MAP_WIDTH; col++) {
     towerMatrix[row * MAP_WIDTH + col] = NULL;
     }
     } */
    return true;
}

void PlayLayer::initPointsVector(float offX)
{
    Node *runOfPoint = NULL;
	int count = 0;
	ValueMap point;
	point = objects->getObject(std::to_string(count));
	while (point.begin()!= point.end())
	{
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();
		runOfPoint = Node::create();
		runOfPoint->setPosition(Point(x - offX, y ));
		this->pointsVector.pushBack(runOfPoint);
		count++;
		point = objects->getObject( std::to_string(count));
	}
	runOfPoint = NULL;
}

void PlayLayer::initToolLayer()
{
	auto size = Director::getInstance()->getWinSize();
	toolLayer = Layer::create();
	addChild(toolLayer);
    
	auto spritetool = Sprite::createWithSpriteFrameName("toolbg.png");
	spritetool->setAnchorPoint(Point(0.5f, 1));
	spritetool->setPosition (Point(size.width / 2, size.height));
	toolLayer->addChild(spritetool);
   
    // back
	Sprite *backItem1 = CCSprite::createWithSpriteFrameName("playbutton1.png");
	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("playbutton2.png");
	MenuItemSprite *pPauseItem = MenuItemSprite::create(backItem1, backItem2, CC_CALLBACK_1(PlayLayer::menuBackCallback, this));
	pPauseItem->setPosition(Point(spritetool->getContentSize().width - backItem1->getContentSize().width/2, spritetool->getContentSize().height / 2));
	pPauseItem->setAnchorPoint(Point(0, 0.4f));
	Menu* pMenu = Menu::create(pPauseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	spritetool->addChild(pMenu);
}

void PlayLayer::menuBackCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    instance->clear();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelScene::create()));
}
Point PlayLayer::convertTotileCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y =map->getMapSize().height- position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}
Point PlayLayer::convertToMatrixCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y = position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}

void PlayLayer::update(float dt)
{
    /*
     if(isSuccessful)
     {
     isSuccessful = false;
     auto star = 0;
     auto playHp = this->getPlayHpPercentage();
     
     if( playHp > 0 && playHp <= 30){ star = 1;}
     else if(playHp > 30 && playHp <= 60 ){ star = 2;}
     else if(playHp > 60 && playHp <= 100 ){ star = 3;}
     */
    /*
     auto star = 0;
     if( star > UserDefault::getInstance()->getIntegerForKey(instance->getCurrLevelFile().c_str()))
     {
     UserDefault::getInstance()->setIntegerForKey(instance->getCurrLevelFile().c_str(), star);
     auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum") + 1;
     UserDefault::getInstance()->setIntegerForKey("levelNum", levelNum);
     }
     */
    auto nextlevel = instance->getNextLevelFile();
    UserDefault::getInstance()->setStringForKey("nextLevelFile", nextlevel);
    
    instance->clear();
    //Director::getInstance()->replaceScene(TransitionFade::create(0.1f, SuccessfulScene::create()));
}
