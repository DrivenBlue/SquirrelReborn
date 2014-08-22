//
//  Player.cpp
//  Squirrel
//
//  Created by september on 8/5/14.
//
//

#include "Player.h"
#include "EntityFactory.h"

Player::Player(const std::string &filename){
    this->initWithFile(filename);
    collided = NULL;
    moveLock = 0.f;
}

bool Player::initToScene(Layer *world, EntityMap *blueprint) {
	if(!Node::init()) {
        std::cout << "init failed\n";
        return false;
	}
    this->setTag(1);
    spawn = blueprint->spawn;
    this->setPosition(blueprint->spawn);
    health = blueprint->health;
    moveSpeed = blueprint->moveSpeed;
    
    PhysicsBody * pbody = NULL;
    if(blueprint->bodyHeightPx == 0 || blueprint->bodyWidthPx == 0) {
        pbody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial( 10.f, 0.f, 0.f ));
    } else {
        Size boundingBox = Size(blueprint->bodyWidthPx, blueprint->bodyHeightPx);
        pbody = PhysicsBody::createBox(boundingBox, PhysicsMaterial( 10.f, 0.f, 0.f ));
    }

    pbody->setLinearDamping(1.f);
    pbody->setRotationEnable(false);
    pbody->setCollisionBitmask(1);
    pbody->setContactTestBitmask(true);

    this->setPhysicsBody(pbody);
    this->world = world;
    scheduleUpdate();
	world->addChild(this, 2);
    
    return true;
}

Player::~Player(void) {
    std::cout << "Player Destructor Called\n";
}

void Player::draw(cocos2d::Renderer *R, const Mat4 &transform, bool transformUpdated) {
    CustomCommand *command = new CustomCommand();
    command->init(_globalZOrder);
    command->func = CC_CALLBACK_0(Player::onDraw, this, transform, transformUpdated);
    
    R->addCommand(command);
    Node::draw(R, transform ,transformUpdated);
}

void Player::onDraw(const Mat4 &transform, bool transformUpdated) {
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    //Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

REGISTER_CLASS("Player", Player);