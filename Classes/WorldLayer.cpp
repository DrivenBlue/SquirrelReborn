//
//  WorldLayer.cpp
//  Squirrel
//
//  Created by september on 8/3/14.
//
//

#include "WorldLayer.h"
#include "GameManager.h"
//#include "SuccessfulScene.h"
//#include "FailedScene.h"
#include "LevelScene.h"
#include "cocos-ext.h"

WorldLayer::WorldLayer()
:spriteSheet(NULL)
,map(NULL)
,objects(NULL)

{}


cocos2d::Scene* WorldLayer::createScene(void) {
	auto scene = cocos2d::Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
	auto layer = WorldLayer::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	scene->addChild(layer);
    //can change this to whatever size
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(visibleSize.width / 2 , visibleSize.height / 2);
    edgeNode->setPhysicsBody(body);
    
    scene->addChild(edgeNode);
	return scene;
}

bool WorldLayer::init() {
	if( !Layer::init() ) {
		return false;
	}
    dimensions = Director::getInstance()->getVisibleSize();
    Size winSize = Director::getInstance()->getWinSize();
    instance = GameManager::getInstance();
    //_meta = map->getLayer("Meta");
    //_meta->setVisible(false);

    auto gameBg = Sprite::create(instance->getCurBgName());
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);
    
    map = TMXTiledMap::create(instance->getCurMapName());
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
    
    this->addChild(map, -10);

    
    ef = EntityFactory::Instance();
    EntityMap *playerInit = new EntityMap();
    playerInit->modelFile = "pixuirrel.png";
    playerInit->health = 100.f;
    playerInit->moveSpeed = 7.f;
    playerInit->spawn = Vec2(60.f, 60.f);
    p1 = (Player *)ef->createToLayer("Player", this, playerInit);
    this->setViewPointCenter(p1->getPosition());

    playerInit->modelFile = "BC_War.png";
    playerInit->health = 0.f;
    playerInit->moveSpeed = 5.f;
    playerInit->spawn = Vec2(500.f, 400.f);
    enemy = (Predator *)ef->createToLayer("Predator", this, playerInit);
    delete playerInit;
    
    auto controls = EventListenerTouchAllAtOnce::create();
    controls->onTouchesBegan = CC_CALLBACK_2(WorldLayer::onTouchesBegan, this);
    controls->onTouchesMoved = CC_CALLBACK_2(WorldLayer::onTouchesMoved, this);
    controls->onTouchesEnded = CC_CALLBACK_2(WorldLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(controls, this);
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(WorldLayer::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_1(WorldLayer::onContactPreSolve, this);
    contactListener->onContactSeperate = CC_CALLBACK_1(WorldLayer::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->schedule(schedule_selector(WorldLayer::update));
	
    return true;
}

WorldLayer::~WorldLayer() {
}

void WorldLayer::setPlayerPosition(Point position) {
	Point tileCoord = this->tileCoordForPosition(position);
	int tileFUCKEDUP = _meta->getTileGIDAt(tileCoord);
	if(tileFUCKEDUP) {
		Value shit = map->getPropertiesForGID(tileFUCKEDUP);
		ValueMap doubleShit = shit.asValueMap();
		auto temp = doubleShit.find("Collidable");
		CCLOG(( temp->second.asBool() ? "Yes" : "No" ));
	}
	
	p1->setPosition(position);
}

void WorldLayer::setViewPointCenter(Point position) {
	Size winSize = Director::getInstance()->getWinSize();
    
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (map->getMapSize().width * this->map->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (map->getMapSize().height *map->getTileSize().height) - winSize.height/2);
    Point actualPosition = Point(x, y);
    
    Point centerOfView = Point(winSize.width/2, winSize.height/2);
    Point viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

Point WorldLayer::tileCoordForPosition(Point position)
{
    int x = position.x / map->getTileSize().width;
    int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
    return Point(x, y);
}


void WorldLayer::setPhysicsWorld(PhysicsWorld * psyx) {
    scenePhysWorld = psyx;
}

void WorldLayer::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    for(cocos2d::Touch *touch : touches) {
        if(touches.size() == 1) {
            cocos2d::Point location = touch->getLocation();
            p1->setDestination(location);
        } else {
            CCLOG("ZOOOOOMM initiated");
        }
    }
}

void WorldLayer::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    
    for(cocos2d::Touch *touch : touches) {
        if(touches.size() == 1) {
            cocos2d::Point location = touch->getLocation();
            p1->setDestination(location);
        } else {
            CCLOG("ZOOOOOMM scrollin");
        }
    }
}

void WorldLayer::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    if(touches.size() == 1) {
        p1->setDestination(cocos2d::Point(0.0,0.0));
    } else {
        CCLOG("ZOOOOOOMM ended");
    }
    
//    Point touchLocation = touches.getLocationInView();
//    Point touchLocation = Director::getInstance()->convertToGL(touchLocation);
//    touchLocation = this->convertToNodeSpace(touchLocation);
//    
//    Point playerPos = p1->getPosition();
//    Point diff = touchLocation - playerPos;
//    
//    if ( abs(diff.x) > abs(diff.y) ) {
//        if (diff.x > 0) {
//            playerPos.x += map->getTileSize().width;
//        } else {
//            playerPos.x -= map->getTileSize().width;
//        }
//    } else {
//        if (diff.y > 0) {
//            playerPos.y += map->getTileSize().height;
//        } else {
//            playerPos.y -= map->getTileSize().height;
//        }
//    }
//        this->setPlayerPosition(playerPos);
    
    
}

bool WorldLayer::onContactBegin(PhysicsContact& contact) {
    PhysicsBody *aBody = contact.getShapeA()->getBody();
    PhysicsBody *bBody =contact.getShapeB()->getBody();
    Player *player = NULL;
    Entity *object = NULL;
    if(aBody->getNode()->getTag() == 1) {
        player = (Player *)aBody->getNode();
        object = (Entity *)bBody->getNode();
        player->setCollided(object);
        return true;
    } else if(bBody->getNode()->getTag() == 1) {
        player = (Player *)bBody->getNode();
        object = (Entity *)aBody->getNode();
        player->setCollided(object);
        return true;
    }

    return false;
}

bool WorldLayer::onContactPreSolve(cocos2d::PhysicsContact &contact) {
    //this is where the perfect pixel check would happen

    return true;
}

void WorldLayer::onContactSeparate(cocos2d::PhysicsContact &contact) {
    PhysicsBody *aBody = contact.getShapeA()->getBody();
    Player *player = (Player *)aBody->getNode();
    p1->setCollided(NULL);
    std::cout << "contact separate\n" << std::endl;
}

void WorldLayer::update(float dt) {
    
    
    //dt is the incremental timestep that occurs at approx. 1/60th of a second
    if(!p1->getDestination().equals(Vec2::ZERO)) {
        cocos2d::Point current = p1->getPosition();
        cocos2d::Point next = p1->getDestination();
        float dx = p1->getMoveSpeed();
        //so we only want angle towards end destination
        float angle = atan2(next.x - current.x, next.y - current.y);
        //Are we there yet?
        if(!current.fuzzyEquals(next, 1.f)) {
            float travel = 0.f;
            if((travel = current.getDistance(next)) < dx) {
                dx = travel;
            }
            float xstep = dx * sin(angle);
            float ystep = dx * cos(angle);
            Size playerDim = p1->getContentSize();
            
            //Account for continuous collision detection with collided body and clip movement
            Entity *obj = p1->getCollided();
            if(obj != NULL) {
                obj->setMoveLock(0.f);
                
            }
            
            current.x += xstep;
            current.y += ystep;
            
            //Account for world boundary and clip movement
            if(current.x < playerDim.width / 2) {
                current.x = playerDim.width / 2;
            } else if(current.x > (dimensions.width - playerDim.width / 2)) {
                current.x = dimensions.width - playerDim.width / 2;
            }
            
            if(current.y < playerDim.height /2) {
                current.y = playerDim.height /2;
            } else if(current.y > (dimensions.height - playerDim.height / 2)) {
                current.y = dimensions.height - playerDim.height / 2;
            }
        }
        p1->setPosition(current);
        setViewPointCenter(current);
    }
}
