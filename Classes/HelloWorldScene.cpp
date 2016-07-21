#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(ccc4(242, 234, 234, 255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    points = 0;
    allowedMistakeCount = 10;
    spawntime = 0.8;
    arrows = Vector<Arrow*>();

    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("textures.plist");
    gameBatchNode = SpriteBatchNode::create("textures.png", 10);
    this->addChild(gameBatchNode);
    
    
    topbox = GameSprite::createWithFrameName("topbox.png");
    topbox->setPosition(Vec2(visibleSize.width/2,visibleSize.height/1.3));
    gameBatchNode->addChild(topbox);
    
    
    leftButton = GameSprite::createWithFrameName("left.png");
    leftButton->setPosition(Vec2(visibleSize.width/2-200,100));
    gameBatchNode->addChild(leftButton);
    
    topButton = GameSprite::createWithFrameName("up.png");
    topButton->setPosition(Vec2(visibleSize.width/2,250));
    gameBatchNode->addChild(topButton);
    
    bottomButton = GameSprite::createWithFrameName("down.png");
    bottomButton->setPosition(Vec2(visibleSize.width/2,100));
    gameBatchNode->addChild(bottomButton);
    
    rightButton = GameSprite::createWithFrameName("right.png");
    rightButton->setPosition(Vec2(visibleSize.width/2+200,100));
    gameBatchNode->addChild(rightButton);
    
    health = GameSprite::createWithFrameName("health.png");
    health->setPosition(Vec2(visibleSize.width/2,health->getContentSize().height/2));
    health->setScale(1,1);
    gameBatchNode->addChild(health);

    
    auto scoreLabel = Label::createWithTTF("Score: ","fonts/Marker Felt.ttf",32);
    scoreLabel->setPosition(Point(visibleSize.width/2,visibleSize.height/1.3+150));
    scoreLabel->setColor(ccc3(0,0,0));
    this->addChild(scoreLabel);
    
    scoreDisplay = Label::createWithTTF("0","fonts/Marker Felt.ttf",32);
    scoreDisplay->setPosition(Point(visibleSize.width/2 + 50,visibleSize.height/1.3+150));
    scoreDisplay->setColor(ccc3(0,0,0));
    this->addChild(scoreDisplay);
    

    
    auto listener = EventListenerTouchOneByOne::create();
    //listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt){
    if(allowedMistakeCount == 0){
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
    }

    for(auto arrow : arrows){
        arrow->update(dt);
        if(arrow->getBoundingBox().intersectsRect(topbox->getBoundingBox()) &&
           arrow->getPosition().x < topbox->getPosition().x){
            arrow->removeFromParentAndCleanup(true);
            arrows.eraseObject(arrow);
            allowedMistakeCount--;
        }
    }
    health->setScale(allowedMistakeCount*0.1,1);
    
    this->scheduleOnce(schedule_selector(HelloWorld::addArrow), spawntime);
    if(points > 100){
        spawntime = 0.4;
    }else if(points > 50){
        spawntime = 0.5;
    }else if(points > 5){
        spawntime = 0.7;
    }
}

void HelloWorld::addArrow(float dt) {
    int randomTag =CCRANDOM_0_1()*4;
    Arrow *arrow = Arrow::create(randomTag);
    arrow->setPosition(Vec2(topbox->getPosition().x-200,topbox->getPosition().y-150));
    arrow->setZOrder(1);
    arrow->setCircleMidPoint(Vec2(topbox->getPosition().x,topbox->getPosition().y-200));
    gameBatchNode->addChild(arrow);
    arrows.pushBack(arrow);
}


bool HelloWorld::onTouchBegan(cocos2d::Touch *touch,
                             cocos2d::Event * event)
{

    Point location = touch->getLocation();
    for(auto arrow : arrows){
        if(arrow->getBoundingBox().intersectsRect(topbox->getBoundingBox())){
            
            if((leftButton->getBoundingBox().containsPoint(location) && arrow->getTag() == 2) ||
               (rightButton->getBoundingBox().containsPoint(location) && arrow->getTag() == 3) ||
               (topButton->getBoundingBox().containsPoint(location) && arrow->getTag() == 0) ||
               (bottomButton->getBoundingBox().containsPoint(location) && arrow->getTag() == 1)){
                
                
                // delete arrow if succesfully catched
                arrow->removeFromParentAndCleanup(true);
                arrows.eraseObject(arrow);
                
                // update score
                points++;
                scoreDisplay->setString(String::createWithFormat("%i", points)->getCString());
                
                // increase health bar
                if(allowedMistakeCount < 10){
                    allowedMistakeCount++;
                }
                break;
            }else{
                allowedMistakeCount--;
            }
            
        }
    }
    
    
    return true;
}
void HelloWorld::onTouchMoved(cocos2d::Touch *touch,cocos2d::Event * event)
{
    
    
}
void HelloWorld::onTouchEnded(cocos2d::Touch *touch,
                             cocos2d::Event * event)
{
}
void HelloWorld::onTouchCancelled(cocos2d::Touch *touch,
                                 cocos2d::Event * event)
{
    onTouchEnded(touch, event);
}
