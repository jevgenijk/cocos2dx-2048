#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
USING_NS_CC;

class GameScene : public LayerColor
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
private:
    Size visibleSize;
    LayerColor* bottomLayer;
    Block* blocks[4][4]; // whole game grid
    
    //for swipe detection https://github.com/SonarSystems/Cocos2d-x-Tutorial---Swipe-Gesture/blob/master/HelloWorldScene.h
    bool isTouchDown;
    float initialTouchPos[2];
    float currentTouchPos[2];
    
    
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    void addBlock(); // adding new number to the field ( 2 or 4 )
    void initializeBlocks(Size size); // adding empty blocks to the screen
    bool onTouchBegan(Touch *touch, Event * event);
    void onTouchMoved(Touch *touch, Event * event);
    void onTouchEnded(Touch *touch, Event * event);
    void onTouchCancelled(Touch *touch, Event * event);
    void update(float dt);
};

#endif 
