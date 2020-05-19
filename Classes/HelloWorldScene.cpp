//
// Created by rsanpui on 5/14/2020.
//

#include "HelloWorldScene.h"
#include "../cocos2d/cocos/deprecated/CCDeprecated.h"
//#include "../cocos2d/cocos/physics/CCPhysicsBody.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = origin.y + closeItem->getContentSize().height/2;
    closeItem->setPosition(Vec2(x,y));


    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite -> setPosition(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height/2);
    this->addChild(backgroundSprite, 1);

    soldierSprite = Sprite::create("soldier.png");
    soldierSprite -> setPosition(visibleSize.width / 2 , visibleSize.height * 0.4);
    initializePhysics(soldierSprite);
    addChild(soldierSprite, 2);

    initTouch();
    schedule(schedule_selector(HelloWorld::addBoulder), 5.0f);
    return true;
}

void HelloWorld::initializePhysics(Sprite* sprite)
{
    auto circle = PhysicsBody::createCircle(sprite -> getContentSize().width / 2);
    circle->setContactTestBitmask(true);
    circle->setDynamic(true);
    sprite->setPhysicsBody(circle);
}

void HelloWorld::addBoulder(float dt)
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* boulder = nullptr;
    for(int i = 0 ; i < 3 ; i++)
    {
        boulder = cocos2d::Sprite::create("boulder.png");
        boulder -> setAnchorPoint(cocos2d::Vec2::ZERO);
        boulder -> setPosition(CCRANDOM_0_1() * visibleSize.width , visibleSize.height);
        initializePhysics(boulder);
        boulder ->getPhysicsBody()->setVelocity(cocos2d::Vec2(10, ( (CCRANDOM_0_1() + 0.02f) * -150) ));
        this -> addChild(boulder, 1);
    }
}

void HelloWorld::moveSoldier(Touch* touch, Event* evento)
{
    auto currPosition = touch->getLocation();
    if(soldierSprite->getBoundingBox().containsPoint(currPosition)){
        soldierSprite-> setPositionX(currPosition.x);
    }
}

void HelloWorld::initTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener -> onTouchBegan = [] (Touch* touch, Event* event) { return true;};
    listener -> onTouchMoved = CC_CALLBACK_2(HelloWorld::moveSoldier, this);
    listener -> onTouchEnded = [=] (Touch* touch, Event* event) {};
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}