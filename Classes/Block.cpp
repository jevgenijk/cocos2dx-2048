#include "Block.h"


Block* Block::create (int number,int row, int cell, Size size) {
    Block*sprite = new Block();
    if (sprite && sprite->init()) {
        sprite->initBlock(number,row,cell,size);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void Block::initBlock(int number,int row, int cell, Size size){
    this->number = number;
    int blockSize = (size.height)/4;
    int x = blockSize*row+50;
    int y = blockSize*cell+15;

    blockLayer = LayerColor::create(Color4B(205,193,182,255), blockSize - 25, blockSize - 25);
    blockLayer->setPosition(x, y);
    
    if (number > 0){
        numberLabel = LabelTTF::create(String::createWithFormat("%i", number)->getCString(), "", 100);
    } else {
        numberLabel = LabelTTF::create("", "", 100);
    }
    blockLayer->setColor(getColor(number));

    numberLabel->setPosition(blockLayer->getContentSize().width/2, blockLayer->getContentSize().height/2);
    blockLayer->addChild(numberLabel);
    
    
    this->addChild(blockLayer);

}

void Block::setNumber(int number) {
    this->number = number;

    blockLayer->setColor(getColor(number));
    if (number > 0) {
        numberLabel->setString(String::createWithFormat("%i", number)->getCString());
    } else {
        numberLabel->setString("");
    }
}

Color3B Block::getColor(int number){
    switch(number){
        case 0:
            return Color3B(205,193,182);
        case 2:
            return Color3B(238,228,219);
        case 4:
            return Color3B(236,224,203);
        case 8:
            return Color3B(241, 177, 125);
        case 16:
            return Color3B(243, 149, 106);
        case 32:
            return Color3B(243, 123, 99);
        case 64:
            return Color3B(244, 94, 67);
        case 128:
            return Color3B(236, 205, 119);
        case 256:
            return Color3B(236, 203, 107);
        case 512:
            return Color3B(235, 199, 90);
        case 1024:
            return Color3B(235, 199, 90);
        case 2048:
            return Color3B(235, 199, 90);
    }
}

int Block::getNumber() {
    return number;
}