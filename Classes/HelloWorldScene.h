#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Arrow.h"

USING_NS_CC;


class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    SpriteBatchNode *gameBatchNode;
    Sprite *leftButton;
    Sprite *rightButton;
    Sprite *topButton;
    Sprite *bottomButton;
    Sprite *topbox;
    Sprite *health;
    Vector<Arrow*> arrows;
    int points;
    float spawntime;
    float allowedMistakeCount;
    Label * scoreDisplay;


    void update(float dt);
    void addArrow(float dt);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event);
};

#endif // __HELLOWORLD_SCENE_H__
