//
//  Predator.h
//  Squirrel
//
//  Created by september on 8/6/14.
//
//

#ifndef ENTITIES__PREDATOR_H__
#define ENTITIES__PREDATOR_H__

#include "Entity.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace cocos2d;

class Predator : public Entity {
public:
    Predator(const std::string& filename);
    
    virtual bool initToScene(Layer *world, EntityMap *blueprint);
	virtual ~Predator(void);
    
    virtual void attack(float dt); //This will encapsulate a strategy for attacking
                           //Whether it be by movement or explicit
    
    virtual void draw(Renderer *R, const Mat4 &transform, bool transformUpdated);
    void onDraw(const Mat4 &transform, bool transformUpdated);

//protected:
//    virtual void update(float dt);
};


#endif /* ENTITIES__PREDATOR_H__ */
