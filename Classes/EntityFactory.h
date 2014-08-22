//
//  EntityFactory.h
//
//  Created by september on 8/7/14.
//
//

#ifndef ENTITIES__ENTITYFACTORY_H__
#define ENTITIES__ENTITYFACTORY_H__

#include "cocos2d.h"
#include "Entity.h"
#include <iostream>
#include <functional>
#include <map>
#include <string>

class Registrar {
public:
    Registrar(const char* ID, Entity * makerFunc(const std::string &));
};

#define REGISTER_CLASS(NAME, TYPE) \
    static Registrar registrar(NAME, [](const std::string& filename) \
        -> Entity * { return new TYPE(filename); });

class EntityFactory {
public:
    static EntityFactory * Instance();
    void RegisterMaker(const char *ID, Entity * makerFunc(const std::string &));
    Entity * createToLayer(const char *ID, cocos2d::Layer* world, EntityMap *blueprint);
    
private:
    EntityFactory(){ };
    std::map<const char *, std::function<Entity * (const std::string &)>> registry;
};

#endif /* end ENTITIES_ENTITYFACTORY_H */
