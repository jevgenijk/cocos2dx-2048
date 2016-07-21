#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init(){
    if (!LayerColor::initWithColor(Color4B(251,248,241,255))){
        return false;//pelekais 180,170,160,255
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    bottomLayer = LayerColor::create(cocos2d::Color4B(180,170,160,255));
    bottomLayer->setContentSize(Size(visibleSize.width, visibleSize.height/2));
    bottomLayer->setPosition(Vec2(0, 100));
    addChild(bottomLayer);
    
    initializeBlocks(visibleSize);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt)
{
    if (true == isTouchDown)
    {
        if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05)
        {
            CCLOG("SWIPED LEFT");
            goLeft();
            addBlock();
            isTouchDown = false;
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - visibleSize.width * 0.05)
        {
            CCLOG("SWIPED RIGHT");
            goRight();
            addBlock();
            isTouchDown = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
        {
            CCLOG("SWIPED DOWN");
            goDown();
            addBlock();
            isTouchDown = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            goUp();
            addBlock();
            isTouchDown = false;
        }
    }
}

void GameScene::goUp(){
    for (int cell = 0; cell < 4; cell++) {
        for (int row = 3; row >= 0; row--) {
            for (int innerRow = row - 1; innerRow >= 0; innerRow--) {
                if (blocks[cell][innerRow]->getNumber() > 0) {
                    if (blocks[cell][row]->getNumber() <= 0) {
                        blocks[cell][row]->setNumber(blocks[cell][innerRow]->getNumber());
                        blocks[cell][innerRow]->setNumber(0);
                        row++;
                    }else if(blocks[cell][row]->getNumber() == blocks[cell][innerRow]->getNumber()){
                        blocks[cell][row]->setNumber(blocks[cell][row]->getNumber()*2);
                        blocks[cell][innerRow]->setNumber(0);
                    }
                    break;
                }
            }
            
        }
    }
}

void GameScene::goDown(){
    for (int cell = 0; cell < 4; cell++) {
        for (int row = 0; row < 4; row++) {
            for (int innerRow = row + 1; innerRow < 4; innerRow++) {
                if (blocks[cell][innerRow]->getNumber() > 0) { // if top block is bigger
                    if (blocks[cell][row]->getNumber() == 0) { // than empty block then push down
                        blocks[cell][row]->setNumber(blocks[cell][innerRow]->getNumber());
                        blocks[cell][innerRow]->setNumber(0);
                        row--;
                    }else if(blocks[cell][row]->getNumber() == blocks[cell][innerRow]->getNumber()){ // if top and bottom block are equal then sum up and push down.
                        blocks[cell][row]->setNumber(blocks[cell][row]->getNumber()*2);
                        blocks[cell][innerRow]->setNumber(0);
                    }
                    break; // Sum up only once and not all numbers at the same time. Can be removed to make game much easier
                }
            }
            
        }
    }
}

void GameScene::goLeft(){
    for (int cell = 0; cell < 4; cell++) {
        for (int row = 0; row < 4; row++) {
            for (int innerCell = row + 1; innerCell < 4; innerCell++) {
                if (blocks[innerCell][cell]->getNumber() > 0) {
                    if (blocks[row][cell]->getNumber() == 0) {
                        blocks[row][cell]->setNumber(blocks[innerCell][cell]->getNumber());
                        blocks[innerCell][cell]->setNumber(0);
                        row--;
                    }else if(blocks[row][cell]->getNumber() == blocks[innerCell][cell]->getNumber()){
                        blocks[row][cell]->setNumber(blocks[row][cell]->getNumber()*2);
                        blocks[innerCell][cell]->setNumber(0);
                    }
                    break;
                }
            }
        }
    }
}

void GameScene::goRight(){
    for (int cell = 0; cell < 4; cell++) {
        for (int row = 3; row >= 0; row--) {
            for (int innerCell = row - 1; innerCell >= 0; innerCell--) {
                if (blocks[innerCell][cell]->getNumber() > 0) {
                    if (blocks[row][cell]->getNumber() == 0) {
                        blocks[row][cell]->setNumber(blocks[innerCell][cell]->getNumber());
                        blocks[innerCell][cell]->setNumber(0);
                        row++;
                    }else if(blocks[row][cell]->getNumber() == blocks[innerCell][cell]->getNumber()){
                        blocks[row][cell]->setNumber(blocks[row][cell]->getNumber()*2);
                        blocks[innerCell][cell]->setNumber(0);
                    }
                    break;
                }
            }
        }
    }
}

void GameScene::initializeBlocks(Size visibleSize){
    for(int row=0; row<4; row++){
        for(int cell=0; cell<4; cell++){
            Block* block = Block::create(0,row, cell,bottomLayer->getContentSize());
            blocks[row][cell] = block;
            bottomLayer->addChild(block);
        }
    }
    
    addBlock();
    addBlock();
}

void GameScene::addBlock(){
    int row, cell;
    do {
        row = CCRANDOM_0_1()*4;
        cell = CCRANDOM_0_1()*4;
    }
    while (blocks[row][cell]->getNumber() > 0);
    
    blocks[row][cell]->setNumber(CCRANDOM_0_1()*10 < 1 ? 2: 4);
    
    log("(%d,%d): %d", row, cell, blocks[row][cell]->getNumber());
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch,
                              cocos2d::Event * event)
{
    
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    
    return true;
}
void GameScene::onTouchMoved(cocos2d::Touch *touch,cocos2d::Event * event)
{
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
}
void GameScene::onTouchEnded(cocos2d::Touch *touch,
                              cocos2d::Event * event)
{
    isTouchDown = false;

}
void GameScene::onTouchCancelled(cocos2d::Touch *touch,
                                  cocos2d::Event * event)
{
    onTouchEnded(touch, event);
}
