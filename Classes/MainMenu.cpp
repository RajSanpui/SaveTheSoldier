//
// Created by rsanpui on 5/20/2020.
//

#include "MainMenu.h"
#include "GameScene.h"
#define TRANSITION_TIME 0.5
#include "../cocos2d/cocos/deprecated/CCDeprecated.h"
//#include "../cocos2d/cocos/physics/CCPhysicsBody.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = MainMenu::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init() {
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    this->addChild(backgroundSprite, 0);

    auto playItem = MenuItemImage::create( "Play.png", "CloseNormal.png", CC_CALLBACK_1( MainMenu::GoToGameScene, this ) );
    playItem->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    auto menuPlay = Menu::create( playItem, NULL );
    menuPlay->setPosition( Point::ZERO );

    this->addChild( menuPlay, 2 );

    return true;
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = GameScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
