//
// Created by rsanpui on 5/14/2020.
//

#include "GameScene.h"
#include "GameOverScene.h"
#define TRANSITION_TIME 0.5
#include "../cocos2d/cocos/deprecated/CCDeprecated.h"
//#include "../cocos2d/cocos/physics/CCPhysicsBody.h"
USING_NS_CC;

int GameScene::SCORE = 0; // Initialize static variable
enum class PhysicsCategory {
    None = 0,
    Boulder = (1 << 0),    // 1
    Soldier = (1 << 1), // 2
    All = PhysicsCategory::Boulder | PhysicsCategory::Soldier // 3
};

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
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
            CC_CALLBACK_1(GameScene::menuCloseCallback, this));

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

    // Scoring section initialization
    SCORE = 0; // Re-initialize to zero.
    char text[256];
    sprintf(text,"SCORE: %d", SCORE);
    scoreLabel = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel, 2);

    // Adding the soldier
    soldierSprite = Sprite::create("soldier.png");
    soldierSprite -> setPosition(visibleSize.width / 2 , visibleSize.height * 0.4);
    initializePhysics(soldierSprite);

    soldierSprite->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Soldier);
    soldierSprite->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    soldierSprite->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Boulder);
    addChild(soldierSprite, 2);

    // Touch init, add boulders and event listeners
    initTouch();
    schedule(schedule_selector(GameScene::addBoulder), 5.0f);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


    return true;
}

bool GameScene::onContactBegan(PhysicsContact &contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    nodeA->removeFromParent();
    nodeB->removeFromParent();

    auto scene = GameOverScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );

    return true;
}

void GameScene::initializePhysics(Sprite* sprite)
{
    auto circle = PhysicsBody::createCircle(sprite -> getContentSize().width / 2);
    circle->setContactTestBitmask(true);
    circle->setDynamic(true);
    sprite->setPhysicsBody(circle);
}

void GameScene::addBoulder(float dt)
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
        boulder->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Boulder);
        boulder->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
        boulder->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Soldier);
        this -> addChild(boulder, 1);

    }
    SCORE++; // Score increment
    scoreLabel->setString("SCORE: " + std::to_string(SCORE));

}

void GameScene::moveSoldier(Touch* touch, Event* evento)
{
    auto currPosition = touch->getLocation();
    if(soldierSprite->getBoundingBox().containsPoint(currPosition)){
        soldierSprite-> setPositionX(currPosition.x);
    }
}

void GameScene::initTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener -> onTouchBegan = [] (Touch* touch, Event* event) { return true;};
    listener -> onTouchMoved = CC_CALLBACK_2(GameScene::moveSoldier, this);
    listener -> onTouchEnded = [=] (Touch* touch, Event* event) {};
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}