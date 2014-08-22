//
//  Squirrel
//
//  Created by september on 8/3/14.
//  Added notes on some valuable c++ insights
//

#ifndef ENTITIES__ENTITY_H__
#define ENTITIES__ENTITY_H__

#include "cocos2d.h"
#include <iostream>

struct EntityMap {
    EntityMap();
    std::string modelFile;
    int bodyWidthPx;
    int bodyHeightPx;
    float moveSpeed;
    int health;
    cocos2d::Vec2 spawn;
};

class Entity : public cocos2d::Sprite {
public:
    virtual bool initToScene(cocos2d::Layer *world, EntityMap *blueprint) = 0;
    virtual ~Entity(void){};
    
    void setSpawn(const cocos2d::Point& pos);
    void setDestination(const cocos2d::Point& pos);
    void setMoveAngle(int deg);
    void setMoveLock(float seconds);
    void setCollided(Entity * object);
        
    cocos2d::Point& getSpawn(void);
    cocos2d::Point& getDestination(void);
    float getMoveSpeed(void) const;
    int getMoveAngle(void) const;
    float getMoveLock(void) const;
    Entity* getCollided(void);
   
    
    
protected:
    cocos2d::Layer * world;
    cocos2d::Point spawn;
    cocos2d::Point destination;
    
    
    float moveSpeed;
    int moveAngle;
    float moveLock;
    Entity * collided;
    int health;

    
};


/* ~(1) private, protected, public access specifiers
    A public inheritance is when the derived class inherits all
    its parent's methods as is. protected and private bumps the
    visibility of parent down 1 & 2 privileges with the specifier
    as the base level
 
    So if [private cocos2d::Node] has <protected doSomething()>, 
    then doSomething is made private [protected cocos2d::Node] 
    has <protected doSomething()>, then doSomething can't go lower 
    so is made protected; but if <private doNothing()> in protected 
    inheritance, then doNothing is still private
*/


/*  ~(2) Virtual Member Functions
    This will act as the constructor (cstor)
    virtual keyword means that the method is polymorphic
    setting the function = 0 means that it's purely virtual and must be defined
    in a derived class. Consequently, this makes this class an abstract class, but
    can have functions that have a definition, too.
    In other words, cannnot instantiate, must be inherited.
 
    Parent Method can be used in a child by doing
    Parent::superMethod();
*/


/* ~(3) Don't use CC_SYNTHESIZE,
    it is has a terrible habit of inlining complex mutators/accessors
    only time it should be used is when you have base types like
    int, float, char, or like the trivial case above.
 
    It's a space vs cost tradeoff. Reason is if the class is used in
    other places, the .o file creates duplicate code. With returns of 
    objects, the duplicate code includes constructors, library calls, etc.
*/


/* ~(4) Difference between function() vs function(void)::
    Comes from C-style of programming where former means
    function can take an unspecified number of arguments
    and the latter means that the function takes no args
*/


/* ~(5) const function const const
    
    const on arg means function can't change pos data
    Ex: void setStartPosition(const cocos2d::Point &pos);
 
    const on function means function can't change member data
    Ex: cocos2d::Point * getStartPosition() const;
  
    The reason for this is self-documenting code
    since some mutators may change the data
    and some accessors may change the state of the object.
    State of the object means its attributes' values during
    the lifetime of the object
*/

#endif
