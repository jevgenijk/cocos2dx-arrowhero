#include "Arrow.h"


Arrow* Arrow::create (int tag) {
    auto sprite = new Arrow();
    
    std::string texture = "";
    if(tag == 0){
        texture = "up.png";
    }else if(tag == 1){
        texture = "down.png";
    }else if(tag == 2){
        texture = "left.png";
    }else if(tag == 3){
        texture = "right.png";
    }
    
    if (sprite && sprite->initWithSpriteFrameName(texture)) {
        sprite->autorelease();
        sprite->setTag(tag);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Arrow::update (float dt) {
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float circle_length = this->getPosition().distance( circleMidPoint )   * M_PI;
    int iterations = floor(circle_length / 300);
    
    Point position = this->getPosition();
    
    float angle = 2 * M_PI / iterations * dt;
    Point rotatedPoint = position.rotateByAngle(circleMidPoint, angle);
    position.x = rotatedPoint.x;
    position.y = rotatedPoint.y;
    this->setPosition(position);
    
}
