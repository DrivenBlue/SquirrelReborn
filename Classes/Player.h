//
//  Player.h
//  Squirrel
//
//  Created by september on 8/5/14.
//
//

#ifndef ENTITIES__PLAYER_H__
#define ENTITIES__PLAYER_H__ 

#include "cocos2d.h"
#include "Entity.h"
#include <iostream>

using namespace cocos2d;

class Player : public Entity {

public:
	Player(const std::string &filename);
    
    virtual bool initToScene(Layer *world, EntityMap *blueprint);
	virtual ~Player(void);

    virtual void draw(Renderer *R, const Mat4 &transform, bool transformUpdated);
    void onDraw(const Mat4 &transform, bool transformUpdated);
};



#endif
