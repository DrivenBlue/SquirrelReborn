//
//  EntityFactory.cpp
//
//  Created by september on 8/7/14.
//
//

#include "EntityFactory.h"


//....FACTORY PUBLIC METHODS......................................................

EntityFactory * EntityFactory::Instance() {
    static EntityFactory ef;
    return &ef;
}

void EntityFactory::RegisterMaker(const char *ID, Entity * makerFunc(const std::string &)) {
    registry[ID] = makerFunc;
}

Entity * EntityFactory::createToLayer(const char *ID, cocos2d::Layer *world, EntityMap *blueprint) {
    Entity *holder = NULL;
    std::map<const char *, std::function<Entity * (const std::string &)>>::iterator entry;
    entry = registry.find(ID);
    if(entry != registry.end()) {
        holder = entry->second(blueprint->modelFile);
        if(holder && holder->initToScene(world, blueprint)) {
            holder->autorelease();
            return holder;
        } else {
            CC_SAFE_DELETE(holder);
        }
    }
    return NULL;
}

//....HELPER METHODS..............................................................

Registrar::Registrar(const char* ID, Entity * makerFunc(const std::string &)) {
    EntityFactory::Instance()->RegisterMaker(ID, makerFunc);
}
