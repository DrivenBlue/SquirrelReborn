//
//  WorldLayer.h
//  Squirrel
//
//  Created by september on 8/3/14.
//
//
#ifndef __WORLDLAYER_SCENE_H__
#define __WORLDLAYER_SCENE_H__

#include "cocos2d.h"
#include "EntityFactory.h"
#include "Player.h"
#include "Predator.h"
#include "GameManager.h" 
#include <iostream>

using namespace std;
class Entity;


class WorldLayer : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene(void);
    virtual bool init();

    WorldLayer();
    ~WorldLayer();
    CREATE_FUNC(WorldLayer);
    //virtual ~WorldLayer();
    
    void setPhysicsWorld(PhysicsWorld * psyx);
    void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    
    void update(float dt);
    void setViewPointCenter(cocos2d::Point position);
    Point tileCoordForPosition(Point position);
    void setPlayerPosition(Point position);

private:
    bool onContactBegin(PhysicsContact &contact);
    bool onContactPreSolve(PhysicsContact &contact);
    void onContactSeparate(PhysicsContact &contact);
    
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
	TMXLayer* bgLayer;
    TMXObjectGroup* objects;
    GameManager* instance;
    TMXLayer *_meta;
    
    EntityFactory *ef;
    Player *p1;
    Predator *enemy;
    PhysicsWorld *scenePhysWorld;
    Size dimensions;
};

#endif // __WORLDLAYER_SCENE_H__
