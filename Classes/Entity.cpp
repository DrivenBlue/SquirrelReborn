//
//  Entity.cpp
//  Squirrel
//
//  Created by september on 8/7/14.
//
//

#include "Entity.h"

EntityMap::EntityMap() :
    modelFile(""),  bodyWidthPx(0), bodyHeightPx(0),
    moveSpeed(0.f), health(0.f),
    spawn(cocos2d::Vec2::ZERO)
{}


void Entity::setSpawn(const cocos2d::Point& pos) {
    spawn = pos;
}

void Entity::setDestination(const cocos2d::Point &pos) {
    destination = pos;
}

void Entity::setMoveAngle(int deg) {
    moveAngle = deg;
}

void Entity::setMoveLock(float seconds) {
    moveLock = seconds;
}

void Entity::setCollided(Entity * object) {
    collided = object;
}

cocos2d::Point& Entity::getSpawn(void) {
    return spawn;
}

cocos2d::Point& Entity::getDestination(void) {
    return destination;
}

float Entity::getMoveSpeed(void) const {
    return moveSpeed;
}

int Entity::getMoveAngle(void) const {
    return moveAngle;
}

float Entity::getMoveLock(void) const {
    return moveLock;
}

Entity * Entity::getCollided(void) {
    return collided;
}