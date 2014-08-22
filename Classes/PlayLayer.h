//
//  PlayLayer.h
//  SquirrelReborn
//
//  Created by David Wang on 8/22/14.
//
//

#ifndef __SquirrelReborn__PlayLayer__
#define __SquirrelReborn__PlayLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;
class PlayLayer : public Layer
{
public:
    PlayLayer();
    ~PlayLayer();
    
    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(PlayLayer);
    
    virtual void update(float dt) override;
   
	void initLabelText();
private:
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
	TMXLayer* bgLayer;
    TMXObjectGroup* objects;
    Vector<Node*> pointsVector;
    
	GameManager* instance;
    float offX;
    
	
	Layer* toolLayer;
    Sprite* _player;
	void initToolLayer();
	//bool isSuccessful;
    
    bool isTouchEnable;
    Point convertTotileCoord(Point position);
	Point convertToMatrixCoord(Point position);
    void menuBackCallback(Ref* pSender);
    
	Point towerPos;
    void initPointsVector(float offX);
};


#endif /* defined(__SquirrelReborn__PlayLayer__) */
