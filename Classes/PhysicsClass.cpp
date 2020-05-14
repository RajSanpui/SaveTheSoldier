//
// Created by rsanpui on 5/14/2020.
//

#include "PhysicsClass.h"
#include "../cocos2d/cocos/deprecated/CCDeprecated.h"
//#include "../cocos2d/cocos/physics/CCPhysicsBody.h"
USING_NS_CC;

Scene* PhysicsClass::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = PhysicsClass::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool PhysicsClass::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite -> setPosition(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height/2);
    this->addChild(backgroundSprite, 1);

    soldierSprite = Sprite::create("Run1.png");
    soldierSprite -> setPosition(visibleSize.width / 2 , visibleSize.height * 0.4);
    initializePhysics(soldierSprite);
    addChild(soldierSprite, 2);

    initTouch();
    schedule(schedule_selector(PhysicsClass::addBoulder), 5.0f);
    return true;
}

void PhysicsClass::initializePhysics(Sprite* sprite)
{
    auto circle = PhysicsBody::createCircle(sprite -> getContentSize().width / 2);
    circle->setContactTestBitmask(true);
    circle->setDynamic(true);
    sprite->setPhysicsBody(circle);
}

void PhysicsClass::addBoulder(float dt)
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* boulder = nullptr;
    for(int i = 0 ; i < 3 ; i++)
    {
        boulder = cocos2d::Sprite::create("boulder1.png");
        boulder -> setAnchorPoint(cocos2d::Vec2::ZERO);
        boulder -> setPosition(CCRANDOM_0_1() * visibleSize.width , visibleSize.height);
        initializePhysics(boulder);
        boulder ->getPhysicsBody()->setVelocity(cocos2d::Vec2(10, ( (CCRANDOM_0_1() + 0.02f) * -150) ));
        this -> addChild(boulder, 1);
    }
}

void PhysicsClass::moveSoldier(Touch* touch, Event* evento)
{
    auto currPosition = touch->getLocation();
    if(soldierSprite->getBoundingBox().containsPoint(currPosition)){
        soldierSprite-> setPositionX(currPosition.x);
    }
}

void PhysicsClass::initTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener -> onTouchBegan = [] (Touch* touch, Event* event) { return true;};
    listener -> onTouchMoved = CC_CALLBACK_2(PhysicsClass::moveSoldier, this);
    listener -> onTouchEnded = [=] (Touch* touch, Event* event) {};
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
}

void PhysicsClass::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}