//
//  GameManager.cpp
//  SquirrelReborn
//
//  Created by David Wang on 8/22/14.
//
//This helps determine what the current and next levels are going to be and look like
//getInstance also helps to grab plist items

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




