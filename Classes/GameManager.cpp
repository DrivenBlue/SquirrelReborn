//
//  GameManager.cpp
//  SquirrelReborn
//
//  Created by David Wang on 8/22/14.
//
//

#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
        instance = new GameManager();
	return instance;
}

void GameManager::clear()
{
	
}




