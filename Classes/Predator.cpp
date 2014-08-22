//
//  Predator.cpp
//  Squirrel
//
//  Created by september on 8/6/14.
//
//

#include "Predator.h"
#include "EntityFactory.h"

Predator::Predator(const std::string &filename) {
    srand(time(NULL));
    this->initWithFile(filename);
    collided = NULL;
    moveLock = 0.f;
}

bool Predator::initToScene(cocos2d::Layer *world, EntityMap * blueprint) {
   	if(!Node::init()) {
        std::cout << "Must've been held up by the FCC b/c of his flying horse...\n";
        return false;
	}

    spawn = blueprint->spawn;
    this->setPosition(spawn);
    moveSpeed = blueprint->moveSpeed;
    health = blueprint->health;
    
    PhysicsBody * pbody = NULL;
    if(blueprint->bodyWidthPx == 0 || blueprint->bodyHeightPx) {
        pbody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial( 2000.f, 0.f, 0.f ));
    } else {
        Size boundingBox = Size(blueprint->bodyWidthPx, blueprint->bodyHeightPx);
        pbody = PhysicsBody::createBox(boundingBox, PhysicsMaterial( 0.f, 0.f, 0.f ));
    }
    pbody->setCollisionBitmask(1);
    pbody->setContactTestBitmask(true);
    pbody->setRotationEnable(false);
    this->setPhysicsBody(pbody);
    
    schedule(schedule_selector(Predator::attack), 1/30);
    
    this->world = world;

	world->addChild(this, 2);
    
    return true;
}

Predator::~Predator(void) {
    std::cout << "calling pred destruct\n";
}

void Predator::attack(float dt) {
    
    if(moveLock > 0.f) {
        float x = moveSpeed * sin(moveAngle) + getPosition().x;
        float y = moveSpeed * cos(moveAngle) + getPosition().y;
        int width = getContentSize().width;
        int height = getContentSize().height;
        Vec2 sceneDim = Director::getInstance()->getVisibleSize();
        
        if(x < width >> 1) {
            x = width >> 1;
        } else if(x > (int)(sceneDim.x - width) >> 1) {
            x = (int)(sceneDim.x - width) >> 1;
        }
        
        if(y < height >> 1) {
            y = height >> 1;
        } else if(y > (int)(sceneDim.y - height) >> 1) {
            y = (int)(sceneDim.y - height) >> 1;
        }
        setPosition(Vec2(x,y));
        moveLock = moveLock - dt;
    } else {
        moveLock = 0.f;
        int doesMove = rand() % 9;
        if(doesMove != 0) {
            moveAngle = 45 * doesMove;
            moveLock = 1.f;
        }
    }
}

void Predator::draw(cocos2d::Renderer *R, const Mat4 &transform, bool transformUpdated) {
    CustomCommand *command = new CustomCommand();
    command->init(_globalZOrder);
    command->func = CC_CALLBACK_0(Predator::onDraw, this, transform, transformUpdated);
    
    R->addCommand(command);
    Node::draw(R, transform ,transformUpdated);
}

void Predator::onDraw(const Mat4 &transform, bool transformUpdated) {
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
}

REGISTER_CLASS("Predator", Predator);