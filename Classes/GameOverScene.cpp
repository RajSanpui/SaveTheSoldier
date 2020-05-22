//
// Created by rsanpui on 5/21/2020.
//

#include "GameOverScene.h"
#include "GameScene.h"
#define TRANSITION_TIME 0.5

int GameOverScene::highestScore = 0; // Initialize static variable
USING_NS_CC;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = GameOverScene::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init() {
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));

    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));

    // Closing menu
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Background Sprite
    auto backgroundSprite = Sprite::create("gameOver.png");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    this->addChild(backgroundSprite, 0);

    // Play menu
    auto playItem = MenuItemImage::create( "Play.png", "CloseNormal.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    playItem->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    if (GameScene::SCORE > highestScore)
    {
        highestScore = GameScene::SCORE;
    }
    char text[256];
    sprintf(text,"Score: %d, Highest Score: %d",GameScene::SCORE, highestScore);
    auto scoreLabel = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel, 2);

    auto menuPlay = Menu::create( playItem, NULL );
    menuPlay->setPosition( Point::ZERO );

    this->addChild( menuPlay, 2 );

    return true;
}

void GameOverScene::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = GameScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void GameOverScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}