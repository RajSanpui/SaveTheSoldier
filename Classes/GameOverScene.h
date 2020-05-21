//
// Created by rsanpui on 5/21/2020.
//

#ifndef PROJ_ANDROID_GAMEOVERSCENE_H
#define PROJ_ANDROID_GAMEOVERSCENE_H

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::CCObject* pSender);
    CREATE_FUNC(GameOverScene);
    void GoToGameScene( cocos2d::Ref *sender );
};

#endif //PROJ_ANDROID_GAMEOVERSCENE_H
