#ifndef __ARROW_H__
#define __ARROW_H__

#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;

class Arrow : public GameSprite{
    
private:
    CC_SYNTHESIZE(Point, circleMidPoint, CircleMidPoint);
public:
    static Arrow* create(int tag);
    void update (float dt);
};

#endif // __ROCKET_H__

