#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;

class Block : public GameSprite{
    
private:
    LabelTTF* numberLabel;
    int number;
    LayerColor *blockLayer;
public:
    static Block* create(int number,int row, int cell, Size size);
    void initBlock(int number,int row, int cell, Size size);
    void setNumber(int number);
    int getNumber();
    Color3B getColor(int number);
};

#endif

